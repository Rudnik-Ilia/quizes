#include <stdio.h>
#include <stdlib.h>
#include <linux/fs.h>
#include <ext2fs/ext2fs.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ext2fs/ext2_fs.h>
#include <string.h>  
#include "ext2.h"
#define OFFSET_1024 (1024)
#define BLOCK_OFFSET(block) (block * block_size)

int block_size = 0;

void FindGroup(struct ext2_group_desc* group_desc, int fd)
{
    struct ext2_super_block super_block;
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
    read(fd, group_desc, sizeof(*group_desc));

    printf("Reading super-block from device :\n"
        "Inodes count            : %u\n"
        "Blocks count            : %u\n"
        "Free blocks count       : %u\n"
        "Free inodes count       : %u\n"
        "First data block        : %u\n"
        "Block size              : %u\n"
        "Blocks per group        : %u\n"
        "Inodes per group        : %u\n"
        "Size of inode structure : %hu\n",
        
        super_block.s_inodes_count,
        super_block.s_blocks_count,
        super_block.s_free_blocks_count,
        super_block.s_free_inodes_count,
        super_block.s_first_data_block,
        block_size,
        super_block.s_blocks_per_group,
        super_block.s_inodes_per_group,
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

void ReadInode(int fd, int inode_no, struct ext2_group_desc *group,  struct ext2_inode *inode)
{
    lseek(fd, BLOCK_OFFSET(group->bg_inode_table) + (inode_no - 1)* sizeof(struct ext2_inode), SEEK_SET);
	read(fd, inode, sizeof(struct ext2_inode));
}

int Find_File_Dir(int fd, struct ext2_group_desc *group_descriptor, struct ext2_inode *inode, char *path, struct ext2_inode *ret_inode)
{
    void* block;
    size_t i = 0;

    if(S_ISDIR(inode->i_mode))
    {
        struct ext2_dir_entry_2 *entry;
        size_t size = 0;

        block = malloc(sizeof(block_size));

        for(i = 0; i < EXT2_N_BLOCKS; ++i)
        {
            lseek(fd, BLOCK_OFFSET(inode->i_block[i]), SEEK_SET);
		    read(fd, block, block_size); 
            entry = (struct ext2_dir_entry_2*)block;
       
            while((size < inode->i_size) && entry->inode)
            {
                char file_name[EXT2_NAME_LEN+1];
                
                memcpy(file_name, entry->name, entry->name_len);
                file_name[entry->name_len] = '\0';   

                if (0 == strcmp(file_name, path))
                {
                    ReadInode(fd, entry->inode, group_descriptor, ret_inode);
                    free(block);
                    return 0;    
                }

                entry = (void*)entry + entry->rec_len;
                size += entry->rec_len;
            }
        }
        free(block);
    }
    return 1;
}

void PrintDataFromFileByPath(int fd, const char *path, struct ext2_group_desc *desc)
{
    char *string = malloc(strlen(path) + 1);
    char *token = NULL;
    struct ext2_inode inode;
    int inode_no = 1;

    strcpy(string, path);
    token = strtok(string, "/");

    ReadInode(fd, 2, desc,  &inode);
    while(NULL != token)
    {
        if (0 != Find_File_Dir(fd, desc, &inode, token, &inode))
        {
            fprintf(stderr, "ERROR %d\n", errno);
            free(string);
            return;
        } 
        ReadData(fd, &inode);
        token = strtok(NULL, "/");
    }
    free(string);
}

void ReadData(int fd, struct ext2_inode *inode)
{
    int i = 0;
    int block = 0;
    char buff[block_size];
    for(i = 0; i < 12 && inode->i_block[i]; i++)
    {
        block = inode->i_block[i];
        printf("block  %d\n", block);
        lseek(fd, block_size * block, SEEK_SET);
        read(fd, &buff, block_size); 
        printf("                        CONTENT: %s\n", buff);
    }
}