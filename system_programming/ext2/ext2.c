#include <stdio.h>

#include <linux/fs.h>
#include <ext2fs/ext2fs.h>
#include <unistd.h>

#include "ext2.h"

#define OFFSET_1024 (1024)
#define BLOCK_OFFSET(block) (OFFSET_1024+(block-1)*block_size)

static unsigned int block_size = 1024;


void FindGroup(struct ext2_group_desc* group_desc, int fd)
{
    struct ext2_super_block super_block = {0};
    int block_size = 0;
    int group_count = 0;
    int descr_list_size = 0;

    lseek(fd, OFFSET_1024, SEEK_SET);
    read(fd, &super_block, sizeof(super_block));

    if (super_block.s_magic != EXT2_SUPER_MAGIC) 
    {
        fprintf(stderr, "Its not EXT2 %d\n", errno);
    }
    block_size = 1024 << super_block.s_log_block_size;

    lseek(fd, block_size, SEEK_SET);
    read(fd, group_desc, sizeof(* group_desc));

    group_count = 1 + (super_block.s_blocks_count-1) / super_block.s_blocks_per_group;
    descr_list_size = group_count * sizeof(* group_desc);
    close(fd);

    printf("Reading super-block from device :\n"
        "Inodes count            : %u\n"
        "Blocks count            : %u\n"
        "Free blocks count       : %u\n"
        "Free inodes count       : %u\n"
        "First data block        : %u\n"
        "Block size              : %u\n"
        "Blocks per group        : %u\n"
        "Inodes per group        : %u\n"
        "Creator OS              : %u\n"
        "Size of inode structure : %hu\n",
        
        super_block.s_inodes_count,
        super_block.s_blocks_count,
        super_block.s_free_blocks_count,
        super_block.s_free_inodes_count,
        super_block.s_first_data_block,
        block_size,
        super_block.s_blocks_per_group,
        super_block.s_inodes_per_group,
        super_block.s_creator_os,
        super_block.s_inode_size);

    printf("Reading first group-descriptor from device:\n"
        "Blocks bitmap block: %u\n"
        "Inodes bitmap block: %u\n"
        "Inodes table block : %u\n"
        "Free blocks count  : %u\n"
        "Free inodes count  : %u\n"
        "Directories count  : %u\n",
    
        group_desc->bg_block_bitmap,
        group_desc->bg_inode_bitmap,
        group_desc->bg_inode_table,
        group_desc->bg_free_blocks_count,
        group_desc->bg_free_inodes_count,
        group_desc->bg_used_dirs_count); 

    
}

void Read_Inode(int fd, struct ext2_group_desc *group_descriptor, int inode_number, struct ext2_inode *inode)
{
    lseek(fd, BLOCK_OFFSET(group_descriptor->bg_inode_table) + (inode_number - 1) * sizeof(struct ext2_inode), SEEK_SET);
	read(fd, inode, sizeof(struct ext2_inode));
}