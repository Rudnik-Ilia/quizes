#include <vector>

#include "NBD.hpp" 
#include "Singleton.hpp"
#include "Reactor.hpp"
#include "ThreadPool.hpp"

namespace ilrd
{
    int NBDServer::nbd_dev_to_disconnect = -1;

    NBDServer::NBDServer(struct buse_operations* aop, const char* dev_file) : aop_(aop), dev_file(dev_file){}

    NBDServer::~NBDServer()
    {
        Quit();
    }

    void NBDServer::disconnect_nbd(int signal) 
    {
        (void)signal;
        if (nbd_dev_to_disconnect != -1) 
        {
            if(ioctl(nbd_dev_to_disconnect, NBD_DISCONNECT) == -1) 
            {
                warn("failed to request disconect on nbd device");
            } 
            else 
            {
                nbd_dev_to_disconnect = -1;
                fprintf(stderr, "sucessfuly requested disconnect on nbd device\n");
            }
        }
    }

    int NBDServer::write_all(int fd, char* buf, size_t count)
    {
        int bytes_written;
        while (count > 0) 
        {
            bytes_written = write(fd, buf, count);
            assert(bytes_written > 0);
            buf += bytes_written;
            count -= bytes_written;
        }
        assert(count == 0);

        return 0;
    }

    int NBDServer::read_all(int fd, char* buf, size_t count)
    {
        int bytes_read;

        while (count > 0) 
        {
            bytes_read = read(fd, buf, count);
            assert(bytes_read > 0);
            buf += bytes_read;
            count -= bytes_read;
        }
        assert(count == 0);

        return 0;
    }

    int NBDServer::set_sigaction(int sig, const struct sigaction * act) 
    {
        struct sigaction oact;
        int r = sigaction(sig, act, &oact);
        if (r == 0 && oact.sa_handler != SIG_DFL) 
        {
            warnx("overriden non-default signal handler (%d: %s)", sig, strsignal(sig));
        }
        return r;
    }

