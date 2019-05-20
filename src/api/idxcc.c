/*  C code generated by apiwrapper for GAMS Version 25.1.2
 *  Copyright (c) 2016, GAMS Development Corp.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>

#define IDX_MAIN
#include "idxcc.h"

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
static idxErrorCallback_t ErrorCallBack = NULL;
static int APIErrorCount = 0;

#if defined(HAVE_MUTEX)
#include "gcmt.h"
static GC_mutex_t libMutex;
static GC_mutex_t objMutex;
static GC_mutex_t exceptMutex;

static int MutexIsInitialized = 0;

void idxInitMutexes(void)
{
  int rc;
  if (0==MutexIsInitialized) {
    rc = GC_mutex_init (&libMutex);     if(0!=rc) idxErrorHandling("Problem initializing libMutex");
    rc = GC_mutex_init (&objMutex);     if(0!=rc) idxErrorHandling("Problem initializing objMutex");
    rc = GC_mutex_init (&exceptMutex);  if(0!=rc) idxErrorHandling("Problem initializing exceptMutex");
    MutexIsInitialized = 1;
  }
}

void idxFiniMutexes(void)
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
void idxInitMutexes(void) {}
void idxFiniMutexes(void) {}
#endif

#if !defined(GAMS_UNUSED)
#define GAMS_UNUSED(x) (void)x;
#endif

typedef void (IDX_CALLCONV *XCreate_t) (idxHandle_t *pidx);
static IDX_FUNCPTR(XCreate);
typedef void (IDX_CALLCONV *XFree_t)   (idxHandle_t *pidx);
static IDX_FUNCPTR(XFree);
typedef int (IDX_CALLCONV *XAPIVersion_t) (int api, char *msg, int *cl);
static IDX_FUNCPTR(XAPIVersion);
typedef int (IDX_CALLCONV *XCheck_t) (const char *ep, int nargs, int s[], char *msg);
static IDX_FUNCPTR(XCheck);

#define printNoReturn(f,nargs) { \
  char d_msgBuf[256]; \
  strcpy(d_msgBuf,#f " could not be loaded: "); \
  XCheck(#f,nargs,d_s,d_msgBuf+strlen(d_msgBuf)); \
  idxErrorHandling(d_msgBuf); \
}
#define printAndReturn(f,nargs,rtype) { \
  char d_msgBuf[256]; \
  strcpy(d_msgBuf,#f " could not be loaded: "); \
  XCheck(#f,nargs,d_s,d_msgBuf+strlen(d_msgBuf)); \
  idxErrorHandling(d_msgBuf); \
  return (rtype) 0; \
}

int  IDX_CALLCONV d_idxGetLastError (idxHandle_t pidx)
{
  int d_s[]={3};
  GAMS_UNUSED(pidx)
  printAndReturn(idxGetLastError,0,int )
}

void  IDX_CALLCONV d_idxErrorStr (idxHandle_t pidx, int ErrNr, char *ErrMsg, int ErrMsg_i)
{
  int d_s[]={0,3,17};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(ErrNr)
  GAMS_UNUSED(ErrMsg)
  printNoReturn(idxErrorStr,2)
}

int  IDX_CALLCONV d_idxOpenRead (idxHandle_t pidx, const char *FileName, int *ErrNr)
{
  int d_s[]={3,11,4};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(FileName)
  GAMS_UNUSED(ErrNr)
  printAndReturn(idxOpenRead,2,int )
}

int  IDX_CALLCONV d_idxOpenWrite (idxHandle_t pidx, const char *FileName, const char *Producer, int *ErrNr)
{
  int d_s[]={3,11,11,4};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(FileName)
  GAMS_UNUSED(Producer)
  GAMS_UNUSED(ErrNr)
  printAndReturn(idxOpenWrite,3,int )
}

int  IDX_CALLCONV d_idxClose (idxHandle_t pidx)
{
  int d_s[]={3};
  GAMS_UNUSED(pidx)
  printAndReturn(idxClose,0,int )
}

int  IDX_CALLCONV d_idxGetSymCount (idxHandle_t pidx, int *symCount)
{
  int d_s[]={3,4};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(symCount)
  printAndReturn(idxGetSymCount,1,int )
}

int  IDX_CALLCONV d_idxGetSymbolInfo (idxHandle_t pidx, int iSym, char *symName, int symName_i, int *symDim, int dims[], int *nNZ, char *explText, int explText_i)
{
  int d_s[]={3,3,17,4,52,4,17};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(iSym)
  GAMS_UNUSED(symName)
  GAMS_UNUSED(symDim)
  GAMS_UNUSED(dims)
  GAMS_UNUSED(nNZ)
  GAMS_UNUSED(explText)
  printAndReturn(idxGetSymbolInfo,6,int )
}

int  IDX_CALLCONV d_idxGetSymbolInfoByName (idxHandle_t pidx, const char *symName, int *iSym, int *symDim, int dims[], int *nNZ, char *explText, int explText_i)
{
  int d_s[]={3,11,4,4,52,4,17};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(symName)
  GAMS_UNUSED(iSym)
  GAMS_UNUSED(symDim)
  GAMS_UNUSED(dims)
  GAMS_UNUSED(nNZ)
  GAMS_UNUSED(explText)
  printAndReturn(idxGetSymbolInfoByName,6,int )
}

int  IDX_CALLCONV d_idxGetIndexBase (idxHandle_t pidx)
{
  int d_s[]={3};
  GAMS_UNUSED(pidx)
  printAndReturn(idxGetIndexBase,0,int )
}

int  IDX_CALLCONV d_idxSetIndexBase (idxHandle_t pidx, int idxBase)
{
  int d_s[]={3,3};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(idxBase)
  printAndReturn(idxSetIndexBase,1,int )
}

int  IDX_CALLCONV d_idxDataReadStart (idxHandle_t pidx, const char *symName, int *symDim, int dims[], int *nRecs, char *ErrMsg, int ErrMsg_i)
{
  int d_s[]={3,11,4,52,4,17};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(symName)
  GAMS_UNUSED(symDim)
  GAMS_UNUSED(dims)
  GAMS_UNUSED(nRecs)
  GAMS_UNUSED(ErrMsg)
  printAndReturn(idxDataReadStart,5,int )
}

int  IDX_CALLCONV d_idxDataRead (idxHandle_t pidx, int keys[], double *val, int *changeIdx)
{
  int d_s[]={3,52,14,4};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(keys)
  GAMS_UNUSED(val)
  GAMS_UNUSED(changeIdx)
  printAndReturn(idxDataRead,3,int )
}

int  IDX_CALLCONV d_idxDataReadDone (idxHandle_t pidx)
{
  int d_s[]={3};
  GAMS_UNUSED(pidx)
  printAndReturn(idxDataReadDone,0,int )
}

int  IDX_CALLCONV d_idxDataReadSparseColMajor (idxHandle_t pidx, int idxBase, int colPtr[], int rowIdx[], double vals[])
{
  int d_s[]={3,3,8,8,6};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(idxBase)
  GAMS_UNUSED(colPtr)
  GAMS_UNUSED(rowIdx)
  GAMS_UNUSED(vals)
  printAndReturn(idxDataReadSparseColMajor,4,int )
}

int  IDX_CALLCONV d_idxDataReadSparseRowMajor (idxHandle_t pidx, int idxBase, int rowPtr[], int colIdx[], double vals[])
{
  int d_s[]={3,3,8,8,6};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(idxBase)
  GAMS_UNUSED(rowPtr)
  GAMS_UNUSED(colIdx)
  GAMS_UNUSED(vals)
  printAndReturn(idxDataReadSparseRowMajor,4,int )
}

int  IDX_CALLCONV d_idxDataReadDenseColMajor (idxHandle_t pidx, double vals[])
{
  int d_s[]={3,6};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(vals)
  printAndReturn(idxDataReadDenseColMajor,1,int )
}

int  IDX_CALLCONV d_idxDataReadDenseRowMajor (idxHandle_t pidx, double vals[])
{
  int d_s[]={3,6};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(vals)
  printAndReturn(idxDataReadDenseRowMajor,1,int )
}

int  IDX_CALLCONV d_idxDataWriteStart (idxHandle_t pidx, const char *symName, const char *explTxt, int symDim, const int dims[], char *ErrMsg, int ErrMsg_i)
{
  int d_s[]={3,11,11,3,51,17};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(symName)
  GAMS_UNUSED(explTxt)
  GAMS_UNUSED(symDim)
  GAMS_UNUSED(dims)
  GAMS_UNUSED(ErrMsg)
  printAndReturn(idxDataWriteStart,5,int )
}

int  IDX_CALLCONV d_idxDataWrite (idxHandle_t pidx, const int keys[], double val)
{
  int d_s[]={3,51,13};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(keys)
  GAMS_UNUSED(val)
  printAndReturn(idxDataWrite,2,int )
}

int  IDX_CALLCONV d_idxDataWriteDone (idxHandle_t pidx)
{
  int d_s[]={3};
  GAMS_UNUSED(pidx)
  printAndReturn(idxDataWriteDone,0,int )
}

int  IDX_CALLCONV d_idxDataWriteSparseColMajor (idxHandle_t pidx, const int colPtr[], const int rowIdx[], const double vals[])
{
  int d_s[]={3,7,7,5};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(colPtr)
  GAMS_UNUSED(rowIdx)
  GAMS_UNUSED(vals)
  printAndReturn(idxDataWriteSparseColMajor,3,int )
}

int  IDX_CALLCONV d_idxDataWriteSparseRowMajor (idxHandle_t pidx, const int rowPtr[], const int colIdx[], const double vals[])
{
  int d_s[]={3,7,7,5};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(rowPtr)
  GAMS_UNUSED(colIdx)
  GAMS_UNUSED(vals)
  printAndReturn(idxDataWriteSparseRowMajor,3,int )
}

int  IDX_CALLCONV d_idxDataWriteDenseColMajor (idxHandle_t pidx, int dataDim, const double vals[])
{
  int d_s[]={3,3,5};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(dataDim)
  GAMS_UNUSED(vals)
  printAndReturn(idxDataWriteDenseColMajor,2,int )
}

int  IDX_CALLCONV d_idxDataWriteDenseRowMajor (idxHandle_t pidx, int dataDim, const double vals[])
{
  int d_s[]={3,3,5};
  GAMS_UNUSED(pidx)
  GAMS_UNUSED(dataDim)
  GAMS_UNUSED(vals)
  printAndReturn(idxDataWriteDenseRowMajor,2,int )
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
# define GMS_DLL_BASENAME "idxcclib"
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
  LOADIT(XCheck, "C__XCheck");
  LOADIT(XAPIVersion, "C__XAPIVersion");

  if (!XAPIVersion(1,errBuf,&cl))
    return 1;


#define CheckAndLoad(f,nargs,prefix) \
  if (!XCheck(#f,nargs,s,errBuf)) \
    f = &d_##f; \
  else { \
    LOADIT(f,prefix #f); \
  }
  {int s[]={3}; CheckAndLoad(idxGetLastError,0,"C__"); }
  {int s[]={0,3,17}; CheckAndLoad(idxErrorStr,2,"C__"); }
  {int s[]={3,11,4}; CheckAndLoad(idxOpenRead,2,"C__"); }
  {int s[]={3,11,11,4}; CheckAndLoad(idxOpenWrite,3,"C__"); }
  {int s[]={3}; CheckAndLoad(idxClose,0,"C__"); }
  {int s[]={3,4}; CheckAndLoad(idxGetSymCount,1,"C__"); }
  {int s[]={3,3,17,4,52,4,17}; CheckAndLoad(idxGetSymbolInfo,6,"C__"); }
  {int s[]={3,11,4,4,52,4,17}; CheckAndLoad(idxGetSymbolInfoByName,6,"C__"); }
  {int s[]={3}; CheckAndLoad(idxGetIndexBase,0,"C__"); }
  {int s[]={3,3}; CheckAndLoad(idxSetIndexBase,1,"C__"); }
  {int s[]={3,11,4,52,4,17}; CheckAndLoad(idxDataReadStart,5,"C__"); }
  {int s[]={3,52,14,4}; CheckAndLoad(idxDataRead,3,"C__"); }
  {int s[]={3}; CheckAndLoad(idxDataReadDone,0,"C__"); }
  {int s[]={3,3,8,8,6}; CheckAndLoad(idxDataReadSparseColMajor,4,"C__"); }
  {int s[]={3,3,8,8,6}; CheckAndLoad(idxDataReadSparseRowMajor,4,"C__"); }
  {int s[]={3,6}; CheckAndLoad(idxDataReadDenseColMajor,1,"C__"); }
  {int s[]={3,6}; CheckAndLoad(idxDataReadDenseRowMajor,1,"C__"); }
  {int s[]={3,11,11,3,51,17}; CheckAndLoad(idxDataWriteStart,5,"C__"); }
  {int s[]={3,51,13}; CheckAndLoad(idxDataWrite,2,"C__"); }
  {int s[]={3}; CheckAndLoad(idxDataWriteDone,0,"C__"); }
  {int s[]={3,7,7,5}; CheckAndLoad(idxDataWriteSparseColMajor,3,"C__"); }
  {int s[]={3,7,7,5}; CheckAndLoad(idxDataWriteSparseRowMajor,3,"C__"); }
  {int s[]={3,3,5}; CheckAndLoad(idxDataWriteDenseColMajor,2,"C__"); }
  {int s[]={3,3,5}; CheckAndLoad(idxDataWriteDenseRowMajor,2,"C__"); }

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


/* idxGetReady: return false on failure to load library, true on success */
int idxGetReady (char *msgBuf, int msgBufSize)
{
  int rc;
  lock(libMutex);
  rc = libloader(NULL, NULL, msgBuf, msgBufSize);
  unlock(libMutex);
  return rc;
} /* idxGetReady */

