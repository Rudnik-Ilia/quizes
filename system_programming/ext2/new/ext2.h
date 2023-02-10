#pragma once
void FindGroupDescriptor(struct ext2_group_desc *group, int file);
void  ReadInode(int fd, int inode_no, struct  ext2_group_desc *group,  struct ext2_inode *inode);
void ReadData(int fd, struct ext2_inode *inode);
int FindDir(int fd, struct ext2_group_desc *group_descriptor, struct ext2_inode *inode, char *path, struct ext2_inode *ret_inode);
void PrintDataFromFileByPath(int fd, const char *path, struct ext2_group_desc *desc);