    int NBDServer::Serve() 
    {
        u_int64_t from;
        u_int32_t len;
        ssize_t bytes_read;
        struct nbd_request request;
        struct nbd_reply reply;
     
        reply.magic = htonl(NBD_REPLY_MAGIC);
        reply.error = htonl(0);

        if((bytes_read = read(sp[0], &request, sizeof(request))) > 0) 
        {
            assert(bytes_read == sizeof(request));
            memcpy(reply.handle, request.handle, sizeof(reply.handle));
            // std::cout << "SERVE: " <<  *(u_int64_t*)reply.handle << std::endl;
            
            reply.error = htonl(0);
            len = ntohl(request.len);
            from = ntohll(request.from);

            assert(request.magic == htonl(NBD_REQUEST_MAGIC));

            auto chunk = std::make_shared<std::vector<char>>(len, 0); 

            switch(ntohl(request.type)) 
            {
                case NBD_CMD_READ:
                    if (BUSE_DEBUG)
                    {
                        fprintf(stderr, "Request for read of size %d\n", len);
                    }

                    m_args = std::make_shared<ArgumentsForTask>(ArgumentsForTask{chunk, *(u_int64_t*)request.handle, from, len, 33, nullptr});
                    break;

                case NBD_CMD_WRITE:

                    if (BUSE_DEBUG) 
                    {
                        fprintf(stderr, "Request for write of size %d\n", len);
                    }

                    read_all(sp[0], chunk.get()->data(), len);
                    m_args = std::make_shared<ArgumentsForTask>(ArgumentsForTask{chunk, *(u_int64_t*)reply.handle, from, len, 1, nullptr});
                    
                    write_all(sp[0], (char*)&reply, sizeof(struct nbd_reply));
                    break;
                    
                case NBD_CMD_DISC:
    
                    if (BUSE_DEBUG) 
                    {
                        fprintf(stderr, "Got NBD_CMD_DISC\n");
                    }
                    if (aop_->disc) 
                    {
                        aop_->disc();
                    }
                    return EXIT_SUCCESS;

                #ifdef NBD_FLAG_SEND_FLUSH
                case NBD_CMD_FLUSH:

                    if (BUSE_DEBUG) 
                    {
                        fprintf(stderr, "Got NBD_CMD_FLUSH\n");
                    }
                    if (aop_->flush) 
                    {
                        reply.error = aop_->flush();
                    }
                    m_args = std::make_shared<ArgumentsForTask>(ArgumentsForTask{chunk, *(u_int64_t*)reply.handle, from, len, 3, nullptr});
                    write_all(sp[0], (char*)&reply, sizeof(struct nbd_reply));
                    break;
                    #endif

                #ifdef NBD_FLAG_SEND_TRIM
                case NBD_CMD_TRIM:

                    if (BUSE_DEBUG) 
                    {
                        fprintf(stderr, "Got NBD_CMD_TRIM\n");
                    }
                    if (aop_->trim) 
                    {
                        reply.error = aop_->trim(from, len);
                    }

                    write_all(sp[0], (char*)&reply, sizeof(struct nbd_reply));
                    break;
                    #endif

                default:
                    assert(0);
            }
        }
   
        if (bytes_read == -1)
        {
            warn("error reading userside of nbd socket");
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }


    int NBDServer::Init() 
    {
        err = socketpair(AF_UNIX, SOCK_STREAM, 0, sp);
        assert(!err);

        nbd = open(dev_file, O_RDWR);
        
        if (nbd == -1) 
        {
            fprintf(stderr, "Failed to open `%s': %s\n" "Is kernel module `nbd' loaded and you have permissions " "to access the device?\n", dev_file, strerror(errno));
            return 1;
        }
        if (aop_->blksize) 
        {
            err = ioctl(nbd, NBD_SET_BLKSIZE, aop_->blksize);
            assert(err != -1);
        }
        if (aop_->size) 
        {
            err = ioctl(nbd, NBD_SET_SIZE, aop_->size);
            assert(err != -1);
        }
        if (aop_->size_blocks) 
        {
            err = ioctl(nbd, NBD_SET_SIZE_BLOCKS, aop_->size_blocks);
            assert(err != -1);
        }

        err = ioctl(nbd, NBD_CLEAR_SOCK);
        assert(err != -1);

        return 0;
    }

    int NBDServer::HandlerStaff()
    {
        assert(nbd_dev_to_disconnect == -1);

        nbd_dev_to_disconnect = nbd;

        struct sigaction act;
        act.sa_handler = disconnect_nbd;
        act.sa_flags = SA_RESTART;

        struct sigaction sa;
        sa.sa_handler = SIG_IGN;
        sa.sa_flags = 0;

        if (sigemptyset(&sa.sa_mask) == -1 || sigaction(SIGPIPE, &sa, 0) == -1) 
        {
            perror("failed to ignore SIGPIPE; sigaction");
            exit(EXIT_FAILURE);
        }
        if(sigemptyset(&act.sa_mask) != 0 || sigaddset(&act.sa_mask, SIGINT) != 0 || sigaddset(&act.sa_mask, SIGTERM) != 0) 
        {
            warn("failed to prepare signal mask in parent");
            return EXIT_FAILURE;
        }
        if (set_sigaction(SIGINT, &act) != 0 || set_sigaction(SIGTERM, &act) != 0) 
        {
            warn("failed to register signal handlers in parent");
            return EXIT_FAILURE;
        }

        close(sp[1]);
        return 0;
    }

    int NBDServer::Buse_main()
    {
        pid = fork();
        if (pid == 0) 
        {
            sigset_t sigset;

            if (sigfillset(&sigset) != 0 || sigprocmask(SIG_SETMASK, &sigset, NULL) != 0) 
            {
                warn("failed to block signals in child");
                exit(EXIT_FAILURE);
            }

            close(sp[0]);
            int sk_ = sp[1];

            if(ioctl(nbd, NBD_SET_SOCK, sk_) == -1)
            {
                fprintf(stderr, "ioctl(nbd, NBD_SET_SOCK, sk) failed.[%s]\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
            else
            {
                #if defined NBD_SET_FLAGS
                flags = 0;
                #if defined NBD_FLAG_SEND_TRIM
                flags |= NBD_FLAG_SEND_TRIM;
                #endif
                #if defined NBD_FLAG_SEND_FLUSH
                flags |= NBD_FLAG_SEND_FLUSH;
                #endif
                if (flags != 0 && ioctl(nbd, NBD_SET_FLAGS, flags) == -1)
                {
                    fprintf(stderr, "ioctl(nbd, NBD_SET_FLAGS, %d) failed.[%s]\n", flags, strerror(errno));
                    exit(EXIT_FAILURE);
                }
                #endif
                err = ioctl(nbd, NBD_DO_IT);

                if (BUSE_DEBUG) 
                {
                    fprintf(stderr, "nbd device terminated with code %d\n", err);
                }
                if (err == -1) 
                {
                    warn("NBD_DO_IT terminated with error");
                    exit(EXIT_FAILURE);
                }
            }

            if (ioctl(nbd, NBD_CLEAR_QUE) == -1 || ioctl(nbd, NBD_CLEAR_SOCK) == -1) 
            {
                warn("failed to perform nbd cleanup actions");
                exit(EXIT_FAILURE);
            }

            std::cout << "EXIT" << std::endl;

            exit(0);
        }
        return 0;
    }
    int NBDServer::Quit()
    {
        int status;

        if (close(sp[0]) != 0) 
        {
            warn("problem closing server side nbd socket");
        }
        if (waitpid(pid, &status, 0) == -1) 
        {
            warn("waitpid failed");
            return EXIT_FAILURE;
        }
        if (WEXITSTATUS(status) != 0) 
        {
            return WEXITSTATUS(status);
        }
        return EXIT_SUCCESS;
    }
    
    void NBDServer::Start()
    {
        Init();
        Buse_main();
        HandlerStaff(); 
    }

    int NBDServer::GetDescriptor()
    {
        return sp[0];
    }

    std::shared_ptr<struct ArgumentsForTask>& NBDServer::GetArguments()
    {
        return m_args;
    }
}