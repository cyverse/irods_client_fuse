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

#ifndef IFUSE_LIB_UTIL_HPP
#define IFUSE_LIB_UTIL_HPP

#include <time.h>
#include <pthread.h>

#ifndef UNUSED
#define UNUSED(expr) (void)(expr)
#endif

#define IFUSE_LIB_LOG_PRINT_TIME
//#define IFUSE_LIB_LOG_OUT_TO_FILE
#define IFUSE_LIB_LOG_OUT_FILE_PATH   "/tmp/irods_debug.out"

#ifdef IFUSE_LIB_LOG_OUT_TO_FILE
#define iFuseLibLogBase(level, formatStr, ...)   \
    iFuseLibLogLock(); \
    iFuseLibLogToFile(level, formatStr, ## __VA_ARGS__); \
    iFuseLibLogUnlock()
#define iFuseLibLogErrorBase(level, errCode, formatStr, ...)   \
    iFuseLibLogLock(); \
    iFuseLibLogErrorToFile(level, errCode, formatStr, ## __VA_ARGS__); \
    iFuseLibLogUnlock()
#else
#   define iFuseLibLogBase       rodsLog
#   define iFuseLibLogErrorBase  rodsLogError
#endif

#ifdef IFUSE_LIB_LOG_PRINT_TIME
#   define iFuseLibLog \
    { \
    char logtimes[100]; \
    iFuseLibGetStrCurrentTime(logtimes); \
    iFuseLibLogBase(LOG_DEBUG, "%s", logtimes); \
    } \
    iFuseLibLogBase
#else
#   define iFuseLibLog   iFuseLibLogBase
#endif

#ifdef IFUSE_LIB_LOG_PRINT_TIME
#   define iFuseLibLogError \
    { \
    char logtimes[100]; \
    iFuseLibGetStrCurrentTime(logtimes); \
    iFuseLibLogBase(LOG_DEBUG, "%s", logtimes); \
    } \
    iFuseLibLogErrorBase
#else
#   define iFuseLibLogError  iFuseLibLogErrorBase
#endif

void iFuseUtilInit();
void iFuseUtilDestroy();

int iFuseUtilStricmp (const char *s1, const char *s2);
time_t iFuseLibGetCurrentTime();
void iFuseLibGetStrCurrentTime(char *buff);
void iFuseLibGetStrTime(time_t time, char *buff);
double iFuseLibDiffTimeSec(time_t end, time_t beginning);
int iFuseLibSplitPath(const char *srcPath, char *dir, unsigned int maxDirLen, char *file, unsigned int maxFileLen);
int iFuseLibJoinPath(const char *dir, const char *file, char *destPath, unsigned int maxDestPathLen);
int iFuseLibGetFilename(const char *srcPath, char *file, unsigned int maxFileLen);

void iFuseLibLogToFile(int level, const char *formatStr, ...);
void iFuseLibLogErrorToFile(int level, int errCode, char *formatStr, ...);
void iFuseLibLogLock();
void iFuseLibLogUnlock();

#endif	/* IFUSE_LIB_UTIL_HPP */
