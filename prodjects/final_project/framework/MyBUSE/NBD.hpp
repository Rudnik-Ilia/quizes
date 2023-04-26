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


  struct buse_operations {
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
        NBDServer(int sk, const struct buse_operations* aop, void* userdata) : nbd_dev_to_disconnect(-1), sk_(sk), aop_(aop), userdata_(userdata) {}

        ~NBDServer() 
        {
            if (nbd_dev_to_disconnect != -1) 
            {
                if (ioctl(nbd_dev_to_disconnect, NBD_DISCONNECT) == -1) 
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

        void disconnect_nbd(int signal) 
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
                if (bytes_written <= 0) {
                    return -1;
                }
                buf += bytes_written;
                count -= bytes_written;
            }

            return 0;
        }

        int read_all(int fd, char* buf, size_t count) 
        {
            int bytes_read;

            while (count > 0) 
            {
                bytes_read = read(fd, buf, count);
                if (bytes_read <= 0) 
                {
                    return -1;
                }
                buf += bytes_read;
                count -= bytes_read;
            }

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

        void Serve() 
        {
            u_int64_t from;
            u_int32_t len;
            ssize_t bytes_read;
            struct nbd_request request;
            struct nbd_reply reply;
            void* chunk;

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

                switch (ntohl(request.type)) 
                {
                    case NBD_CMD_READ:
                        if (BUSE_DEBUG) 
                        {
                            fprintf(stderr, "Request for read of size %d\n", len);
                        }
                        chunk = (char*)malloc(len);
                        if (aop_->read) 
                        {
                            reply.error = aop_->read(chunk, len, from, userdata_);
                        }
                        else 
                        {
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
                        chunk = (char*)malloc(len);

                        read_all(sk_, (char*)chunk, len);

                        if (aop_->write) 
                        {
                            reply.error = aop_->write(chunk, len, from, userdata_);
                        }
                        else 
                        {
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
                        if (aop_->disc) {
                        aop_->disc(userdata_);
                        }
                        return;
                    default:
                        fprintf(stderr, "Unknown command %d\n", ntohl(request.type));
                        reply.error = htonl(EINVAL);
                        write_all(sk_, (char*)&reply, sizeof(struct nbd_reply));
                        break;
                }
            }
        }

    private:
        int nbd_dev_to_disconnect;
        int sk_;
        const struct buse_operations* aop_;
        void* userdata_;

        u_int64_t ntohll(u_int64_t a) 
        {
            #ifdef WORDS_BIGENDIAN
            return a;
            #else
            u_int32_t lo = a & 0xffffffff;
            u_int32_t hi = a >> 32U;
            lo = ntohl(lo);
            hi = ntohl(hi);
            return ((u_int64_t) lo) << 32U | hi;
            #endif
        }



};
