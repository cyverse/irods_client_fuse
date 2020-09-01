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

#ifndef IFUSE_LIB_RODSCLIENTAPI_HPP
#define IFUSE_LIB_RODSCLIENTAPI_HPP

#include <pthread.h>
#include "rodsClient.h"
#include "iFuse.Lib.Util.hpp"

#define IFUSE_RODSCLIENTAPI_TIMEOUT_SEC     (90)


void iFuseRodsClientInit();
void iFuseRodsClientDestroy();

int iFuseRodsClientReadMsgError(int status);

rcComm_t *iFuseRodsClientConnect(const char *rodsHost, int rodsPort, const char *userName, const char *rodsZone, const char *clientUserName, const char *clientRodsZone, int reconnFlag, rErrMsg_t *errMsg);
int iFuseRodsClientLogin(rcComm_t *conn);
int iFuseRodsClientDisconnect(rcComm_t *conn);

int iFuseRodsClientMakeRodsPath(const char *path, char *iRodsPath);

int iFuseRodsClientSetSessionTicket(rcComm_t *conn, ticketAdminInp_t *ticketAdminInp);

int iFuseRodsClientDataObjOpen(rcComm_t *conn, dataObjInp_t *dataObjInp);
int iFuseRodsClientDataObjClose(rcComm_t *conn, openedDataObjInp_t *dataObjCloseInp);
int iFuseRodsClientOpenCollection( rcComm_t *conn, char *collection, int flag, collHandle_t *collHandle );
int iFuseRodsClientCloseCollection(collHandle_t *collHandle);
int iFuseRodsClientObjStat(rcComm_t *conn, dataObjInp_t *dataObjInp, rodsObjStat_t **rodsObjStatOut);
int iFuseRodsClientDataObjLseek(rcComm_t *conn, openedDataObjInp_t *dataObjLseekInp, fileLseekOut_t **dataObjLseekOut);
int iFuseRodsClientDataObjRead(rcComm_t *conn, openedDataObjInp_t *dataObjReadInp, bytesBuf_t *dataObjReadOutBBuf);
int iFuseRodsClientDataObjWrite(rcComm_t *conn, openedDataObjInp_t *dataObjWriteInp, bytesBuf_t *dataObjWriteInpBBuf);
int iFuseRodsClientDataObjCreate(rcComm_t *conn, dataObjInp_t *dataObjInp);
int iFuseRodsClientDataObjUnlink(rcComm_t *conn, dataObjInp_t *dataObjUnlinkInp);
int iFuseRodsClientReadCollection(rcComm_t *conn, collHandle_t *collHandle, collEnt_t *collEnt);
int iFuseRodsClientCollCreate(rcComm_t *conn, collInp_t *collCreateInp);
int iFuseRodsClientRmColl(rcComm_t *conn, collInp_t *rmCollInp, int vFlag);
int iFuseRodsClientDataObjRename(rcComm_t *conn, dataObjCopyInp_t *dataObjRenameInp);
int iFuseRodsClientDataObjTruncate(rcComm_t *conn, dataObjInp_t *dataObjInp);
int iFuseRodsClientModDataObjMeta(rcComm_t *conn, modDataObjMeta_t *modDataObjMetaInp);

#endif	/* IFUSE_LIB_RODSCLIENTAPI_HPP */
