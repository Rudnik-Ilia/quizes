#pragma once

#include <linux/fs.h>
#include <ext2fs/ext2fs.h>



void FindGroup(struct ext2_group_desc* group_block, int fd);