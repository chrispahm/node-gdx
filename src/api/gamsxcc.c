/*  C code generated by apiwrapper for GAMS Version 25.1.2
 *  Copyright (c) 2016, GAMS Development Corp.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>

#define GAMSX_MAIN
#include "gamsxcc.h"

#if defined(_WIN32)
# include <windows.h>
  static char winErr[] = "Windows error";
  typedef HINSTANCE soHandle_t;
#else
# include <unistd.h>
# include <dlfcn.h>
# include <sys/utsname.h>
  typedef void *soHandle_t;
#endif

static soHandle_t h;
static int isLoaded = 0;
static int objectCount = 0;
static int ScreenIndicator = 1;
static int ExceptionIndicator = 0;
static int ExitIndicator = 1;
static gamsxErrorCallback_t ErrorCallBack = NULL;
static int APIErrorCount = 0;

#if defined(HAVE_MUTEX)
#include "gcmt.h"
static GC_mutex_t libMutex;
static GC_mutex_t objMutex;
static GC_mutex_t exceptMutex;

static int MutexIsInitialized = 0;

void gamsxInitMutexes(void)
{
  int rc;
  if (0==MutexIsInitialized) {
    rc = GC_mutex_init (&libMutex);     if(0!=rc) gamsxErrorHandling("Problem initializing libMutex");
    rc = GC_mutex_init (&objMutex);     if(0!=rc) gamsxErrorHandling("Problem initializing objMutex");
    rc = GC_mutex_init (&exceptMutex);  if(0!=rc) gamsxErrorHandling("Problem initializing exceptMutex");
    MutexIsInitialized = 1;
  }
}

void gamsxFiniMutexes(void)
{
  if (1==MutexIsInitialized) {
    GC_mutex_delete (&libMutex);
    GC_mutex_delete (&objMutex);
    GC_mutex_delete (&exceptMutex);
    MutexIsInitialized = 0;
  }
}
#  define lock(MUTEX)   if(MutexIsInitialized) GC_mutex_lock (&MUTEX);
#  define unlock(MUTEX) if(MutexIsInitialized) GC_mutex_unlock (&MUTEX);
#else
#  define lock(MUTEX)   ;
#  define unlock(MUTEX) ;
void gamsxInitMutexes(void) {}
void gamsxFiniMutexes(void) {}
#endif

#if !defined(GAMS_UNUSED)
#define GAMS_UNUSED(x) (void)x;
#endif

typedef void (GAMSX_CALLCONV *XCreate_t) (gamsxHandle_t *pgamsx);
static GAMSX_FUNCPTR(XCreate);
typedef void (GAMSX_CALLCONV *XFree_t)   (gamsxHandle_t *pgamsx);
static GAMSX_FUNCPTR(XFree);
typedef int (GAMSX_CALLCONV *XAPIVersion_t) (int api, char *msg, int *cl);
static GAMSX_FUNCPTR(XAPIVersion);
typedef int (GAMSX_CALLCONV *XCheck_t) (const char *ep, int nargs, int s[], char *msg);
static GAMSX_FUNCPTR(XCheck);

#define printNoReturn(f,nargs) { \
  char d_msgBuf[256]; \
  strcpy(d_msgBuf,#f " could not be loaded: "); \
  XCheck(#f,nargs,d_s,d_msgBuf+strlen(d_msgBuf)); \
  gamsxErrorHandling(d_msgBuf); \
}
#define printAndReturn(f,nargs,rtype) { \
  char d_msgBuf[256]; \
  strcpy(d_msgBuf,#f " could not be loaded: "); \
  XCheck(#f,nargs,d_s,d_msgBuf+strlen(d_msgBuf)); \
  gamsxErrorHandling(d_msgBuf); \
  return (rtype) 0; \
}

int  GAMSX_CALLCONV d_gamsxRunExecDLL (gamsxHandle_t pgamsx, void *optPtr, const char *sysDir, int AVerbose, char *Msg)
{
  int d_s[]={3,1,11,3,12};
  GAMS_UNUSED(pgamsx)
  GAMS_UNUSED(optPtr)
  GAMS_UNUSED(sysDir)
  GAMS_UNUSED(AVerbose)
  GAMS_UNUSED(Msg)
  printAndReturn(gamsxRunExecDLL,4,int )
}

int  GAMSX_CALLCONV d_gamsxShowError (gamsxHandle_t pgamsx, const char *fNameLog, char *errorLine, char *errorTyp, char *gmsLine)
{
  int d_s[]={15,11,12,12,12};
  GAMS_UNUSED(pgamsx)
  GAMS_UNUSED(fNameLog)
  GAMS_UNUSED(errorLine)
  GAMS_UNUSED(errorTyp)
  GAMS_UNUSED(gmsLine)
  printAndReturn(gamsxShowError,4,int )
}

void  GAMSX_CALLCONV d_gamsxAddBreakPoint (gamsxHandle_t pgamsx, const char *fn, int lineNr)
{
  int d_s[]={0,11,3};
  GAMS_UNUSED(pgamsx)
  GAMS_UNUSED(fn)
  GAMS_UNUSED(lineNr)
  printNoReturn(gamsxAddBreakPoint,2)
}

void  GAMSX_CALLCONV d_gamsxClearBreakPoints (gamsxHandle_t pgamsx)
{
  int d_s[]={0};
  GAMS_UNUSED(pgamsx)
  printNoReturn(gamsxClearBreakPoints,0)
}

int  GAMSX_CALLCONV d_gamsxSystemInfo (gamsxHandle_t pgamsx, int *NrSy, int *NrUel)
{
  int d_s[]={3,21,21};
  GAMS_UNUSED(pgamsx)
  GAMS_UNUSED(NrSy)
  GAMS_UNUSED(NrUel)
  printAndReturn(gamsxSystemInfo,2,int )
}

int  GAMSX_CALLCONV d_gamsxSymbolInfo (gamsxHandle_t pgamsx, int SyNr, char *SyName, char *SyExplTxt, int *SyDim, int *SyTyp, int *SyCount, int *SyUserInfo)
{
  int d_s[]={3,3,12,12,21,21,21,21};
  GAMS_UNUSED(pgamsx)
  GAMS_UNUSED(SyNr)
  GAMS_UNUSED(SyName)
  GAMS_UNUSED(SyExplTxt)
  GAMS_UNUSED(SyDim)
  GAMS_UNUSED(SyTyp)
  GAMS_UNUSED(SyCount)
  GAMS_UNUSED(SyUserInfo)
  printAndReturn(gamsxSymbolInfo,7,int )
}

char * GAMSX_CALLCONV d_gamsxUelName (gamsxHandle_t pgamsx, int uel, char *buf)
{
  int d_s[]={12,3};
  GAMS_UNUSED(pgamsx)
  GAMS_UNUSED(uel)
  GAMS_UNUSED(buf)
  printAndReturn(gamsxUelName,1,char *)
}

int  GAMSX_CALLCONV d_gamsxFindSymbol (gamsxHandle_t pgamsx, const char *SyName)
{
  int d_s[]={3,11};
  GAMS_UNUSED(pgamsx)
  GAMS_UNUSED(SyName)
  printAndReturn(gamsxFindSymbol,1,int )
}

int  GAMSX_CALLCONV d_gamsxDataReadRawStart (gamsxHandle_t pgamsx, int SyNr, int *SyCount)
{
  int d_s[]={3,3,21};
  GAMS_UNUSED(pgamsx)
  GAMS_UNUSED(SyNr)
  GAMS_UNUSED(SyCount)
  printAndReturn(gamsxDataReadRawStart,2,int )
}

int  GAMSX_CALLCONV d_gamsxDataReadRaw (gamsxHandle_t pgamsx, int Elements[], double Vals[], int *FDim)
{
  int d_s[]={3,52,54,21};
  GAMS_UNUSED(pgamsx)
  GAMS_UNUSED(Elements)
  GAMS_UNUSED(Vals)
  GAMS_UNUSED(FDim)
  printAndReturn(gamsxDataReadRaw,3,int )
}

int  GAMSX_CALLCONV d_gamsxDataReadDone (gamsxHandle_t pgamsx)
{
  int d_s[]={3};
  GAMS_UNUSED(pgamsx)
  printAndReturn(gamsxDataReadDone,0,int )
}

int  GAMSX_CALLCONV d_gamsxDataWriteRawStart (gamsxHandle_t pgamsx, int SyNr, int DoMerge)
{
  int d_s[]={3,3,15};
  GAMS_UNUSED(pgamsx)
  GAMS_UNUSED(SyNr)
  GAMS_UNUSED(DoMerge)
  printAndReturn(gamsxDataWriteRawStart,2,int )
}

int  GAMSX_CALLCONV d_gamsxDataWriteRaw (gamsxHandle_t pgamsx, const int Elements[], const double Vals[])
{
  int d_s[]={3,51,53};
  GAMS_UNUSED(pgamsx)
  GAMS_UNUSED(Elements)
  GAMS_UNUSED(Vals)
  printAndReturn(gamsxDataWriteRaw,2,int )
}

int  GAMSX_CALLCONV d_gamsxDataWriteDone (gamsxHandle_t pgamsx)
{
  int d_s[]={3};
  GAMS_UNUSED(pgamsx)
  printAndReturn(gamsxDataWriteDone,0,int )
}

void  GAMSX_CALLCONV d_gamsxRegisterCB1 (gamsxHandle_t pgamsx, TBrkPCallBack1_t CB1, void *userMem)
{
  int d_s[]={0,59,1};
  GAMS_UNUSED(pgamsx)
  GAMS_UNUSED(CB1)
  GAMS_UNUSED(userMem)
  printNoReturn(gamsxRegisterCB1,2)
}

void  GAMSX_CALLCONV d_gamsxRegisterCB2 (gamsxHandle_t pgamsx, TBrkPCallBack2_t CB2, void *userMem1, void *userMem2)
{
  int d_s[]={0,59,1,1};
  GAMS_UNUSED(pgamsx)
  GAMS_UNUSED(CB2)
  GAMS_UNUSED(userMem1)
  GAMS_UNUSED(userMem2)
  printNoReturn(gamsxRegisterCB2,3)
}

TBrkPCallBack1_t GAMSX_CALLCONV d_gamsxGetCB1 (gamsxHandle_t pgamsx)
{
  int d_s[]={59};
  GAMS_UNUSED(pgamsx)
  printAndReturn(gamsxGetCB1,0,TBrkPCallBack1_t)
}

TBrkPCallBack2_t GAMSX_CALLCONV d_gamsxGetCB2 (gamsxHandle_t pgamsx)
{
  int d_s[]={59};
  GAMS_UNUSED(pgamsx)
  printAndReturn(gamsxGetCB2,0,TBrkPCallBack2_t)
}

void * GAMSX_CALLCONV d_gamsxGetCB1UM (gamsxHandle_t pgamsx)
{
  int d_s[]={1};
  GAMS_UNUSED(pgamsx)
  printAndReturn(gamsxGetCB1UM,0,void *)
}

void * GAMSX_CALLCONV d_gamsxGetCB2UM1 (gamsxHandle_t pgamsx)
{
  int d_s[]={1};
  GAMS_UNUSED(pgamsx)
  printAndReturn(gamsxGetCB2UM1,0,void *)
}

void * GAMSX_CALLCONV d_gamsxGetCB2UM2 (gamsxHandle_t pgamsx)
{
  int d_s[]={1};
  GAMS_UNUSED(pgamsx)
  printAndReturn(gamsxGetCB2UM2,0,void *)
}

void GAMSX_CALLCONV d_gamsxSWSet (gamsxHandle_t pgamsx, const int x)
{
  int d_s[]={0,3};
  GAMS_UNUSED(pgamsx)
  GAMS_UNUSED(x)
  printNoReturn(gamsxSWSet,1)
}

int  GAMSX_CALLCONV d_gamsxStepThrough (gamsxHandle_t pgamsx)
{
  int d_s[]={15};
  GAMS_UNUSED(pgamsx)
  printAndReturn(gamsxStepThrough,0,int )
}

void GAMSX_CALLCONV d_gamsxStepThroughSet (gamsxHandle_t pgamsx, const int x)
{
  int d_s[]={0,15};
  GAMS_UNUSED(pgamsx)
  GAMS_UNUSED(x)
  printNoReturn(gamsxStepThroughSet,1)
}

int  GAMSX_CALLCONV d_gamsxRunToEnd (gamsxHandle_t pgamsx)
{
  int d_s[]={15};
  GAMS_UNUSED(pgamsx)
  printAndReturn(gamsxRunToEnd,0,int )
}

void GAMSX_CALLCONV d_gamsxRunToEndSet (gamsxHandle_t pgamsx, const int x)
{
  int d_s[]={0,15};
  GAMS_UNUSED(pgamsx)
  GAMS_UNUSED(x)
  printNoReturn(gamsxRunToEndSet,1)
}

int  GAMSX_CALLCONV d_gamsxCB1Defined (gamsxHandle_t pgamsx)
{
  int d_s[]={15};
  GAMS_UNUSED(pgamsx)
  printAndReturn(gamsxCB1Defined,0,int )
}

int  GAMSX_CALLCONV d_gamsxCB2Defined (gamsxHandle_t pgamsx)
{
  int d_s[]={15};
  GAMS_UNUSED(pgamsx)
  printAndReturn(gamsxCB2Defined,0,int )
}

/* return dirName on success, NULL on failure */
static char *
extractFileDirFileName (const char *fileName, char *dirName, char *fName)
{
  int fileNameLen, shave=0;
  const char *end, *s;
  char *t;

  if (NULL == fileName || NULL == dirName || fName == NULL) {
    return NULL;
  }
  fileNameLen = (int) strlen(fileName);

#if defined(_WIN32)
  /* get the last delimiter */
  for (end = fileName + fileNameLen - 1;
       end >= fileName && '\\' != *end && ':' != *end;  end--);
  /* shave off the trailing delimiter if:
   *  it isn't the first char,
   *  it is a backslash, and
   *  it is not preceded by a delimiter
   */
  if (end > fileName && '\\' == *end
   && (! ('\\' == *(end-1) || ':' == *(end-1)))
     ) {
    end--; shave=1;
  }
#else
  /* non-Windows: implicitly, this is the Unix version */
  /* get the last delimiter */
  for (end = fileName + fileNameLen - 1;
       end >= fileName && '/' != *end;  end--);

  if (end > fileName && '/' == *end) {
    end--; shave=1;
  }
#endif  /* if defined(_WIN32) */

  for (s = fileName, t = dirName;  s <= end;  s++, t++)
    *t = *s;
  *t = '\0';

  if (shave) s++;
  for (t = fName;  s <= fileName + fileNameLen - 1;  s++, t++)
    *t = *s;
  *t = '\0';

  return dirName;
} /* extractFileDirFileName */

