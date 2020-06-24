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

#ifndef IFUSE_LIB_METADATACACHE_HPP
#define IFUSE_LIB_METADATACACHE_HPP

#include <sys/stat.h>
#include <list>
#include <time.h>

#define IFUSE_METADATA_CACHE_TIMEOUT_SEC           (3*60)

typedef struct IFuseStatCache {
    char *iRodsPath;
    struct stat *stbuf;
    time_t timestamp;
} iFuseStatCache_t;

typedef struct IFuseDirCache {
    char *iRodsPath;
    std::list<char*> *entries;
    time_t timestamp;
} iFuseDirCache_t;

void iFuseMetadataCacheInit();
void iFuseMetadataCacheDestroy();
void iFuseMetadataCacheClear();
int iFuseMetadataCacheClearExpiredStat(bool force);
int iFuseMetadataCacheClearExpiredDir(bool force);
int iFuseMetadataCachePutStat(const char *iRodsPath, const struct stat *stbuf);
int iFuseMetadataCachePutStat2(const char *iRodsDirPath, const char *iRodsFilename, const struct stat *stbuf);
int iFuseMetadataCacheAddDirEntry(const char *iRodsPath, const char *iRodsFilename);
int iFuseMetadataCacheAddDirEntryIfFresh(const char *iRodsPath, const char *iRodsFilename);
int iFuseMetadataCacheAddDirEntryIfFresh2(const char *iRodsPath);
int iFuseMetadataCacheGetStat(const char *iRodsPath, struct stat *stbuf);
int iFuseMetadataCacheGetDirEntry(const char *iRodsPath, char **entries, unsigned int *bufferLen);
int iFuseMetadataCacheCheckExistanceOfDirEntry(const char *iRodsPath);
int iFuseMetadataCacheRemoveStat(const char *iRodsPath);
int iFuseMetadataCacheRemoveDir(const char *iRodsPath);
int iFuseMetadataCacheRemoveDirEntry(const char *iRodsPath, const char *iRodsFilename);
int iFuseMetadataCacheRemoveDirEntry2(const char *iRodsPath);

#endif	/* IFUSE_LIB_METADATACACHE_HPP */
