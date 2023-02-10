#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ext2fs/ext2fs.h> 
#include "ext2.h"

#define BASE_OFFSET 1024  
#define BLOCK_OFFSET(block) (block * block_size)

#define PATH "/dev/ram0"

int block_size = 0; 
int inode_table_offset_in_blocks = 0;

void FindGroupDescriptor(struct ext2_group_desc *group, int file) 
{
    struct ext2_super_block super_block = {0};
    file = open(PATH, O_RDONLY);
    
    if(file == -1)
    {
        perror("open is failed");
    }
    lseek(file, BASE_OFFSET, SEEK_SET);
    read(file, &super_block, sizeof(super_block)); 

    if (super_block.s_magic != EXT2_SUPER_MAGIC) 
    {
       fprintf(stderr, "failed %d", errno);
    }

    block_size =  1024 << super_block.s_log_block_size;
    printf("Block size: %d \n", block_size);
    printf("Block: %d \n",  super_block.s_blocks_count);
    printf("Reserved: %d \n", super_block.s_r_blocks_count);
    printf("Size of inode structure: %d\n", super_block.s_inode_size);

    lseek(file, block_size, SEEK_SET);
    read(file, group, sizeof(*group));   
}

void ReadInode(int fd, int inode_no, struct  ext2_group_desc *group,  struct ext2_inode *inode)
{
    lseek(fd, BLOCK_OFFSET(group->bg_inode_table) + (inode_no - 1) * 256, SEEK_SET);
	read(fd, inode, sizeof(struct ext2_inode));
}

int FindDir(int fd, struct ext2_group_desc *group_descriptor, struct ext2_inode *inode, char *path, struct ext2_inode *ret_inode)
{
    void* block;
    size_t i = 0;

    if(S_ISDIR(inode->i_mode))
    {
        struct ext2_dir_entry_2 * entry;
        size_t size = 0;

        block = malloc(sizeof(block_size));

        for(i = 0; i < EXT2_N_BLOCKS; ++i)
        {
            lseek(fd, BLOCK_OFFSET(inode->i_block[i]), SEEK_SET);
            read(fd, block, block_size); 
            entry = (struct ext2_dir_entry_2*)block;
       
            while((size < inode->i_size) && entry->inode)
            {
                char file_name[EXT2_NAME_LEN + 1];
                
                memcpy(file_name, entry->name, entry->name_len);
                file_name[entry->name_len] = '\0';   

                if (0 == strcmp(file_name, path))
                {
                    ReadInode(fd, entry->inode, group_descriptor, ret_inode);
                    free(block);
                    return 0;    
                }

                size += entry->rec_len;
                entry = (void*) entry + entry->rec_len;
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
    printf("inode size %d\n", inode.i_size);
    while(NULL != token)
    {
        puts("loop iteration");
        if (0 != FindDir(fd, desc, &inode, token, &inode))
        {
            
            perror("Find_File_Dir err");
            free(string);
            return;
        } 
        printf("inode size %d\n", inode.i_size);

        ReadData(fd, &inode);

        token = strtok(NULL, "/");
    }
    free(string);
}

void ReadData(int fd, struct ext2_inode *inode)
{
    int i = 0;
    int block;
    char *buff= malloc(sizeof(block_size));
    
    for(i = 0; i < 12 && inode->i_block[i]; i++)
    {
        block = inode->i_block[i];
        printf("block number: %d content: %d\n", i, block);
        lseek(fd, block_size * block, SEEK_SET);
        read(fd, buff, block_size); 
        printf("Content of file: %s", buff);
    }
    free(buff);
}