static soHandle_t
loadLib (const char *libName, char **errMsg)
{
  soHandle_t h;

#if defined(_WIN32)
#if defined(UNICODE) || defined (_UNICODE)
  h = LoadLibraryA(libName);
#else
  h = LoadLibrary(libName);
#endif
  if (NULL == h) {
    *errMsg = winErr;
  }
  else {
    *errMsg = NULL;
  }
#else
  (void) dlerror();
  h = dlopen (libName, RTLD_NOW);
  if (NULL == h) {
    *errMsg = dlerror();
  }
  else {
    *errMsg = NULL;
  }
#endif

  return h;
} /* loadLib */

static int
unLoadLib (soHandle_t hh)
{
  int rc;

#if defined(_WIN32)
  rc = FreeLibrary (hh);
  return ! rc;
#else
  rc = dlclose (hh);
#endif
  return rc;
} /* unLoadLib */

static void *
loadSym (soHandle_t h, const char *sym, char **errMsg)
{
  void *s;
  const char *from;
  char *to;
  const char *tripSym;
  char lcbuf[257];
  char ucbuf[257];
  size_t symLen;
  int trip;

  /* search in this order:
   *  1. lower
   *  2. original
   *  3. upper
   */

  symLen = 0;
  for (trip = 1;  trip <= 3;  trip++) {
    switch (trip) {
    case 1:                             /* lower */
      for (from = sym, to = lcbuf;  *from;  from++, to++) {
        *to = tolower(*from);
      }
      symLen = from - sym;
      lcbuf[symLen] = '\0';
      tripSym = lcbuf;
      break;
    case 2:                             /* original */
      tripSym = sym;
      break;
    case 3:                             /* upper */
      for (from = sym, to = ucbuf;  *from;  from++, to++) {
        *to = toupper(*from);
      }
      ucbuf[symLen] = '\0';
      tripSym = ucbuf;
      break;
    default:
      tripSym = sym;
    } /* end switch */
#if defined(_WIN32)
#  if defined(HAVE_INTPTR_T)
    s = (void *)(intptr_t)GetProcAddress (h, tripSym);
#  else
    s = (void *)GetProcAddress (h, tripSym);
#  endif
    *errMsg = NULL;
    if (NULL != s) {
      return s;
    }
#else
    (void) dlerror();
    s = dlsym (h, tripSym);
    *errMsg = dlerror();
    if (NULL == *errMsg) {
      return s;
    }
#endif
  } /* end loop over symbol name variations */

  return NULL;
} /* loadSym */

