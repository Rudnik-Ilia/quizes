#pragma once

#include <linux/fs.h>
#include <ext2fs/ext2fs.h>



void FindGroup(struct ext2_group_desc* group_block, int fd);
void Read_Inode(int fd, int inode_no, struct  ext2_group_desc *group,  struct ext2_inode *inode);