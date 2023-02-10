#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/fs.h>
#include <ext2fs/ext2fs.h>
#include <unistd.h>
#include <fcntl.h>

#include "ext2.h"

// #define PATH ("/dev/ram0")
// #define NEED_TO_FIND  ("papka/txt.txt")


int main(int argc, char *argv[])
{
    int i = 0;
    int node_num = 0;
    struct ext2_group_desc group_desc = {0};
    struct ext2_inode inode = {0};
    int fd = 0; 

    if( (fd = open(argv[1], O_RDONLY)) < 0)
    {
        fprintf(stderr, "can't open file%d\n", errno);
        exit(1);
    }

    FindGroup(&group_desc, fd);
   

    PrintDataFromFileByPath(fd, argv[2], &group_desc); 

    Find_File_Dir(fd, &group_desc, &inode, argv[2], &inode);
   
    ReadData(fd, &inode);

    close(fd);

    return 0;
}