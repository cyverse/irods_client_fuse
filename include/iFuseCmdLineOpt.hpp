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

#ifndef IFUSECMDLINEOPT_HPP
#define IFUSECMDLINEOPT_HPP

#include "iFuse.Lib.hpp"

// for Postgresql-iCAT only
//#define USE_CONNREUSE

#define IFUSE_CMD_ARG_MAX_TOKEN_LEN 30
#define MAX_PASSWORD_INPUT_LEN 100

typedef struct IFuseCmdArg {
    int start;
    int end;
    char command[IFUSE_CMD_ARG_MAX_TOKEN_LEN];
    char value[IFUSE_CMD_ARG_MAX_TOKEN_LEN];
} iFuseCmdArg_t;

void iFuseCmdOptsInit();
void iFuseCmdOptsDestroy();
int iFuseCmdOptsParse(int argc, char **argv);
void iFuseCmdOptsAdd(char *opt);
void iFuseGetOption(iFuseOpt_t *opt);
void iFuseGenCmdLineForFuse(int *fuse_argc, char ***fuse_argv);
void iFuseReleaseCmdLineForFuse(int fuse_argc, char **fuse_argv);

#endif	/* IFUSECMDLINEOPT_HPP */
