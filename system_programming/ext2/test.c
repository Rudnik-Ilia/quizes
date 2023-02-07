#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/fs.h>
#include <ext2fs/ext2fs.h>
#include <unistd.h>
#include <fcntl.h>

#include "ext2.h"
#define PATH "/dev/ram0"




int main(int argc, char *argv[])
{
    int i = 0;
    struct ext2_group_desc group_desc = {0};
    struct ext2_inode inode = {0};
    int fd = 0; 

    if( (fd = open(PATH, O_RDONLY)) < 0)
    {
        fprintf(stderr, "can't open file%d\n", errno);
        exit(1);
    }

    FindGroup(&group_desc, fd);

   
    Read_Inode(fd, 2, &group_desc, &inode);

    printf("Reading root inode: \n"
        "File mode: %hu\n"
        "Owner UID: %hu\n"
        "Size     : %u bytes\n"
        "Blocks   : %u\n"
        ,
        inode.i_mode,
        inode.i_uid,
        inode.i_size,
        inode.i_blocks);

    
	for(int i=0; i<EXT2_N_BLOCKS; i++)
		if (i < EXT2_NDIR_BLOCKS)        
			printf("Block %2u : %u\n", i, inode.i_block[i]);
		else if (i == EXT2_IND_BLOCK)   
			printf("Single   : %u\n", inode.i_block[i]);
		else if (i == EXT2_DIND_BLOCK)  
			printf("Double   : %u\n", inode.i_block[i]);
		else if (i == EXT2_TIND_BLOCK)  
			printf("Triple   : %u\n", inode.i_block[i]);


    printf(" ");



   

  
    
   
    
    return 0;
}