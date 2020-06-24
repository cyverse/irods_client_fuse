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

#ifndef IFUSE_LIB_CONN_HPP
#define IFUSE_LIB_CONN_HPP

#include <pthread.h>
#include <time.h>
#include "rodsClient.h"

#define IFUSE_MAX_NUM_CONN	10

#define IFUSE_CONN_TYPE_FOR_FILE_IO      0
#define IFUSE_CONN_TYPE_FOR_SHORTOP      1
#define IFUSE_CONN_TYPE_FOR_ONETIMEUSE   2

#define IFUSE_FREE_CONN_CHECK_INTERVAL_SEC  10
#define IFUSE_FREE_CONN_TIMEOUT_SEC         (60*5)
#define IFUSE_FREE_CONN_KEEPALIVE_SEC       (60*3)

typedef struct IFuseConn {
    unsigned long connId;
    int type;
    rcComm_t *conn;
    time_t lastActTime;
    time_t lastUseTime;
    int inuseCnt;
    pthread_rwlockattr_t lockAttr;
    pthread_rwlock_t lock;
} iFuseConn_t;

typedef struct IFuseFsConnReport {
    int inuseShortOpConn;
    int inuseConn;
    int inuseOnetimeuseConn;
    int freeShortopConn;
    int freeConn;
} iFuseFsConnReport_t;

/*
 * Usage pattern
 * - iFuseConnInit
 * - iFuseConnGetAndUse
 * - iFuseConnLock
 * - some operations
 * - iFuseConnUnlock
 * - iFuseConnUnuse
 * - iFuseConnDestroy
 */

int iFuseConnTest();
void iFuseConnInit();
void iFuseConnDestroy();
void iFuseConnReport(iFuseFsConnReport_t *report);
int iFuseConnGetAndUse(iFuseConn_t **iFuseConn, int connType);
int iFuseConnUnuse(iFuseConn_t *iFuseConn);
void iFuseConnUpdateLastActTime(iFuseConn_t *iFuseConn, bool lock);
int iFuseConnReconnect(iFuseConn_t *iFuseConn);
void iFuseConnLock(iFuseConn_t *iFuseConn);
void iFuseConnUnlock(iFuseConn_t *iFuseConn);

#endif	/* IFUSE_LIB_CONN_HPP */