/* idxGetReadyD: return false on failure to load library, true on success */
int idxGetReadyD (const char *dirName, char *msgBuf, int msgBufSize)
{
  int rc;
  lock(libMutex);
  rc = libloader(dirName, NULL, msgBuf, msgBufSize);
  unlock(libMutex);
  return rc;
} /* idxGetReadyD */

/* idxGetReadyL: return false on failure to load library, true on success */
int idxGetReadyL (const char *libName, char *msgBuf, int msgBufSize)
{
  char dirName[1024],fName[1024];
  int rc;
  extractFileDirFileName (libName, dirName, fName);
  lock(libMutex);
  rc = libloader(dirName, fName, msgBuf, msgBufSize);
  unlock(libMutex);
  return rc;
} /* idxGetReadyL */

/* idxCreate: return false on failure to load library, true on success */
int idxCreate (idxHandle_t *pidx, char *msgBuf, int msgBufSize)
{
  int idxIsReady;

  idxIsReady = idxGetReady (msgBuf, msgBufSize);
  if (! idxIsReady) {
    return 0;
  }
  assert(XCreate);
  XCreate(pidx);
  if(pidx == NULL)
  { strcpy(msgBuf,"Error while creating object"); return 0; }
  lock(objMutex);
  objectCount++;
  unlock(objMutex);
  return 1;                     /* return true on successful library load */
} /* idxCreate */

