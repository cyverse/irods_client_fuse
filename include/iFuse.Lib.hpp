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

#ifndef IFUSE_LIB_HPP
#define IFUSE_LIB_HPP

#include "rodsClient.h"

typedef struct IFuseExtendedOpt {
    bool fuse;
    char *opt;
    struct IFuseExtendedOpt *next;
} iFuseExtendedOpt_t;

typedef struct IFuseOpt {
    char *program;
    bool help;
    bool version;
    bool debug;
    bool nonempty;
    bool foreground;
    bool directio;
    bool bufferedFS;
    bool preload;
    bool cacheMetadata;
    int maxConn;
    int blocksize;
    bool connReuse;
    int connTimeoutSec;
    int connKeepAliveSec;
    int connCheckIntervalSec;
    int rodsapiTimeoutSec;
    int preloadNumThreads;
    int preloadNumBlocks;
    int metadataCacheTimeoutSec;
    char *host;
    int port;
    char *zone;
    char *user;
    char *password;
    char *defResource;
    char *ticket;
    char *workdir;
    char *mountpoint;
    iFuseExtendedOpt_t *extendedOpts;
} iFuseOpt_t;

typedef void (*iFuseLibTimerHandlerCB) ();

rodsEnv *iFuseLibGetRodsEnv();
void iFuseLibSetRodsEnv(rodsEnv *pEnv);
iFuseOpt_t *iFuseLibGetOption();
void iFuseLibSetOption(iFuseOpt_t *pOpt);

void iFuseLibInit();
void iFuseLibDestroy();

void iFuseLibInitTimerThread();
void iFuseLibTerminateTimerThread();
void iFuseLibSetTimerTickHandler(iFuseLibTimerHandlerCB callback);
void iFuseLibUnsetTimerTickHandler(iFuseLibTimerHandlerCB callback);

#endif	/* IFUSE_LIB_HPP */
