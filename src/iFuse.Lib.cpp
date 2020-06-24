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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>
#include <list>
#include <unistd.h>
#include "iFuse.Lib.hpp"
#include "iFuse.Lib.RodsClientAPI.hpp"
#include "iFuse.Lib.Conn.hpp"
#include "iFuse.Lib.Fd.hpp"
#include "iFuse.Lib.MetadataCache.hpp"
#include "iFuse.Lib.Util.hpp"
#include "rodsClient.h"

static rodsEnv g_iFuseEnv;
static iFuseOpt_t g_iFuseOpt;

static pthread_rwlock_t g_TimerHandlerLock;
static pthread_rwlockattr_t g_TimerHandlerLockAttr;
static std::list<iFuseLibTimerHandlerCB> g_TimerHandlers;

static pthread_t g_Timer;
static bool g_TimerRunning;

static void* _timerTick(void* param) {
    std::list<iFuseLibTimerHandlerCB>::iterator it_cb;
    iFuseLibTimerHandlerCB callback;

    UNUSED(param);

    iFuseLibLog(LOG_DEBUG, "_timerTick: timer is running");

    while(g_TimerRunning) {
        //iFuseLibLog(LOG_DEBUG, "_timerTick: calling timer handlers");

        pthread_rwlock_rdlock(&g_TimerHandlerLock);

        // iterate list
        for(it_cb=g_TimerHandlers.begin();it_cb!=g_TimerHandlers.end();it_cb++) {
            callback = *it_cb;

            //iFuseLibLog(LOG_DEBUG, "_timerTick: calling a timer handler %p", callback);
            callback();
        }

        pthread_rwlock_unlock(&g_TimerHandlerLock);

        //iFuseLibLog(LOG_DEBUG, "_timerTick: called all timer handlers, sleep 1sec");

        usleep(1000);
    }

    iFuseLibLog(LOG_DEBUG, "_timerTick: timer is stopped");

    return NULL;
}

rodsEnv *iFuseLibGetRodsEnv() {
    return &g_iFuseEnv;
}

void iFuseLibSetRodsEnv(rodsEnv *pEnv) {
    memcpy(&g_iFuseEnv, pEnv, sizeof(rodsEnv));
}

iFuseOpt_t *iFuseLibGetOption() {
    return &g_iFuseOpt;
}

void iFuseLibSetOption(iFuseOpt_t *pOpt) {
    memcpy(&g_iFuseOpt, pOpt, sizeof(iFuseOpt_t));
}

void iFuseLibInit() {
    // timer
    pthread_rwlockattr_init(&g_TimerHandlerLockAttr);
    pthread_rwlock_init(&g_TimerHandlerLock, &g_TimerHandlerLockAttr);

    iFuseUtilInit();

    iFuseRodsClientInit();
    iFuseConnInit();

    iFuseFdInit();

    iFuseMetadataCacheInit();
}

void iFuseLibDestroy() {
    iFuseMetadataCacheDestroy();

    iFuseFdDestroy();

    iFuseConnDestroy();
    iFuseRodsClientDestroy();

    iFuseUtilDestroy();

    pthread_rwlock_destroy(&g_TimerHandlerLock);
    pthread_rwlockattr_destroy(&g_TimerHandlerLockAttr);
}

void iFuseLibInitTimerThread() {
    // should be called in FUSE_INIT to avoid dead-lock issue in FUSE
    g_TimerRunning = true;
    pthread_create(&g_Timer, NULL, _timerTick, NULL);
}

void iFuseLibTerminateTimerThread() {
    g_TimerRunning = false;
    pthread_join(g_Timer, NULL);
}

void iFuseLibSetTimerTickHandler(iFuseLibTimerHandlerCB callback) {
    pthread_rwlock_wrlock(&g_TimerHandlerLock);

    g_TimerHandlers.push_back(callback);

    pthread_rwlock_unlock(&g_TimerHandlerLock);
}

void iFuseLibUnsetTimerTickHandler(iFuseLibTimerHandlerCB callback) {
    pthread_rwlock_wrlock(&g_TimerHandlerLock);

    g_TimerHandlers.remove(callback);

    pthread_rwlock_unlock(&g_TimerHandlerLock);
}
