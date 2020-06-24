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

#ifndef IFUSE_PRELOAD_HPP
#define IFUSE_PRELOAD_HPP

#include <list>
#include <pthread.h>
#include "iFuse.BufferedFS.hpp"
#include "iFuse.Lib.Fd.hpp"

#define IFUSE_PRELOAD_PBLOCK_NUM             3
#define IFUSE_PRELOAD_THREAD_NUM             3
#define IFUSE_PRELOAD_MAX_PBLOCK_NUM         10
#define IFUSE_PRELOAD_MAX_THREAD_NUM         10

#define IFUSE_PRELOAD_PBLOCK_STATUS_INIT                 0
#define IFUSE_PRELOAD_PBLOCK_STATUS_RUNNING              1
#define IFUSE_PRELOAD_PBLOCK_STATUS_COMPLETED            2
#define IFUSE_PRELOAD_PBLOCK_STATUS_TASK_FAILED          3
#define IFUSE_PRELOAD_PBLOCK_STATUS_CREATION_FAILED      4

typedef struct IFusePreloadPBlock {
    iFuseFd_t *fd;
    unsigned int blockID;
    int status;
    bool threadJoined;
    pthread_t thread;
    pthread_rwlockattr_t lockAttr;
    pthread_rwlock_t lock;
} iFusePreloadPBlock_t;

typedef struct IFusePreload {
    unsigned long fdId;
    char *iRodsPath;
    std::list<iFusePreloadPBlock_t*> *pblocks;
    pthread_rwlockattr_t lockAttr;
    pthread_rwlock_t lock;
} iFusePreload_t;

typedef struct IFusePreloadThreadParam {
    iFusePreload_t *preload;
    iFusePreloadPBlock_t *pblock;
} iFusePreloadThreadParam_t;

void iFusePreloadInit();
void iFusePreloadDestroy();

int iFusePreloadOpen(const char *iRodsPath, iFuseFd_t **iFuseFd, int openFlag);
int iFusePreloadClose(iFuseFd_t *iFuseFd);
int iFusePreloadRead(iFuseFd_t *iFuseFd, char *buf, off_t off, size_t size);

#endif	/* IFUSE_PRELOAD_HPP */
