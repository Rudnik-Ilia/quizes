#include <assert.h>
#include <errno.h>
#include <err.h>
#include <fcntl.h>
#include <linux/nbd.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#ifndef BUSE_DEBUG
#define BUSE_DEBUG (0)
#endif


struct buse_operations 
{
    int (*read)(void *buf, u_int32_t len, u_int64_t offset, void *userdata);
    int (*write)(const void *buf, u_int32_t len, u_int64_t offset, void *userdata);
    void (*disc)(void *userdata);
    int (*flush)(void *userdata);
    int (*trim)(u_int64_t from, u_int32_t len, void *userdata);

    // either set size, OR set both blksize and size_blocks
    u_int64_t size;
    u_int32_t blksize;
    u_int64_t size_blocks;
};

class NBDServer 
{
    public:
        NBDServer(struct buse_operations* aop, void* userdata, const char* dev_file) : sk_(0), aop_(aop), userdata_(userdata) , dev_file(dev_file){}
        ~NBDServer() = default;

        static void disconnect_nbd(int signal) 
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

        int write_all(int fd, char* buf, size_t count)
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

        int read_all(int fd, char* buf, size_t count)
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

        int set_sigaction(int sig, const struct sigaction * act) 
        {
            struct sigaction oact;
            int r = sigaction(sig, act, &oact);
            if (r == 0 && oact.sa_handler != SIG_DFL) 
            {
                warnx("overriden non-default signal handler (%d: %s)", sig, strsignal(sig));
            }
            return r;
        }

        int Serve() 
        {
            u_int64_t from;
            u_int32_t len;
            ssize_t bytes_read;
            struct nbd_request request;
            struct nbd_reply reply;
            void *chunk;

            reply.magic = htonl(NBD_REPLY_MAGIC);
            reply.error = htonl(0);

            while ((bytes_read = read(sk_, &request, sizeof(request))) > 0) 
            {
                assert(bytes_read == sizeof(request));

                memcpy(reply.handle, request.handle, sizeof(reply.handle));
                reply.error = htonl(0);

                len = ntohl(request.len);
                from = ntohll(request.from);

                assert(request.magic == htonl(NBD_REQUEST_MAGIC));

                switch(ntohl(request.type)) 
                {
                    /* I may at some point need to deal with the the fact that the
                    * official nbd server has a maximum buffer size, and divides up
                    * oversized requests into multiple pieces. This applies to reads
                    * and writes.
                    */
                    case NBD_CMD_READ:
                        if (BUSE_DEBUG)
                        {
                            fprintf(stderr, "Request for read of size %d\n", len);
                        }
                        /* Fill with zero in case actual read is not implemented */
                        chunk = malloc(len);
                        if (aop_->read) 
                        {
                            reply.error = aop_->read(chunk, len, from, userdata_);
                        } 
                        else 
                        {
                        /* If user not specified read operation, return EPERM error */
                            reply.error = htonl(EPERM);
                        }
                        write_all(sk_, (char*)&reply, sizeof(struct nbd_reply));
                        write_all(sk_, (char*)chunk, len);

                        free(chunk);
                        break;

                    case NBD_CMD_WRITE:
                        if (BUSE_DEBUG) 
                        {
                            fprintf(stderr, "Request for write of size %d\n", len);
                        }
                        chunk = malloc(len);

                        read_all(sk_, (char*)chunk, len);

                        if (aop_->write) 
                        {
                            reply.error = aop_->write(chunk, len, from, userdata_);
                        } 
                        else 
                        {
                        /* If user not specified write operation, return EPERM error */
                            reply.error = htonl(EPERM);
                        }
                        free(chunk);
                        write_all(sk_, (char*)&reply, sizeof(struct nbd_reply));
                        break;

                    case NBD_CMD_DISC:
                        if (BUSE_DEBUG) 
                        {
                            fprintf(stderr, "Got NBD_CMD_DISC\n");
                        }
                        /* Handle a disconnect request. */
                        if (aop_->disc) 
                        {
                            aop_->disc(userdata_);
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
                            reply.error = aop_->flush(userdata_);
                        }
                        write_all(sk_, (char*)&reply, sizeof(struct nbd_reply));
                        break;
                        #endif

                    #ifdef NBD_FLAG_SEND_TRIM
                    case NBD_CMD_TRIM:
                        if (BUSE_DEBUG) fprintf(stderr, "Got NBD_CMD_TRIM\n");
                        if (aop_->trim) {
                        reply.error = aop_->trim(from, len, userdata_);
                        }
                        write_all(sk_, (char*)&reply, sizeof(struct nbd_reply));
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

        int Init()
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
        }

        int Buse_main()
        {
            Init();

            pid_t pid = fork();

            if (pid == 0) 
            {
                /* Block all signals to not get interrupted in ioctl(NBD_DO_IT), as
                * it seems there is no good way to handle such interruption.*/
                sigset_t sigset;

                if (sigfillset(&sigset) != 0 || sigprocmask(SIG_SETMASK, &sigset, NULL) != 0) 
                {
                    warn("failed to block signals in child");
                    exit(EXIT_FAILURE);
                }

                /* The child needs to continue setting things up. */
                close(sp[0]);
                sk_ = sp[1];

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

                exit(0);
            }

            /* Parent handles termination signals by terminating nbd device. */
            assert(nbd_dev_to_disconnect == -1);

            nbd_dev_to_disconnect = nbd;

            struct sigaction act;
            act.sa_handler = disconnect_nbd;
            act.sa_flags = SA_RESTART;

            if (sigemptyset(&act.sa_mask) != 0 || sigaddset(&act.sa_mask, SIGINT) != 0 || sigaddset(&act.sa_mask, SIGTERM) != 0) 
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

            /* serve NBD socket */
            int status;
            status = Serve();

            if (close(sp[0]) != 0) 
            {
                warn("problem closing server side nbd socket");
            }
            if (status != 0) 
            {
                return status;
            }

            /* wait for subprocess */

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

    private:

        static int nbd_dev_to_disconnect;
        int sk_;
        const struct buse_operations* aop_;
        void* userdata_;
        const char* dev_file;
        int sp[2];
        int nbd, err, flags;

        u_int64_t ntohll(u_int64_t a) 
        {
            u_int32_t lo = a & 0xffffffff;
            u_int32_t hi = a >> 32U;
            lo = ntohl(lo);
            hi = ntohl(hi);
            return ((u_int64_t) lo) << 32U | hi;
        }
};

int NBDServer::nbd_dev_to_disconnect = -1;