/* idxCreateD: return false on failure to load library, true on success */
int idxCreateD (idxHandle_t *pidx, const char *dirName,
                char *msgBuf, int msgBufSize)
{
  int idxIsReady;

  idxIsReady = idxGetReadyD (dirName, msgBuf, msgBufSize);
  if (! idxIsReady) {
    return 0;
  }
  assert(XCreate);
  XCreate(pidx);
  if(pidx == NULL)
  { strcpy(msgBuf,"Error while creating object"); return 0; }
  lock(objMutex);
  objectCount++;
  unlock(objMutex);
  return 1;                     /* return true on successful library load */
} /* idxCreateD */

/* idxCreateL: return false on failure to load library, true on success */
int idxCreateL (idxHandle_t *pidx, const char *libName,
                char *msgBuf, int msgBufSize)
{
  int idxIsReady;

  idxIsReady = idxGetReadyL (libName, msgBuf, msgBufSize);
  if (! idxIsReady) {
    return 0;
  }
  assert(XCreate);
  XCreate(pidx);
  if(pidx == NULL)
  { strcpy(msgBuf,"Error while creating object"); return 0; }
  lock(objMutex);
  objectCount++;
  unlock(objMutex);
  return 1;                     /* return true on successful library load */
} /* idxCreateL */

