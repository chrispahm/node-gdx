/*  Copyright (c) 2016, GAMS Development Corp. */
/*  GAMS Embedded Code C API */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include "gclgms.h"

#define EMBCODE_MAIN
#include "emblib.h"

//#define EMBDebug(msg)   fprintf(stdout,"%s\n", msg);fflush(stdout);
#define EMBDebug(msg)


EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegInfoCB(
   EMBCODE_DATA*        data,            /**< embedded code library data structure */
   EMBCODEGetInfo_t     embGetInfoPtr    /**< function pointer GetInfo */
)
{
   embGetInfoCB = embGetInfoPtr;
   return EMBCODE_RETURN_OK;
}

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegSymbolInfoCB(
   EMBCODE_DATA*          data,                  /**< embedded code library data structure */
   EMBCODEGetSymbolInfo_t embGetSymbolInfoPtr    /**< function pointer GetSymbolInfo */
)
{
   embGetSymbolInfoCB = embGetSymbolInfoPtr;
   return EMBCODE_RETURN_OK;
}

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegUELCB(
   EMBCODE_DATA*        data,            /**< embedded code library data structure */
   EMBCODEGetUel_t      embGetUelPtr     /**< function pointer GetUel */
)
{
   embGetUelCB = embGetUelPtr;
   return EMBCODE_RETURN_OK;
}

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegSetTextCB(
   EMBCODE_DATA*        data,             /**< embedded code library data structure */
   EMBCODEGetElemText_t embGetElemTextPtr /**< function pointer GetUel */
)
{
   embGetElemTextCB = embGetElemTextPtr;
   return EMBCODE_RETURN_OK;
}

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegAddUELCB(
   EMBCODE_DATA*        data,            /**< embedded code library data structure */
   EMBCODEAddUel_t      embAddUelPtr     /**< function pointer AddUel */
)
{
   embAddUelCB = embAddUelPtr;
   return EMBCODE_RETURN_OK;
}

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegFindSymCB(
   EMBCODE_DATA*        data,            /**< embedded code library data structure */
   EMBCODEFindSymbol_t  embFindSymbolPtr /**< function pointer FindSymbol */
)
{
   embFindSymbolCB = embFindSymbolPtr;
   return EMBCODE_RETURN_OK;
}

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegSymbolDomCB(
   EMBCODE_DATA*              data,                  /**< embedded code library data structure */
   EMBCODEGetSymbolDomains_t  embGetSymbolDomainsPtr /**< function pointer GetSymbolDomains */
)
{
   embGetSymbolDomainsCB = embGetSymbolDomainsPtr;
   return EMBCODE_RETURN_OK;
}

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegReadStartCB(
   EMBCODE_DATA*             data,                  /**< embedded code library data structure */
   EMBCODEDataReadRawStart_t embDataReadRawStartPtr /**< function pointer DataReadStart */
)
{
   embDataReadRawStartCB = embDataReadRawStartPtr;
   return EMBCODE_RETURN_OK;
}

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegReadCB(
   EMBCODE_DATA*         data,               /**< embedded code library data structure */
   EMBCODEDataReadRaw_t  embDataReadRawPtr  /**< function pointer DataReadRaw */
)
{
   embDataReadRawCB = embDataReadRawPtr;
   return EMBCODE_RETURN_OK;
}

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embRegReadDoneCB(
   EMBCODE_DATA*          data,               /**< embedded code library data structure */
   EMBCODEDataReadDone_t  embDataReadDonePtr  /**< function pointer DataReadDone */
)
{
   embDataReadDoneCB = embDataReadDonePtr;
   return EMBCODE_RETURN_OK;
}

#if defined(_WIN32)             /* set automagically */
# define vsnprintf _vsnprintf
#endif

void embMessage( void* usrmem, const char *fmt, ... )
{

   va_list args;
   char msg[EMBCODE_STRSIZE];

   va_start( args, fmt );
   vsnprintf( msg+1, sizeof( msg )-1, fmt, args );

   va_end( args );
   msg[0] = strlen(msg+1);

   embMessageCB(msg, usrmem);
}


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
)
{
   char s_data[EMBCODE_STRSIZE];
   EMBCODE_RETURN rc;
   int _symAccess;

   EMBDebug("embGetSymbolInfoByNumber Access");
   if ((rc=embGetSymbolInfoCB(symNr,EMB_SYMBOLACCESS,&_symAccess,NULL,NULL,0,usrmem)) != EMBCODE_RETURN_OK)
      return rc;

   if (symAccess)
      *symAccess = _symAccess;

   if (!_symAccess)
   {
      if (symAccess)
         return EMBCODE_RETURN_OK;
      else
         return EMBCODE_RETURN_SYSTEM;
   }

   EMBDebug("DIM");
   if (symDim)
   {
      if ((rc=embGetSymbolInfoCB(symNr,EMB_SYMBOLDIM,symDim,NULL,NULL,0,usrmem)) != EMBCODE_RETURN_OK)
         return rc;
      assert((*symDim>=0) && (*symDim<=GMS_MAX_INDEX_DIM));
   }

   EMBDebug("Type");
   if (symType)
   {
      if ((rc=embGetSymbolInfoCB(symNr,EMB_SYMBOLTYPE,symType,NULL,NULL,0,usrmem)) != EMBCODE_RETURN_OK)
      {
         EMBDebug("trouble with Type");
         return rc;
      }

      EMBDebug("UserInfo");
      if (symUserInfo)
      {
         if ((*symType==GMS_DT_EQU) || (*symType==GMS_DT_VAR))
         {
            if ((rc=embGetSymbolInfoCB(symNr,EMB_SYMBOLUSERINFO,symUserInfo,NULL,NULL,0,usrmem)) != EMBCODE_RETURN_OK)
               return rc;
         }
         else
            *symUserInfo = 0;
      }
   }

   EMBDebug("NumRecs");
   if (symNumRecs)
   {
      if ((rc=embGetSymbolInfoCB(symNr,EMB_NUMRECORDS,symNumRecs,NULL,NULL,0,usrmem)) != EMBCODE_RETURN_OK)
         return rc;
      assert(*symNumRecs>=0);
   }

   EMBDebug("SymName");
   if (symName)
   {
      if ((rc=embGetSymbolInfoCB(symNr,EMB_SYMBOLNAME,NULL,NULL,s_data,sizeof(s_data),usrmem)) != EMBCODE_RETURN_OK)
         return rc;
      assert(symNameSize>=GMS_UEL_IDENT_SIZE);
      s_data[s_data[0]+1] = '\0';
      strncpy(symName,s_data+1,GMS_UEL_IDENT_SIZE);
      assert(symName[GMS_UEL_IDENT_SIZE-1]==0);
   }

   EMBDebug("SymText");
   if (symText)
   {
      if ((rc=embGetSymbolInfoCB(symNr,EMB_SYMBOLTEXT,NULL,NULL,s_data,sizeof(s_data),usrmem)) != EMBCODE_RETURN_OK)
         return rc;
            s_data[s_data[0]+1] = '\0';
      assert(symTextSize>=GMS_SSSIZE);
      s_data[s_data[0]+1] = '\0';
      strncpy(symText,s_data+1,GMS_SSSIZE);
      assert(symText[GMS_SSSIZE-1]==0);
   }

   EMBDebug("embGetSymbolInfoByNumber done");
   return EMBCODE_RETURN_OK;
} /* embGetSymbolInfoByNumber */