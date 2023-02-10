#pragma once

#include <linux/fs.h>
#include <ext2fs/ext2fs.h>



void FindGroup(struct ext2_group_desc* group_block, int fd);
void ReadInode(int fd, int inode_no, struct  ext2_group_desc *group,  struct ext2_inode *inode);
int Find_File_Dir(int fd, struct ext2_group_desc *group_descriptor, struct ext2_inode *inode, const char *path, struct ext2_inode *ret_inode);


void ReadData(int fd, struct ext2_inode *inode);
void PrintDataFromFileByPath(int fd, const char *path, struct ext2_group_desc *desc);