int idxFree   (idxHandle_t *pidx)
{
  assert(XFree);
  XFree(pidx); pidx = NULL;
  lock(objMutex);
  objectCount--;
  unlock(objMutex);
  return 1;
} /* idxFree */

int idxLibraryLoaded(void)
{
  int rc;
  lock(libMutex);
  rc = isLoaded;
  unlock(libMutex);
  return rc;
} /* idxLibraryLoaded */

int idxLibraryUnload(void)
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
} /* idxLibraryUnload */

int  idxCorrectLibraryVersion(char *msgBuf, int msgBufLen)
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

  XAPIVersion(IDXAPIVERSION,localBuf,&cl);
  strncpy(msgBuf, localBuf, msgBufLen);

  if (1 == cl)
    return 1;
  else
    return 0;
}

int idxGetScreenIndicator(void)
{
  return ScreenIndicator;
}

void idxSetScreenIndicator(int scrind)
{
  ScreenIndicator = scrind ? 1 : 0;
}

int idxGetExceptionIndicator(void)
{
   return ExceptionIndicator;
}

void idxSetExceptionIndicator(int excind)
{
  ExceptionIndicator = excind ? 1 : 0;
}

int idxGetExitIndicator(void)
{
  return ExitIndicator;
}

void idxSetExitIndicator(int extind)
{
  ExitIndicator = extind ? 1 : 0;
}

idxErrorCallback_t idxGetErrorCallback(void)
{
  return ErrorCallBack;
}

void idxSetErrorCallback(idxErrorCallback_t func)
{
  lock(exceptMutex);
  ErrorCallBack = func;
  unlock(exceptMutex);
}

int idxGetAPIErrorCount(void)
{
  return APIErrorCount;
}

void idxSetAPIErrorCount(int ecnt)
{
  APIErrorCount = ecnt;
}

void idxErrorHandling(const char *msg)
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

