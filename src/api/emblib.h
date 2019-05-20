/*  Copyright (c) 2016, GAMS Development Corp. */
/*  GAMS Embedded Code C API */

#ifndef EMBCODE_H_
#define EMBCODE_H_

#if defined(_WIN32)
# define EMBCODE_API __declspec(dllexport)
# define EMBCODE_CALLCONV __stdcall
#elif defined(__GNUC__)
# define EMBCODE_API __attribute__((__visibility__("default")))
# define EMBCODE_CALLCONV
#else
# define EMBCODE_API
# define EMBCODE_CALLCONV
#endif

#define EMBCODE_STRSIZE 257

#define EMB_NRUELS    1
#define EMB_NRSYMBOLS 2
#define EMB_SCRDIR    3
#define EMB_SYSDIR    4

#define EMB_SYMBOLTYPE     1
#define EMB_SYMBOLNAME     2
#define EMB_SYMBOLDIM      3
#define EMB_SYMBOLUSERINFO 4
#define EMB_SYMBOLTEXT     5
#define EMB_SYMBOLACCESS   6
#define EMB_ALIASEDSET     7
#define EMB_NUMRECORDS     8

#define EMBVER     1

#include <stdarg.h>
#include <string.h>
#if defined(_WIN32)
# define strcasecmp  _stricmp
# define strncasecmp _strnicmp
#else
# include <strings.h>
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/** Embedded Code Data Structure */
struct EMBCODE_Data;
/** Extrinsic Function Data Type */
typedef struct EMBCODE_Data EMBCODE_DATA;

/** Return codes for function calls */
typedef enum
{
   EMBCODE_RETURN_OK       = 0,  /**< no error */
   EMBCODE_RETURN_SYSTEM   = 1   /**< system error */
} EMBCODE_RETURN;

/** Error callbacks signature */
typedef void (EMBCODE_CALLCONV *EMBCODEMessage_t) (
   const char*           msg,                /**< error message as Delphi string */
   void*                 usrmem              /**< GAMS user memory */
);

typedef EMBCODE_RETURN (EMBCODE_CALLCONV *EMBCODEGetInfo_t) (
   int                   infoType,           /**< Information type number */
   int*                  iData,              /**< Integer information */
   double*               rData,              /**< Double information */
   char*                 sData,              /**< String information as Delphi string */
   int                   sDataSize,          /**< String size */
   void*                 usrmem              /**< GAMS user memory */
);

typedef EMBCODE_RETURN (EMBCODE_CALLCONV *EMBCODEGetSymbolInfo_t) (
   int                   syNr,               /**< Identifies number */
   int                   infoType,           /**< Information type number */
   int*                  iData,              /**< Integer information */
   double*               rData,              /**< Double information */
   char*                 sData,              /**< String information as Delphi string */
   int                   sDataSize,          /**< String size */
   void*                 usrmem              /**< GAMS user memory */
);

typedef EMBCODE_RETURN (EMBCODE_CALLCONV *EMBCODEAddUel_t) (
   const char*           uel,                /**< UEL as Delphi string */
   int*                  uelNr,              /**< UEL number */
   void*                 usrmem              /**< GAMS user memory */
);

typedef EMBCODE_RETURN (EMBCODE_CALLCONV *EMBCODEGetUel_t) (
   int                   uelNr,              /**< UEL number */
   char*                 uel,                /**< UEL as Delphi string */
   int                   uelSize,            /**< Size of string to store uel buffer */
   void*                 usrmem              /**< GAMS user memory */
);

typedef EMBCODE_RETURN (EMBCODE_CALLCONV *EMBCODEGetElemText_t) (
   int                   eTextNr,            /**< Text number */
   char*                 eText,              /**< Text as Delphi string */
   int                   eTextSize,          /**< Size of string to store text buffer */
   void*                 usrmem              /**< GAMS user memory */
);

typedef EMBCODE_RETURN (EMBCODE_CALLCONV *EMBCODEFindSymbol_t) (
   const char*           syId,               /**< Identifier name as Delphi string*/
   int*                  syNr,               /**< Identifier number */
   void*                 usrmem              /**< GAMS user memory */
);

