#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/fs.h>
#include <ext2fs/ext2fs.h>
#include <unistd.h>
#include <fcntl.h>

#include "ext2.h"

#define PATH "/dev/ram0"
#define PATH_1 "/home/ilia53/mydisk"



int main(int argc, char *argv[])
{
    struct ext2_group_desc group_desc = {0};
    struct ext2_inode inode = {0};
    int fd = 0; 

    if( (fd = open(PATH, O_RDONLY)) < 0)
    {
        fprintf(stderr, "can't open file%d\n", errno);
        exit(1);
    }

    FindGroup(&group_desc, fd);
    

   

  
    
    // printf("%d\n", group_desc.bg_inode_table);q

    // printf("%d\n", super_block.s_inodes_count);
    // printf("%d\n", super_block.s_blocks_count);
    // printf("%d\n", super_block.s_log_block_size);
    
    return 0;
}