#include <argp.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FRAME.hpp"
// g++ test_frame.cpp ../src/NBD.cpp ../src/Reactor.cpp -I ../include
using namespace ilrd;

static void *data;

void Show(const void *data)
{
    for(int i = 0; i < 100; ++i)
    {
        std::cout << *(((char*)(data)) + i);
    }
    std::cout << '\n';
}

int my_read(void *buf, u_int32_t len, u_int64_t offset, void *userdata)
{   
    (void*)userdata;
    std::cout << "My_read" << std::endl;
    memcpy(buf, (char *)data + offset, len);
    Show(buf);
    return 0;
}

int my_write(const void *buf, u_int32_t len, u_int64_t offset, void *userdata)
{
    (void*)userdata;
    std::cout << "My_write" << std::endl;
    memcpy((char *)data + offset, buf, len);
    Show(buf);
  return 0;
}

void my_disc(void *userdata)
{   
    (void*)userdata;
    std::cout << "My_disc" << std::endl;
}

int my_flush(void *userdata)
{
    (void*)userdata;
    std::cout << "My_flush" << std::endl;
    return 0;
}

int my_trim(u_int64_t from, u_int32_t len, void *userdata)
{   
    (void*)userdata;
    std::cout << "My_trim" << std::endl;
    return 0;
}


static struct argp_option options[] = {
    {"verbose", 'v', 0, 0, "Produce verbose output", 0},
    {0},
};

struct arguments 
{
    unsigned long long size;
    char * device;
    int verbose;
};

static unsigned long long strtoull_with_prefix(const char *str, char **end) 
{
    unsigned long long v = strtoull(str, end, 0);
    switch (**end) 
    {
        case 'K':
            v *= 1024;
            *end += 1;
            break;
        case 'M':
            v *= 1024 * 1024;
            *end += 1;
            break;
        case 'G':
            v *= 1024 * 1024 * 1024;
            *end += 1;
            break;
    }
    return v;
}

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, struct argp_state *state) 
{
    struct arguments *arguments = (struct arguments *)(state->input);

    char *endptr;

    switch (key) 
    {

    case 'v':
        arguments->verbose = 1;
        break;

    case ARGP_KEY_ARG:
        switch (state->arg_num) 
        {
        case 0:
            arguments->size = strtoull_with_prefix(arg, &endptr);
            if (*endptr != '\0') 
            {
                /* failed to parse integer */
                errx(EXIT_FAILURE, "SIZE must be an integer");
            }
            break;

        case 1:
            arguments->device = arg;
            break;

        default:
            /* Too many arguments. */
            return ARGP_ERR_UNKNOWN;
        }
        break;

    case ARGP_KEY_END:
        if (state->arg_num < 2) 
        {
            warnx("not enough arguments");
            argp_usage(state);
        }
        break;

    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {
    .options = options,
    .parser = parse_opt,
    .args_doc = "SIZE DEVICE",
    .doc = "BUSE virtual block device that stores its content in memory.\n""`SIZE` accepts suffixes K, M, G. `DEVICE` is path to block device, for example \"/dev/nbd0\".",
};

void Foo()
{
    std::cout << "FOO" << std::endl;
}

int main(int argc, char *argv[])
{
    struct arguments arguments = {
    .verbose = 0,
    };

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    struct buse_operations aop = {
        .read = my_read,
        .write = my_write,
        .disc = my_disc,
        .flush = my_flush,
        .trim = my_trim,
        .size = arguments.size,
    };

    data = malloc(aop.size);
    if (data == NULL) 
    {
        err(EXIT_FAILURE, "failed to alloc space for data");
    }
    
    NBDServer nbd(&aop, arguments.device, (void *)&arguments.verbose);
    FRAME frame(nbd);
    frame.Run_Reactor();

    


    return 0;   
}