typedef EMBCODE_RETURN (EMBCODE_CALLCONV *EMBCODEGetSymbolDomains_t) (
   int                   syNr,               /**< Identifier number */
   int                   domainSyNrs[],      /**< Domain symbol numbers */
   void*                 usrmem              /**< GAMS user memory */
);


typedef EMBCODE_RETURN (EMBCODE_CALLCONV *EMBCODEDataReadRawStart_t) (
   int                   syNr,               /**< Identifier number */
   int*                  nrRecs,             /**< Number of record */
   void*                 usrmem              /**< GAMS user memory */
);

typedef EMBCODE_RETURN (EMBCODE_CALLCONV *EMBCODEDataReadRaw_t) (
   int                   keyInt[],           /**< UEL numbers */
   double                values[],           /**< Record values */
   int*                  dimFirst,           /**< First dimension that changed from last call */
   void*                 usrmem              /**< GAMS user memory */
);

typedef EMBCODE_RETURN (EMBCODE_CALLCONV *EMBCODEDataReadDone_t) (
   void*                 usrmem              /**< GAMS user memory */
);

#if defined(EMBCODE_MAIN)    /* we must define some things only once */
# define EMBCODE_FUNCPTR(NAME)  EMBCODE##NAME##_t emb##NAME##CB = NULL
#else
# define EMBCODE_FUNCPTR(NAME)  extern EMBCODE##NAME##_t emb##NAME##CB
#endif

EMBCODE_FUNCPTR(Message);
EMBCODE_FUNCPTR(GetInfo);
EMBCODE_FUNCPTR(GetSymbolInfo);
EMBCODE_FUNCPTR(AddUel);
EMBCODE_FUNCPTR(GetUel);
EMBCODE_FUNCPTR(GetElemText);
EMBCODE_FUNCPTR(FindSymbol);
EMBCODE_FUNCPTR(GetSymbolDomains);
EMBCODE_FUNCPTR(DataReadRawStart);
EMBCODE_FUNCPTR(DataReadRaw);
EMBCODE_FUNCPTR(DataReadDone);

void embMessage(
   void* usrmem,
   const char *fmt, ...
);

EMBCODE_RETURN embGetSymbolInfoByNumber(
   int            symNr,           /**< symbol number */
   int*           symAccess,       /**< access allowed */
   int*           symDim,          /**< symbol dimension */
   int*           symType,         /**< symbol type */
   int*           symUserInfo,     /**< symbol user info */
   int*           symNumRecs,      /**< symbol numRecs aka NNZ or card */
   char*          symName,         /**< symbol name */
   int            symNameSize,     /**< size of symName buffer */
   char*          symText,         /**< symbol text */
   int            symTextSize,     /**< size of symText buffer */
   void*          usrmem           /**< user memory */
);

/** Function to create embedded code library data.
 *
 * This function is called by the GAMS execution system after the library
 * has been loaded. Its purpose is to allocate and initialize the
 * library-specific data structure (struct EMBCODE_Data).
 */
EMBCODE_API void EMBCODE_CALLCONV XCreate(
   EMBCODE_DATA**       data             /**< buffer to store pointer to embedded code library data structure */
);

/** Function to free embedded code library data.
 *
 * This function is called by the GAMS execution system before the library
 * is unloaded. Its purpose is to free the library-specific data.
 */
EMBCODE_API void EMBCODE_CALLCONV XFree(
   EMBCODE_DATA**       data             /**< pointer to pointer to embedded code library data structure */
);

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embLibInit(
   EMBCODE_DATA*        data,            /**< embedded code library data structure */
   int                  version,         /**< version number */
   EMBCODEMessage_t     embMessagePtr,   /**< error callback */
   void*                usrmem           /**< error callback user memory */
);

   /** Function to initialize embedded code library.
 *
 * This function is called by the GAMS execution system after the library
 * has been loaded and library-specific data has been initialized.
 *
 * Its purpose is to check whether the API version of the library
 * is compatible with the GAMS execution system.
 * Additionally, library-specific initializations can be executed in this
 * call.
 *
 * In difference to xcreate, this function can return a message
 * and error code to the GAMS execution system in case of an error.
 *
 * @return 0 if successful, <> 0 in case of error.
 */
EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embInit(
   EMBCODE_DATA*        data,            /**< embedded code library data structure */
   char*                args             /**< buffer of length 255 for library arguments (as Delphi string!) */
);

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegInfoCB(
   EMBCODE_DATA*        data,            /**< embedded code library data structure */
   EMBCODEGetInfo_t     embGetInfoPtr    /**< function pointer GetInfo */
);

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegSymbolInfoCB(
   EMBCODE_DATA*          data,                  /**< embedded code library data structure */
   EMBCODEGetSymbolInfo_t embGetSymbolInfoPtr    /**< function pointer GetSymbolInfo */
);

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegAddUELCB(
   EMBCODE_DATA*        data,            /**< embedded code library data structure */
   EMBCODEAddUel_t      embAddUelPtr     /**< function pointer AddUel */
);

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegUELCB(
   EMBCODE_DATA*        data,            /**< embedded code library data structure */
   EMBCODEGetUel_t      embGetUelPtr     /**< function pointer GetUel */
);

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegSetTextCB(
   EMBCODE_DATA*        data,             /**< embedded code library data structure */
   EMBCODEGetElemText_t embGetElemTextPtr /**< function pointer GetElemText */
);

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegFindSymCB(
   EMBCODE_DATA*         data,            /**< embedded code library data structure */
   EMBCODEFindSymbol_t  embFindSymbolPtr /**< function pointer FindSymbol */
);

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegSymbolDomCB(
   EMBCODE_DATA*              data,                  /**< embedded code library data structure */
   EMBCODEGetSymbolDomains_t  embGetSymbolDomainsPtr /**< function pointer GetSymbolDomains */
);

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegReadStartCB(
   EMBCODE_DATA*              data,                  /**< embedded code library data structure */
   EMBCODEDataReadRawStart_t  embDataReadRawStartPtr /**< function pointer DataReadStart */
);

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegReadCB(
   EMBCODE_DATA*          data,               /**< embedded code library data structure */
   EMBCODEDataReadRaw_t   embDataReadRawPtr  /**< function pointer DataReadRaw */
);

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegReadDoneCB(
   EMBCODE_DATA*          data,               /**< embedded code library data structure */
   EMBCODEDataReadDone_t  embDataReadDonePtr  /**< function pointer DataReadDone */
);

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embExecute(
   EMBCODE_DATA*         data,               /**< embedded code library data structure */
   int*                  gmsOutSymNr,        /**< list of symbols GAMS expects to be written (input)*/
   int*                  gmsOutSymLoadType,  /**< list of load types xy x=1 Merge, x=0 Replace, y=1 DC, y=0 Filtered (output)*/   
   int                   size,               /**< length of arrays */
   const char*           code,               /**< Python code to execute, right now file name to script */
   char*                 args                /**< buffer of length 255 for library arguments (as Delphi string!) */
);

/* Data access routines - Embedded Code -> GAMS */
EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embFindSymbol(
   EMBCODE_DATA*         data,               /**< embedded code library data structure */
   const char*           syId,               /**< Identifier name */
   int*                  syNr                /**< Identifier number */
 );

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embDataReadRawStart(
   EMBCODE_DATA*         data,               /**< embedded code library data structure */
   int                   syNr,               /**< Identifier number */
   int*                  nrRecs              /**< Number of record */
 );

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embDataReadRaw(
   EMBCODE_DATA*         data,               /**< embedded code library data structure */
   int                   keyInt[],           /**< uels */
   double                values[],           /**< values */
   int*                  dimFirst            /**< First dimension that changed from last call */
 );

/* For now: This call need to come right after the embDataReadRaw of the corresponding set record */
EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embGetElemText(
   EMBCODE_DATA*         data,               /**< embedded code library data structure */
   int                   textNr,             /**< text number */
   char*                 eText               /**< Text */
 );

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embDataReadDone(
   EMBCODE_DATA*         data                /**< embedded code library data structure */
);

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embFini(
   EMBCODE_DATA*         data                /**< embedded code library data structure */
);

#if defined(__cplusplus)
}
#endif

#endif /* EMBCODE_H_ */