/* TNAME = type name, ENAME = exported name */
#if defined(HAVE_INTPTR_T)
#  define LOADIT(TNAME,ENAME) symName = ENAME; TNAME = (TNAME##_t) (intptr_t) loadSym (h, symName, &errMsg); if (NULL == TNAME) goto symMissing
#  define LOADIT_ERR_OK(TNAME,ENAME) symName = ENAME; TNAME = (TNAME##_t) (intptr_t) loadSym (h, symName, &errMsg)
#else
#  define LOADIT(TNAME,ENAME) symName = ENAME; TNAME = (TNAME##_t) loadSym (h, symName, &errMsg); if (NULL == TNAME) goto symMissing
#  define LOADIT_ERR_OK(TNAME,ENAME) symName = ENAME; TNAME = (TNAME##_t) loadSym (h, symName, &errMsg)
#endif

#if ! defined(GMS_DLL_BASENAME)
# define GMS_DLL_BASENAME "gamsxdclib"
#endif
#if defined(_WIN32)
# if ! defined(GMS_DLL_PREFIX)
#  define GMS_DLL_PREFIX ""
# endif
# if ! defined(GMS_DLL_EXTENSION)
#  define GMS_DLL_EXTENSION ".dll"
# endif
# if ! defined(GMS_DLL_SUFFIX)
#  if defined(_WIN64)
#   define GMS_DLL_SUFFIX "64"
#  else
#   define GMS_DLL_SUFFIX ""
#  endif
# endif

