/*************************************************************************\
* Copyright (c) 2002 The University of Chicago, as Operator of Argonne
*     National Laboratory.
* Copyright (c) 2002 The Regents of the University of California, as
*     Operator of Los Alamos National Laboratory.
* EPICS BASE Versions 3.13.7
* and higher are distributed subject to a Software License Agreement found
* in file LICENSE that is included with this distribution. 
\*************************************************************************/
/* asTestRegister.c */
/* Author:  Marty Kraimer Date: 02MAY2000 */

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "asDbLib.h"
#include "asCa.h"
#define epicsExportSharedSymbols
#include "iocsh.h"
#include "asTestRegister.h"

/* asSetFilename */
static const iocshArg asSetFilenameArg0 = { "ascf",iocshArgString};
static const iocshArg * const asSetFilenameArgs[1] = {&asSetFilenameArg0};
static const iocshFuncDef asSetFilenameFuncDef =
    {"asSetFilename",1,asSetFilenameArgs};
static void asSetFilenameCallFunc(const iocshArgBuf *args)
{
    asSetFilename(args[0].sval);
}

/* asSetSubstitutions */
static const iocshArg asSetSubstitutionsArg0 = { "substitutions",iocshArgString};
static const iocshArg * const asSetSubstitutionsArgs[1] = {&asSetSubstitutionsArg0};
static const iocshFuncDef asSetSubstitutionsFuncDef =
    {"asSetSubstitutions",1,asSetSubstitutionsArgs};
static void asSetSubstitutionsCallFunc(const iocshArgBuf *args)
{
    asSetSubstitutions(args[0].sval);
}

/* asInit */
static const iocshFuncDef asInitFuncDef = {"asInit",0};
static void asInitCallFunc(const iocshArgBuf *args)
{
    asInit();
}

/* asdbdump */
static const iocshFuncDef asdbdumpFuncDef = {"asdbdump",0};
static void asdbdumpCallFunc(const iocshArgBuf *args)
{
    asdbdump();
}

/* aspuag */
static const iocshArg aspuagArg0 = { "uagname",iocshArgString};
static const iocshArg * const aspuagArgs[1] = {&aspuagArg0};
static const iocshFuncDef aspuagFuncDef = {"aspuag",1,aspuagArgs};
static void aspuagCallFunc(const iocshArgBuf *args)
{
    aspuag(args[0].sval);
}

/* asphag */
static const iocshArg asphagArg0 = { "hagname",iocshArgString};
static const iocshArg * const asphagArgs[1] = {&asphagArg0};
static const iocshFuncDef asphagFuncDef = {"asphag",1,asphagArgs};
static void asphagCallFunc(const iocshArgBuf *args)
{
    asphag(args[0].sval);
}

/* asprules */
static const iocshArg asprulesArg0 = { "asgname",iocshArgString};
static const iocshArg * const asprulesArgs[1] = {&asprulesArg0};
static const iocshFuncDef asprulesFuncDef = {"asprules",1,asprulesArgs};
static void asprulesCallFunc(const iocshArgBuf *args)
{
    asprules(args[0].sval);
}

/* aspmem */
static const iocshArg aspmemArg0 = { "asgname",iocshArgString};
static const iocshArg aspmemArg1 = { "clients",iocshArgInt};
static const iocshArg * const aspmemArgs[2] = {&aspmemArg0,&aspmemArg1};
static const iocshFuncDef aspmemFuncDef = {"aspmem",2,aspmemArgs};
static void aspmemCallFunc(const iocshArgBuf *args)
{
    aspmem(args[0].sval,args[1].ival);
}

/* astac */
static const iocshArg astacArg0 = { "recordname",iocshArgString};
static const iocshArg astacArg1 = { "user",iocshArgString};
static const iocshArg astacArg2 = { "location",iocshArgString};
static const iocshArg * const astacArgs[3] = {&astacArg0,&astacArg1,&astacArg2};
static const iocshFuncDef astacFuncDef = {"astac",3,astacArgs};
static void astacCallFunc(const iocshArgBuf *args)
{
    astac(args[0].sval,args[1].sval,args[2].sval);
}

/* ascar */
static const iocshArg ascarArg0 = { "level",iocshArgInt};
static const iocshArg * const ascarArgs[1] = {&ascarArg0};
static const iocshFuncDef ascarFuncDef = {"ascar",1,ascarArgs};
static void ascarCallFunc(const iocshArgBuf *args)
{
    ascar(args[0].ival);
}

static int * const pasCaDebug = &asCaDebug;
static struct iocshVarDef vardefs[] = {
    {"asCaDebug", iocshArgInt,(void *)&asCaDebug},
    {0,iocshArgInt,0}
};

void epicsShareAPI asTestRegister(void)
{
    iocshRegister(&asSetFilenameFuncDef,asSetFilenameCallFunc);
    iocshRegister(&asSetSubstitutionsFuncDef,asSetSubstitutionsCallFunc);
    iocshRegister(&asInitFuncDef,asInitCallFunc);
    iocshRegister(&asdbdumpFuncDef,asdbdumpCallFunc);
    iocshRegister(&aspuagFuncDef,aspuagCallFunc);
    iocshRegister(&asphagFuncDef,asphagCallFunc);
    iocshRegister(&asprulesFuncDef,asprulesCallFunc);
    iocshRegister(&aspmemFuncDef,aspmemCallFunc);
    iocshRegister(&astacFuncDef,astacCallFunc);
    iocshRegister(&ascarFuncDef,ascarCallFunc);
    iocshRegisterVariable(vardefs);
}
