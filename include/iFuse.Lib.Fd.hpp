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

#ifndef IFUSE_LIB_FD_HPP
#define IFUSE_LIB_FD_HPP

#include <pthread.h>
#include "iFuse.Lib.Conn.hpp"
#include "rodsClient.h"

typedef struct IFuseFd {
    unsigned long fdId;
    int fd;
    iFuseConn_t *conn;
    char *iRodsPath;
    int openFlag;
    off_t lastFilePointer;
    pthread_rwlockattr_t lockAttr;
    pthread_rwlock_t lock;
} iFuseFd_t;

typedef struct IFuseDir {
    unsigned long ddId;
    collHandle_t *handle;
    iFuseConn_t *conn;
    char *iRodsPath;
    char *cachedEntries;
    unsigned int cachedEntryBufferLen;
    pthread_rwlockattr_t lockAttr;
    pthread_rwlock_t lock;
} iFuseDir_t;

void iFuseFdInit();
void iFuseFdDestroy();
int iFuseFdOpen(iFuseFd_t **iFuseFd, iFuseConn_t *iFuseConn, const char* iRodsPath, int openFlag);
int iFuseFdReopen(iFuseFd_t *iFuseFd);
int iFuseDirOpen(iFuseDir_t **iFuseDir, iFuseConn_t *iFuseConn, const char* iRodsPath);
int iFuseDirOpenWithCache(iFuseDir_t **iFuseDir, const char* iRodsPath, const char* cachedEntries, unsigned int entryBufferLen);
int iFuseFdClose(iFuseFd_t *iFuseFd);
int iFuseDirClose(iFuseDir_t *iFuseDir);
void iFuseFdLock(iFuseFd_t *iFuseFd);
void iFuseDirLock(iFuseDir_t *iFuseDir);
void iFuseFdUnlock(iFuseFd_t *iFuseFd);
void iFuseDirUnlock(iFuseDir_t *iFuseDir);

#endif	/* IFUSE_LIB_FD_HPP */
