#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ext2fs/ext2fs.h> 
#include "ext2.h"

#define PATH "/dev/ram0"

#define FILE "path/text.txt"

int main(int argc, char **argv)
{
    struct ext2_inode inode = {0};
    struct ext2_group_desc group = {0};
    int fd = 0;
    int i = 0;
    fd = open(PATH, O_RDONLY);
    
    if(fd == -1)
    {
        perror("open is failed");
        return -1;
    }

    FindGroupDescriptor(&group, fd);
    printf("Reading first group-descriptor from device " PATH ":\n"
	       "Blocks bitmap block: %u\n"
	       "Inodes bitmap block: %u\n"
	       "Inodes table block : %u\n"
	       "Free blocks count  : %u\n"
	       "Free inodes count  : %u\n"
	       "Directories count  : %u\n"
	       ,
	       group.bg_block_bitmap,
	       group.bg_inode_bitmap,
	       group.bg_inode_table,
	       group.bg_free_blocks_count,
	       group.bg_free_inodes_count,
	       group.bg_used_dirs_count);

	printf("path %s\n", FILE);
	PrintDataFromFileByPath(fd, FILE, &group); 
	FindDir(fd, &group, &inode, FILE, &inode);
	ReadData(fd, &inode);
    return 0;
}



