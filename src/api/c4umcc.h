/* c4umcc.h
 * Header file for C-style interface to the C4U library
 * generated by apiwrapper for GAMS Version 25.1.2
 * Copyright (c) 2016, GAMS Development Corp.
 */

#if ! defined(_C4UCC_H_)
#     define  _C4UCC_H_

#define C4UAPIVERSION 2




#if defined(_WIN32)
# define C4U_CALLCONV __stdcall
#else
# define C4U_CALLCONV
#endif

#if defined(__cplusplus)
extern "C" {
#endif

struct c4uRec;
typedef struct c4uRec *c4uHandle_t;

typedef int (*c4uErrorCallback_t) (int ErrCount, const char *msg);

/* headers for "wrapper" routines implemented in C */
int c4uGetReady  (char *msgBuf, int msgBufLen);
int c4uGetReadyD (const char *dirName, char *msgBuf, int msgBufLen);
int c4uGetReadyL (const char *libName, char *msgBuf, int msgBufLen);
int c4uCreate    (c4uHandle_t *pc4u, char *msgBuf, int msgBufLen);
int c4uCreateD   (c4uHandle_t *pc4u, const char *dirName, char *msgBuf, int msgBufLen);
int c4uCreateL   (c4uHandle_t *pc4u, const char *libName, char *msgBuf, int msgBufLen);
int c4uFree      (c4uHandle_t *pc4u);

int c4uLibraryLoaded(void);
int c4uLibraryUnload(void);

/* returns true  (1) if API and library have the same version,
           false (0) on failure;
   Library needs to be initialized before calling this        */
int  c4uCorrectLibraryVersion(char *msgBuf, int msgBufLen);

int  c4uGetScreenIndicator   (void);
void c4uSetScreenIndicator   (int scrind);
int  c4uGetExceptionIndicator(void);
void c4uSetExceptionIndicator(int excind);
int  c4uGetExitIndicator     (void);
void c4uSetExitIndicator     (int extind);
c4uErrorCallback_t c4uGetErrorCallback(void);
void c4uSetErrorCallback(c4uErrorCallback_t func);
int  c4uGetAPIErrorCount     (void);
void c4uSetAPIErrorCount     (int ecnt);

void c4uErrorHandling(const char *msg);
void c4uInitMutexes(void);
void c4uFiniMutexes(void);


#if defined(C4U_MAIN)    /* we must define some things only once */
# define C4U_FUNCPTR(NAME)  NAME##_t NAME = NULL
#else
# define C4U_FUNCPTR(NAME)  extern NAME##_t NAME
#endif


/* Prototypes for Dummy Functions */
void  C4U_CALLCONV d_c4uReadLice (c4uHandle_t pc4u, const char *syspath, const char *licefn, int WriteHTML);
int  C4U_CALLCONV d_c4uCheck4Update (c4uHandle_t pc4u);
int  C4U_CALLCONV d_c4uCheck4NewStudio (c4uHandle_t pc4u, int myStudio);
void  C4U_CALLCONV d_c4uCreateMsg (c4uHandle_t pc4u);
void  C4U_CALLCONV d_c4uAddDistro (c4uHandle_t pc4u, const char *Distro);
void  C4U_CALLCONV d_c4uAddMsg (c4uHandle_t pc4u, const char *Msg, int pos);
int  C4U_CALLCONV d_c4uGetMsg (c4uHandle_t pc4u, int msgNr, char *Msg);
int  C4U_CALLCONV d_c4uIsValid (c4uHandle_t pc4u);
void * C4U_CALLCONV d_c4ugetMsgLst (c4uHandle_t pc4u);
int  C4U_CALLCONV d_c4uThisRel (c4uHandle_t pc4u);
char * C4U_CALLCONV d_c4uThisRelStr (c4uHandle_t pc4u, char *buf);
int  C4U_CALLCONV d_c4uLastRel (c4uHandle_t pc4u);
char * C4U_CALLCONV d_c4uLastRelStr (c4uHandle_t pc4u, char *buf);
int  C4U_CALLCONV d_c4uMsgCount (c4uHandle_t pc4u);

typedef void  (C4U_CALLCONV *c4uReadLice_t) (c4uHandle_t pc4u, const char *syspath, const char *licefn, int WriteHTML);
C4U_FUNCPTR(c4uReadLice);
typedef int  (C4U_CALLCONV *c4uCheck4Update_t) (c4uHandle_t pc4u);
C4U_FUNCPTR(c4uCheck4Update);
typedef int  (C4U_CALLCONV *c4uCheck4NewStudio_t) (c4uHandle_t pc4u, int myStudio);
C4U_FUNCPTR(c4uCheck4NewStudio);
typedef void  (C4U_CALLCONV *c4uCreateMsg_t) (c4uHandle_t pc4u);
C4U_FUNCPTR(c4uCreateMsg);
typedef void  (C4U_CALLCONV *c4uAddDistro_t) (c4uHandle_t pc4u, const char *Distro);
C4U_FUNCPTR(c4uAddDistro);
typedef void  (C4U_CALLCONV *c4uAddMsg_t) (c4uHandle_t pc4u, const char *Msg, int pos);
C4U_FUNCPTR(c4uAddMsg);
typedef int  (C4U_CALLCONV *c4uGetMsg_t) (c4uHandle_t pc4u, int msgNr, char *Msg);
C4U_FUNCPTR(c4uGetMsg);
typedef int  (C4U_CALLCONV *c4uIsValid_t) (c4uHandle_t pc4u);
C4U_FUNCPTR(c4uIsValid);
typedef void * (C4U_CALLCONV *c4ugetMsgLst_t) (c4uHandle_t pc4u);
C4U_FUNCPTR(c4ugetMsgLst);
typedef int  (C4U_CALLCONV *c4uThisRel_t) (c4uHandle_t pc4u);
C4U_FUNCPTR(c4uThisRel);
typedef char * (C4U_CALLCONV *c4uThisRelStr_t) (c4uHandle_t pc4u, char *buf);
C4U_FUNCPTR(c4uThisRelStr);
typedef int  (C4U_CALLCONV *c4uLastRel_t) (c4uHandle_t pc4u);
C4U_FUNCPTR(c4uLastRel);
typedef char * (C4U_CALLCONV *c4uLastRelStr_t) (c4uHandle_t pc4u, char *buf);
C4U_FUNCPTR(c4uLastRelStr);
typedef int  (C4U_CALLCONV *c4uMsgCount_t) (c4uHandle_t pc4u);
C4U_FUNCPTR(c4uMsgCount);
#if defined(__cplusplus)
}
#endif
#endif /* #if ! defined(_C4UCC_H_) */
