/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/
/*
    Copyright 2020 The Trustees of University of Arizona and CyVerse

    Licensed under the Apache License, Version 2.0 (the "License" );
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef IFUSE_BUFFEREDFS_HPP
#define IFUSE_BUFFEREDFS_HPP

#include <pthread.h>
#include "iFuse.Lib.Fd.hpp"

#define IFUSE_BUFFER_CACHE_BLOCK_SIZE         (64*1024)

typedef struct IFuseBufferCache {
    unsigned long fdId;
    char *iRodsPath;
    off_t offset;
    size_t size;
    char *buffer;
} iFuseBufferCache_t;

void iFuseBufferedFSInit();
void iFuseBufferedFSDestroy();

size_t getBufferCacheBlockSize();
unsigned int getBlockID(off_t off);
off_t getBlockStartOffset(unsigned int blockID);
off_t getInBlockOffset(off_t off);

int iFuseBufferedFsGetAttr(const char *iRodsPath, struct stat *stbuf);
int iFuseBufferedFsOpen(const char *iRodsPath, iFuseFd_t **iFuseFd, int openFlag);
int iFuseBufferedFsClose(iFuseFd_t *iFuseFd);
int iFuseBufferedFsFlush(iFuseFd_t *iFuseFd);
int iFuseBufferedFsReadBlock(iFuseFd_t *iFuseFd, char *buf, unsigned int blockID);
int iFuseBufferedFsRead(iFuseFd_t *iFuseFd, char *buf, off_t off, size_t size);
int iFuseBufferedFsWrite(iFuseFd_t *iFuseFd, const char *buf, off_t off, size_t size);

#endif	/* IFUSE_BUFFEREDFS_HPP */