#else  /* start non-Windows */

# if ! defined(GMS_DLL_PREFIX)
#  define GMS_DLL_PREFIX "lib"
# endif
# if ! defined(GMS_DLL_EXTENSION)
#  if defined(__APPLE__)
#   define GMS_DLL_EXTENSION ".dylib"
#  else
#   define GMS_DLL_EXTENSION ".so"
#  endif
# endif
# if ! defined(GMS_DLL_SUFFIX)
#  if defined(__WORDSIZE)
#   if 64 == __WORDSIZE
#    define GMS_DLL_SUFFIX "64"
#   else
#    define GMS_DLL_SUFFIX ""
#   endif
#  elif defined(__SIZEOF_POINTER__)
#   if 4 == __SIZEOF_POINTER__
#    define GMS_DLL_SUFFIX ""
#   elif 8 == __SIZEOF_POINTER__
#    define GMS_DLL_SUFFIX "64"
#   endif
#  elif defined(__sparcv9)
#   define GMS_DLL_SUFFIX "64"
#  elif defined(__sparc)
/*  check __sparc after __sparcv9, both are defined for 64-bit */
#   define GMS_DLL_SUFFIX ""
#  endif
# endif /* ! defined(GMS_DLL_SUFFIX) */
#endif

/* XLibraryLoad: return 0 on success, ~0 on failure */
static int
XLibraryLoad (const char *dllName, char *errBuf, int errBufSize)
{
  char *errMsg;
  const char *symName;
  int rc, cl;

  if (isLoaded)
    return 0;
  h = loadLib (dllName, &errMsg);
  if (NULL == h) {
    if (NULL != errBuf) {
      int elen;
      char* ebuf;
      elen = errBufSize;  ebuf = errBuf;
      rc = sprintf (ebuf, "%.*s", elen, "Could not load shared library ");
      elen -= rc;  ebuf+= rc;
      rc = sprintf (ebuf, "%.*s", elen, dllName);
      elen -= rc;  ebuf+= rc;
      rc = sprintf (ebuf, "%.*s", elen, ": ");
      elen -= rc;  ebuf+= rc;
      rc = sprintf (ebuf, "%.*s", elen, errMsg);
      /* elen -= rc;  ebuf+= rc; */
      errBuf[errBufSize-1] = '\0';
    }
    return 1;
  }
  else {
     /* printf ("Loaded shared library %s successfully\n", dllName); */
    if (errBuf && errBufSize)
      errBuf[0] = '\0';
  }

  LOADIT(XCreate, "XCreate");
  LOADIT(XFree, "XFree");
  LOADIT(XCheck, "CXCheck");
  LOADIT(XAPIVersion, "CXAPIVersion");

  if (!XAPIVersion(1,errBuf,&cl))
    return 1;


#define CheckAndLoad(f,nargs,prefix) \
  if (!XCheck(#f,nargs,s,errBuf)) \
    f = &d_##f; \
  else { \
    LOADIT(f,prefix #f); \
  }
  {int s[]={3,1,11,3,12}; CheckAndLoad(gamsxRunExecDLL,4,"C"); }
  {int s[]={15,11,12,12,12}; CheckAndLoad(gamsxShowError,4,"C"); }
  {int s[]={0,11,3}; CheckAndLoad(gamsxAddBreakPoint,2,"C"); }
  {int s[]={0}; CheckAndLoad(gamsxClearBreakPoints,0,""); }
  {int s[]={3,21,21}; CheckAndLoad(gamsxSystemInfo,2,""); }
  {int s[]={3,3,12,12,21,21,21,21}; CheckAndLoad(gamsxSymbolInfo,7,"C"); }
  {int s[]={12,3}; CheckAndLoad(gamsxUelName,1,"C"); }
  {int s[]={3,11}; CheckAndLoad(gamsxFindSymbol,1,"C"); }
  {int s[]={3,3,21}; CheckAndLoad(gamsxDataReadRawStart,2,""); }
  {int s[]={3,52,54,21}; CheckAndLoad(gamsxDataReadRaw,3,""); }
  {int s[]={3}; CheckAndLoad(gamsxDataReadDone,0,""); }
  {int s[]={3,3,15}; CheckAndLoad(gamsxDataWriteRawStart,2,""); }
  {int s[]={3,51,53}; CheckAndLoad(gamsxDataWriteRaw,2,""); }
  {int s[]={3}; CheckAndLoad(gamsxDataWriteDone,0,""); }
  {int s[]={0,59,1}; CheckAndLoad(gamsxRegisterCB1,2,""); }
  {int s[]={0,59,1,1}; CheckAndLoad(gamsxRegisterCB2,3,""); }
  {int s[]={59}; CheckAndLoad(gamsxGetCB1,0,""); }
  {int s[]={59}; CheckAndLoad(gamsxGetCB2,0,""); }
  {int s[]={1}; CheckAndLoad(gamsxGetCB1UM,0,""); }
  {int s[]={1}; CheckAndLoad(gamsxGetCB2UM1,0,""); }
  {int s[]={1}; CheckAndLoad(gamsxGetCB2UM2,0,""); }
  {int s[]={0,3}; CheckAndLoad(gamsxSWSet,1,""); }
  {int s[]={15}; CheckAndLoad(gamsxStepThrough,0,""); }
  {int s[]={0,15}; CheckAndLoad(gamsxStepThroughSet,1,""); }
  {int s[]={15}; CheckAndLoad(gamsxRunToEnd,0,""); }
  {int s[]={0,15}; CheckAndLoad(gamsxRunToEndSet,1,""); }
  {int s[]={15}; CheckAndLoad(gamsxCB1Defined,0,""); }
  {int s[]={15}; CheckAndLoad(gamsxCB2Defined,0,""); }

 return 0;

 symMissing:
  if (errBuf && errBufSize>0) {
    int elen;
    char* ebuf;
    elen = errBufSize;  ebuf = errBuf;
    rc = sprintf (ebuf, "%.*s", elen, "Could not load symbol '");
    elen -= rc;  ebuf+= rc;
    rc = sprintf (ebuf, "%.*s", elen, symName);
    elen -= rc;  ebuf+= rc;
    rc = sprintf (ebuf, "%.*s", elen, "': ");
    elen -= rc;  ebuf+= rc;
    rc = sprintf (ebuf, "%.*s", elen, errMsg);
    /* elen -= rc;  ebuf+= rc; */
    errBuf[errBufSize-1] = '\0';
    /* printf ("%s\n", errBuf); */
    return 2;
  }

 return 0;

} /* XLibraryLoad */

static int
libloader(const char *dllPath, const char *dllName, char *msgBuf, int msgBufSize)
{

  char dllNameBuf[512];
  int myrc = 0;
  char gms_dll_suffix[4];

#if ! defined(GMS_DLL_PREFIX)
# error "GMS_DLL_PREFIX expected but not defined"
#endif
#if ! defined(GMS_DLL_BASENAME)
# error "GMS_DLL_BASENAME expected but not defined"
#endif
#if ! defined(GMS_DLL_EXTENSION)
# error "GMS_DLL_EXTENSION expected but not defined"
#endif
#if ! defined(GMS_DLL_SUFFIX)
# if defined (_WIN32)
#   error "GMS_DLL_SUFFIX expected but not defined"
# else
  struct utsname uts;

  myrc = uname(&uts);
  if (myrc) {
    strcpy(msgBuf,"Error, cannot define library name suffix");
    return 0;
  }
  if (0 == strcmp(uts.sysname, "AIX")) /* assume AIX is 64-bit */
    strcpy (gms_dll_suffix, "64");
  else if (0 == strcmp(uts.sysname, "Darwin")) {
    /* keep Darwin test in here: fat binaries must check at run time */
    if (8 == (int)sizeof(void *))
      strcpy (gms_dll_suffix, "64");
    else
      strcpy (gms_dll_suffix, "");
  }
  else {
    strcpy(msgBuf,"Error, cannot define library name suffix");
    return 0;
  }
# endif
#else
  strcpy (gms_dll_suffix, GMS_DLL_SUFFIX);
#endif


  if (NULL != msgBuf) msgBuf[0] = '\0';

  if (! isLoaded) {
    if (NULL != dllPath && '\0' != *dllPath) {
      strncpy(dllNameBuf, dllPath, sizeof(dllNameBuf)-1);
      dllNameBuf[sizeof(dllNameBuf)-1] = '\0';
#if defined(_WIN32)
      if ('\\' != dllNameBuf[strlen(dllNameBuf)])
        strcat(dllNameBuf,"\\");
#else
      if ('/' != dllNameBuf[strlen(dllNameBuf)])
        strcat(dllNameBuf,"/");
#endif
    }
    else {
      dllNameBuf[0] = '\0';
    }
    if (NULL != dllName && '\0' != *dllName) {
      strncat(dllNameBuf, dllName, sizeof(dllNameBuf)-strlen(dllNameBuf)-1);
    }
    else {
      strncat(dllNameBuf, GMS_DLL_PREFIX GMS_DLL_BASENAME, sizeof(dllNameBuf)-strlen(dllNameBuf)-1);
      strncat(dllNameBuf, gms_dll_suffix                 , sizeof(dllNameBuf)-strlen(dllNameBuf)-1);
      strncat(dllNameBuf, GMS_DLL_EXTENSION              , sizeof(dllNameBuf)-strlen(dllNameBuf)-1);
    }
    isLoaded = ! XLibraryLoad (dllNameBuf, msgBuf, msgBufSize);
    if (isLoaded) {
    }
    else {                              /* library load failed */
      myrc |= 1;
    }
  }
  return (myrc & 1) == 0;
}


/* gamsxGetReady: return false on failure to load library, true on success */
int gamsxGetReady (char *msgBuf, int msgBufSize)
{
  int rc;
  lock(libMutex);
  rc = libloader(NULL, NULL, msgBuf, msgBufSize);
  unlock(libMutex);
  return rc;
} /* gamsxGetReady */

/* gamsxGetReadyD: return false on failure to load library, true on success */
int gamsxGetReadyD (const char *dirName, char *msgBuf, int msgBufSize)
{
  int rc;
  lock(libMutex);
  rc = libloader(dirName, NULL, msgBuf, msgBufSize);
  unlock(libMutex);
  return rc;
} /* gamsxGetReadyD */

/* gamsxGetReadyL: return false on failure to load library, true on success */
int gamsxGetReadyL (const char *libName, char *msgBuf, int msgBufSize)
{
  char dirName[1024],fName[1024];
  int rc;
  extractFileDirFileName (libName, dirName, fName);
  lock(libMutex);
  rc = libloader(dirName, fName, msgBuf, msgBufSize);
  unlock(libMutex);
  return rc;
} /* gamsxGetReadyL */

/* gamsxCreate: return false on failure to load library, true on success */
int gamsxCreate (gamsxHandle_t *pgamsx, char *msgBuf, int msgBufSize)
{
  int gamsxIsReady;

  gamsxIsReady = gamsxGetReady (msgBuf, msgBufSize);
  if (! gamsxIsReady) {
    return 0;
  }
  assert(XCreate);
  XCreate(pgamsx);
  if(pgamsx == NULL)
  { strcpy(msgBuf,"Error while creating object"); return 0; }
  lock(objMutex);
  objectCount++;
  unlock(objMutex);
  return 1;                     /* return true on successful library load */
} /* gamsxCreate */

/* gamsxCreateD: return false on failure to load library, true on success */
int gamsxCreateD (gamsxHandle_t *pgamsx, const char *dirName,
                char *msgBuf, int msgBufSize)
{
  int gamsxIsReady;

  gamsxIsReady = gamsxGetReadyD (dirName, msgBuf, msgBufSize);
  if (! gamsxIsReady) {
    return 0;
  }
  assert(XCreate);
  XCreate(pgamsx);
  if(pgamsx == NULL)
  { strcpy(msgBuf,"Error while creating object"); return 0; }
  lock(objMutex);
  objectCount++;
  unlock(objMutex);
  return 1;                     /* return true on successful library load */
} /* gamsxCreateD */

/* gamsxCreateL: return false on failure to load library, true on success */
int gamsxCreateL (gamsxHandle_t *pgamsx, const char *libName,
                char *msgBuf, int msgBufSize)
{
  int gamsxIsReady;

  gamsxIsReady = gamsxGetReadyL (libName, msgBuf, msgBufSize);
  if (! gamsxIsReady) {
    return 0;
  }
  assert(XCreate);
  XCreate(pgamsx);
  if(pgamsx == NULL)
  { strcpy(msgBuf,"Error while creating object"); return 0; }
  lock(objMutex);
  objectCount++;
  unlock(objMutex);
  return 1;                     /* return true on successful library load */
} /* gamsxCreateL */

int gamsxFree   (gamsxHandle_t *pgamsx)
{
  assert(XFree);
  XFree(pgamsx); pgamsx = NULL;
  lock(objMutex);
  objectCount--;
  unlock(objMutex);
  return 1;
} /* gamsxFree */

int gamsxLibraryLoaded(void)
{
  int rc;
  lock(libMutex);
  rc = isLoaded;
  unlock(libMutex);
  return rc;
} /* gamsxLibraryLoaded */

int gamsxLibraryUnload(void)
{
  lock(objMutex);
  if (objectCount > 0)
  {
    unlock(objMutex);
    return 0;
  }
  unlock(objMutex);
  lock(libMutex);
  isLoaded = 0;
  (void) unLoadLib(h);
  unlock(libMutex);
  return 1;
} /* gamsxLibraryUnload */

int  gamsxCorrectLibraryVersion(char *msgBuf, int msgBufLen)
{
  int cl;
  char localBuf[256];

  if (msgBuf && msgBufLen) msgBuf[0] = '\0';

  if (! isLoaded) {
    strncpy(msgBuf, "Library needs to be initialized first", msgBufLen);
    return 0;
  }

  if (NULL == XAPIVersion) {
    strncpy(msgBuf, "Function XAPIVersion not found", msgBufLen);
    return 0;
  }

  XAPIVersion(GAMSXAPIVERSION,localBuf,&cl);
  strncpy(msgBuf, localBuf, msgBufLen);

  if (1 == cl)
    return 1;
  else
    return 0;
}

int gamsxGetScreenIndicator(void)
{
  return ScreenIndicator;
}

void gamsxSetScreenIndicator(int scrind)
{
  ScreenIndicator = scrind ? 1 : 0;
}

int gamsxGetExceptionIndicator(void)
{
   return ExceptionIndicator;
}

void gamsxSetExceptionIndicator(int excind)
{
  ExceptionIndicator = excind ? 1 : 0;
}

int gamsxGetExitIndicator(void)
{
  return ExitIndicator;
}

void gamsxSetExitIndicator(int extind)
{
  ExitIndicator = extind ? 1 : 0;
}

gamsxErrorCallback_t gamsxGetErrorCallback(void)
{
  return ErrorCallBack;
}

void gamsxSetErrorCallback(gamsxErrorCallback_t func)
{
  lock(exceptMutex);
  ErrorCallBack = func;
  unlock(exceptMutex);
}

int gamsxGetAPIErrorCount(void)
{
  return APIErrorCount;
}

void gamsxSetAPIErrorCount(int ecnt)
{
  APIErrorCount = ecnt;
}

void gamsxErrorHandling(const char *msg)
{
  APIErrorCount++;
  if (ScreenIndicator) { printf("%s\n", msg); fflush(stdout); }
  lock(exceptMutex);
  if (ErrorCallBack)
    if (ErrorCallBack(APIErrorCount, msg)) { unlock(exceptMutex); exit(123); }
  unlock(exceptMutex);
  assert(!ExceptionIndicator);
  if (ExitIndicator) exit(123);
}

