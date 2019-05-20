/** GAMS Embedded Code Python OO-API
 *
 * Python OO-Code Implementation using embedded code API.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "embpyoo.h"
#if defined(_WIN32)
# include <windows.h>
#endif


void embpyooInitFunc ( void );
void embpyooFiniFunc ( void );

#define GC_DLL_INIT_FUNC embpyooInitFunc
#define GC_DLL_FINI_FUNC embpyooFiniFunc

#include "gcdllinit.h"

static int GMSPYTHONMULTINST=0;

void embpyooInitFunc ( void )
{

   //printf("\ninit\n");fflush(stdout);
  const char* pyhome = getenv("GMSPYTHONHOME");
  const char* pymult = getenv("GMSPYTHONMULTINST");
  if (pyhome)
  {
     //printf("\ninit pyhome %s\n",pyhome);fflush(stdout);
     Py_SetPythonHome(Py_DecodeLocale(pyhome, NULL));
  }

  if (pymult && *pymult && pymult[0]=='1')
     GMSPYTHONMULTINST = 1;

  #if PY_MAJOR_VERSION >= 3
   Py_SetProgramName(L"");  /* optional but recommended */
#else
   Py_SetProgramName("");  /* optional but recommended */
#endif
   Py_InitializeEx(0);

   if (GMSPYTHONMULTINST)
      PyEval_InitThreads();
} /* embpyooInitFunc */

void embpyooFiniFunc ( void )
{
   //printf("\nfini\n");fflush(stdout);
   Py_FinalizeEx();
} /* embpyooFiniFunc */


//#define debug(msg)   embMessage(data->usrmem, msg)
#define debug(msg)

static EMBCODE_RETURN addUELS(
   EMBCODE_DATA*       data
)
{
   int gmdUELs;
   int i;
   if (!gmdInfo(data->gmd, GMD_NRUELS, &gmdUELs, NULL, NULL))
   {
     embMessage(data->usrmem, "Cannot query number of UELs");
     return EMBCODE_RETURN_SYSTEM;
   }
   //embMessage(data->usrmem, "UELs before %d and after %d", data->lastUel, gmdUELs);
   for (i=data->lastUel; i<gmdUELs; i++)
   {
      char buf[EMBCODE_STRSIZE];
      int uelCmex;

      if (!gmdGetUelByIndex(data->gmd,i+1,buf+1))
      {
        embMessage(data->usrmem, "Could not retrieve new %dth UEL", i);
        return EMBCODE_RETURN_SYSTEM;
      }
      buf[0] = strlen(buf+1);

      if (EMBCODE_RETURN_OK != embAddUelCB(buf , &uelCmex, data->usrmem))
      {
         embMessage(data->usrmem, "Could not register UEL %s", buf+1);
         return EMBCODE_RETURN_SYSTEM;
      }
      //embMessage(data->usrmem, "added UEL %s got number %d", buf+1, uelCmex);
      if ( i+1 != uelCmex )
      {
         embMessage(data->usrmem, "Unexpected mismatch of UEL numbers for UEL %s GMD:%d CMEX:%d", buf+1, i, uelCmex);
         return EMBCODE_RETURN_SYSTEM;
      }
   }
   data->lastUel = gmdUELs;

   return EMBCODE_RETURN_OK;

}

static EMBCODE_RETURN addGMDUels(EMBCODE_DATA* data, int GAMSUels)
{
   int i;
   for (i=data->lastUel; i<GAMSUels; i++)
   {
      char uel[GMS_UEL_IDENT_SIZE+1];
      int numuel;

      embGetUelCB(i+1,uel,sizeof(uel),data->usrmem);
      uel[uel[0]+1] = '\0';
      if (!gmdMergeUel(data->gmd, uel+1, &numuel))
      {
         embMessage(data->usrmem, "Could not add uel: %s.", uel);
         return EMBCODE_RETURN_SYSTEM;
      }
      assert(numuel==(i+1));
   }
   data->lastUel = GAMSUels;

   return EMBCODE_RETURN_OK;
}

static EMBCODE_RETURN addGMDSymbol(EMBCODE_DATA* data, int symNr)
{
   char symName[GMS_UEL_IDENT_SIZE];
   char symText[GMS_SSSIZE];
   int symDim;
   int symType;
   int symAccess;
   int symUserInfo;
   void *symPtr;

   if (EMBCODE_RETURN_OK != embGetSymbolInfoByNumber(symNr,&symAccess,&symDim,&symType,&symUserInfo,NULL,symName,sizeof(symName),symText,sizeof(symText),data->usrmem))
   {
      embMessage(data->usrmem, "Could not extract symbol information for symbol number %d.",symNr);
      return EMBCODE_RETURN_SYSTEM;
   }

   if (!symAccess)
   {
      return EMBCODE_RETURN_OK;
   }

   if ((symType!=GMS_DT_SET) && (symType!=GMS_DT_PAR) &&
       (symType!=GMS_DT_VAR) && (symType!=GMS_DT_EQU))
   {
      return EMBCODE_RETURN_OK;
   }

   if (GMS_DT_EQU == symType)
      symUserInfo -= GMS_EQUEOFFSET;

   if (!gmdAddSymbol(data->gmd,symName,symDim,symType,symUserInfo,symText,&symPtr))
   {
      embMessage(data->usrmem, "Could not add symbol: %s.",symName);
      return EMBCODE_RETURN_SYSTEM;
   }

   return EMBCODE_RETURN_OK;
}

/** Function to create embedded code library data.
 *
 * This function is called by the GAMS execution system after the library
 * has been loaded. Its purpose is to allocate and initialize the
 * library-specific data structure (struct EMBCODE_Data).
 */
EMBCODE_API void EMBCODE_CALLCONV XCreate(
   EMBCODE_DATA**       data             /**< buffer to store pointer to embedded code library data structure */
   )
{
   *data = (EMBCODE_DATA*) malloc(sizeof(EMBCODE_DATA));
   assert(*data != NULL);
}

/** Function to free embedded code library data.
 *
 * This function is called by the GAMS execution system before the library
 * is unloaded. Its purpose is to free the library-specific data.
 */
EMBCODE_API void EMBCODE_CALLCONV XFree(
   EMBCODE_DATA**       data             /**< pointer to pointer to function library data structure */
)
{
   if( data != NULL )
   {
      free(*data);
      *data = NULL;
   }
}

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embLibInit(
   EMBCODE_DATA*        data,          /**< embedded code library data structure */
   int                  version,       /**< version number */
   EMBCODEMessage_t     embMessagePtr, /**< error callback */
   void*                usrmem         /**< error callback user memory */
)
{
   assert(embMessagePtr != NULL);
   embMessageCB = embMessagePtr;

   assert(data != NULL);
   data->usrmem = usrmem;

   debug("LibInit Start");
   if( version < EMBVER ) // TODO why is version sometimes wrong?
   {
      embMessage(data->usrmem, "Client is too old for this Library.", version, EMBVER);
      return EMBCODE_RETURN_SYSTEM;
   }

   debug("LibInit End");
   return EMBCODE_RETURN_OK;
}

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
 * In difference to XCreate, this function can return a message
 * and error code to the GAMS execution system in case of an error.
 *
 * @return 0 if successful, <> 0 in case of error.
 */
EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embInit(
   EMBCODE_DATA*        data,          /**< embedded code library data structure */
   char*                args           /**< buffer of length 255 for library arguments (as Delphi string!) */
)
{
   char msg[GMS_SSSIZE];
   PyThreadState* pyMainThread=NULL;

   PyObject* pyGmd;
   int rc;
   char sysDir[GMS_SSSIZE+1];
   char pyExecStr[1024];
   debug("Init Start");
   assert(data != NULL);

   /* Create GMD object with UELs and symbols but no data */
   if (!gmdCreate(&(data->gmd), msg, sizeof(msg)))
   {
      embMessage(data->usrmem, "gmdCreate: %s.",msg);
      return EMBCODE_RETURN_SYSTEM;
   }
   // create a new interpreter
   if (GMSPYTHONMULTINST)
   {
      data->pThreadState = Py_NewInterpreter() ;
      assert(data->pThreadState != NULL) ;
      pyMainThread = PyThreadState_Swap(data->pThreadState);
   }

   data->py_main = PyImport_AddModule("__main__");
   rc = PyRun_SimpleString("from gamsemb import *");
   if (rc)
   {
      embMessage(data->usrmem, "Trouble executing 'from gamsemb import *'");
      return EMBCODE_RETURN_SYSTEM;
   }
   embGetInfoCB(EMB_SYSDIR,NULL,NULL,sysDir,sizeof(sysDir),data->usrmem);
   sysDir[(unsigned int)(unsigned char)sysDir[0]+1] = '\0';
   if (sysDir[strlen(sysDir)-1] == '\\') //remove trailing backslashes
       sysDir[strlen(sysDir)-1] = '\0';
   
   strcpy(pyExecStr, "_gamsCMEXDatabase = ECGAMSDatabase(r'");
   strcat(pyExecStr, sysDir+1);
   strcat(pyExecStr, "')");
   rc = PyRun_SimpleString(pyExecStr);
   if (rc)
   {
      embMessage(data->usrmem, "Trouble executing: %s", pyExecStr);
      return EMBCODE_RETURN_SYSTEM;
   }
   rc = PyRun_SimpleString("gams = _gamsCMEXDatabase");
   if (rc)
   {
      embMessage(data->usrmem, "Trouble executing 'gams = _gamsCMEXDatabase'");
      return EMBCODE_RETURN_SYSTEM;
   }
   data->py_gams = PyObject_GetAttrString(data->py_main, "_gamsCMEXDatabase");
   pyGmd = PyObject_GetAttrString(data->py_gams, "_gmd");
   ((SwigPyObject *)pyGmd)->ptr = &(data->gmd);
   rc = PyRun_SimpleString("gams._setSpecialValue()");
   if (rc)
   {
      embMessage(data->usrmem, "Trouble executing 'gams._setSpecialValue()'");
      return EMBCODE_RETURN_SYSTEM;
   }
   
   data->lastUel = 0;
   data->lastSymb = 0;
   gmdGetSpecialValues(data->gmd,data->gmdSpecVal);

   if (GMSPYTHONMULTINST)
      data->pThreadState = PyThreadState_Swap(pyMainThread);
   debug("Init End");
   return EMBCODE_RETURN_OK;
}

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embExecute(
   EMBCODE_DATA*         data,               /**< embedded code library data structure */
   int*                  gmsOutSymNr,        /**< output symbol numbers in GAMS enumeration (input) */
   int*                  gmsOutSymLoadType,  /**< load type for output symbol: xy x=1 Merge, x=0 Replace, y=1 DC, y=0 Filtered (output) */
   int                   size,               /**< length of gmsOutSymNr and gmsOutSymLoadType arrays */
   const char*           code,               /**< Python code to execute, for now script name (as Delphi string!) */
   char*                 args                /**< buffer of length 255 for library arguments (as Delphi string!) */
)
{
   int GAMSUels;
   int GAMSSymb;
   int i;
   PyThreadState* pyMainThread=NULL;

   assert(data != NULL);
   assert(embMessageCB != NULL);
   assert(embFindSymbolCB != NULL);
   assert(embDataReadRawStartCB != NULL);
   assert(embDataReadRawCB != NULL);
   assert(embDataReadDoneCB != NULL);
   assert(embGetElemTextCB != NULL);

   embGetInfoCB(EMB_NRUELS,&GAMSUels,NULL,NULL,0,data->usrmem);
   if (EMBCODE_RETURN_OK != addGMDUels(data, GAMSUels))
      return EMBCODE_RETURN_SYSTEM;

   embGetInfoCB(EMB_NRSYMBOLS,&GAMSSymb,NULL,NULL,0,data->usrmem);
   for (i=data->lastSymb; i<GAMSSymb; i++)
   {
      if (EMBCODE_RETURN_OK != addGMDSymbol(data, i+1))
         return EMBCODE_RETURN_SYSTEM;
   }
   data->lastSymb = GAMSSymb;

   debug("Execute Start");

#if 1
   gmdInitFromCMEX(data->gmd,(TFindSymbol_t) embFindSymbolCB,
                             (TDataReadRawStart_t) embDataReadRawStartCB,
                             (TDataReadRaw_t) embDataReadRawCB,
                             (TDataReadDone_t) embDataReadDoneCB,
                             (TGetElemText_t) embGetElemTextCB,
                             (TPrintLog_t) embMessageCB, data->usrmem);
#else
   {
   /* Fill input symbols */
   int numGMDSymbols;
   debug("Fill Symbols");
   if (!gmdInfo(data->gmd, GMD_NRSYMBOLS, &numGMDSymbols, NULL, NULL))
   {
      embMessage(data->usrmem, "Could not access number of symbols");
      return EMBCODE_RETURN_SYSTEM;
   }

   for (i=0; i<numGMDSymbols; i++)
   {
      void* symPtr;
      char symName[GMS_UEL_IDENT_SIZE+1];
      int symType;
      int symNr;
      int symRecs;
      int dimFirst;
      gdxValues_t values;
      gdxUelIndex_t keys;


      if (!gmdGetSymbolByIndex(data->gmd, i, &symPtr))
      {
        embMessage(data->usrmem, "Cannot access symbol at index position %d", i);
        return EMBCODE_RETURN_SYSTEM;
      }

      if (!gmdClearSymbol(data->gmd, symPtr))
      {
        embMessage(data->usrmem, "Cannot clear symbol number %d", i);
        return EMBCODE_RETURN_SYSTEM;
      }

      if (!gmdSymbolInfo(data->gmd, symPtr, GMD_NAME, NULL, NULL, symName+1))
      {
        embMessage(data->usrmem, "Cannot access symbol information (name) for symbol number %d", i);
        return EMBCODE_RETURN_SYSTEM;
      }
      symName[0] = strlen(symName+1);

      if (!gmdSymbolInfo(data->gmd, symPtr, GMD_TYPE, &symType, NULL, NULL))
      {
        embMessage(data->usrmem, "Cannot access symbol information (name) for symbol number %d", i);
        return EMBCODE_RETURN_SYSTEM;
      }

      if (EMBCODE_RETURN_OK != embFindSymbolCB(symName, &symNr, data->usrmem))
      {
         embMessage(data->usrmem, "Could not find symbol >%s< in GAMS", symName+1);
         return EMBCODE_RETURN_SYSTEM;
      }

      /* Start reading the size of the symbol and allocate accordingly */
      if (EMBCODE_RETURN_OK != embDataReadRawStartCB(symNr, &symRecs, data->usrmem))
      {
         embMessage(data->usrmem, "Could not start reading symbol >%s<", symName+1);
         return EMBCODE_RETURN_SYSTEM;
      }

      while (0==embDataReadRawCB(keys,values,&dimFirst,data->usrmem))
      {
         char buf[GMS_SSSIZE+1];

         if (GMS_DT_SET == symType && values[GMS_VAL_LEVEL] != 0.0)
         {
            embGetElemTextCB((int)values[GMS_VAL_LEVEL],buf,sizeof(buf),data->usrmem);
            buf[(unsigned int)(unsigned char)buf[0]+1] = '\0';
         }

         if (!gmdAddRecordRaw(data->gmd,symPtr,keys,values,buf+1))
         {
            embMessage(data->usrmem, "Problem adding data for symbol %s", symName+1);
            return EMBCODE_RETURN_SYSTEM;
         }
      }

      if (EMBCODE_RETURN_OK != embDataReadDoneCB(data->usrmem))
      {
         embMessage(data->usrmem, "Could not execute DataReadDone");
         return EMBCODE_RETURN_SYSTEM;
      }
   // gmdWriteGDX(data->gmd,"foo.gdx",0);
   }
   }
#endif
   debug("FillSymbol End");

   debug("Start Python");
   {
      char pyInFileName[EMBCODE_STRSIZE];
      char *pyScript;
      char pyArgs[EMBCODE_STRSIZE];

      strncpy(pyArgs,args+1,args[0]);
      pyArgs[(unsigned int)(unsigned char)args[0]] = '\0';

      strncpy(pyInFileName,code+1,code[0]);
      pyInFileName[(unsigned int)(unsigned char)code[0]] = '\0';

      /* Add two leading blanks to start a new block for the Python user code. */
      {
         FILE* pyFileIn = fopen(pyInFileName, "rb");
         char line[8192];
         int haveLines=0;
         long int fileSize;
         
         if (!pyFileIn)
         {
             embMessage(data->usrmem, "Could not open %s", pyInFileName);
             return EMBCODE_RETURN_SYSTEM;
         }

         fseek (pyFileIn, 0, SEEK_END);
         fileSize = ftell (pyFileIn);
         fseek (pyFileIn, 0, SEEK_SET);

         pyScript = malloc (fileSize+EMBCODE_STRSIZE+2560);
         if (NULL==pyScript)
         {
             embMessage(data->usrmem, "Could not allocate space for copying Python script");
             return EMBCODE_RETURN_SYSTEM;
         }
         sprintf(pyScript, "import sys\n_gamsCMEXDatabase._e_msg = ''\n_gamsCMEXDatabase._modSymList = {}\n_gamsCMEXDatabase.arguments='%s'\ntry:\n", pyArgs);
         while (fgets(line, sizeof(line), pyFileIn)) // fgets doesn't strip the terminating \n
         {
             if (0==haveLines) // add a first 
             {  char *p = line;
                while (*p && isspace(*p++)) ;
                if ((*p) && (*p != '#')) // we have some real code line
                   haveLines = 1;
             }
             strcat(pyScript,"  ");
             strcat(pyScript,line);
         }
         if (0==haveLines) // Empty Python file would cause compilation error because of empty try/except block
             strcat(pyScript, "  pass\n");
            
         strcat(pyScript, "except Exception as _einst:\n  _gamsCMEXDatabase._e_msg = str(_einst)\n  if _gamsCMEXDatabase._debug > 0:\n    print(_gamsCMEXDatabase._e_msg)\n    sys.stdout.flush()\n");

         fclose(pyFileIn);
      }

      if (GMSPYTHONMULTINST)
         pyMainThread = PyThreadState_Swap(data->pThreadState);
     {
      int rc;
      char* exception_msg;
      PyObject* py_exception_msg;

      gmdStartWriteRecording(data->gmd);
      rc = PyRun_SimpleString("my_stderr = sys.stderr\nsys.stderr = sys.stdout");
      if (rc)
      {
         embMessage(data->usrmem, "Trouble executing 'my_stderr = sys.stderr ...'");
         free(pyScript);
         return EMBCODE_RETURN_SYSTEM;
      }
      rc = PyRun_SimpleString(pyScript);
      free(pyScript);
      gmdStopWriteRecording(data->gmd);
      if (0==rc)
      {
         rc = PyRun_SimpleString("sys.stderr = my_stderr\nsys.stdout.flush()");
         if (rc)
         {
            embMessage(data->usrmem, "Trouble executing 'sys.stderr = my_stderr ...'");
            return EMBCODE_RETURN_SYSTEM;
         }
      }
      if(rc)
      {
         if (GMSPYTHONMULTINST)
            data->pThreadState = PyThreadState_Swap(pyMainThread);
         embMessage(data->usrmem, "Python error! Return code from Python execution: %d", rc);
         return EMBCODE_RETURN_SYSTEM;
      }
      py_exception_msg = PyObject_GetAttrString(data->py_gams, "_e_msg");
#if PY_MAJOR_VERSION >= 3
      if (PyUnicode_Check(py_exception_msg))
      {
        PyObject* temp_bytes = PyUnicode_AsEncodedString(py_exception_msg, "ASCII", "strict"); // Owned reference
        if (temp_bytes != NULL)
        {
           exception_msg = PyBytes_AS_STRING(temp_bytes); // Borrowed pointer
           if(strlen(exception_msg))
           {
              embMessage(data->usrmem, "Exception from Python: %s", exception_msg);
              Py_DECREF(temp_bytes);
              if (GMSPYTHONMULTINST)
                 data->pThreadState = PyThreadState_Swap(pyMainThread);
              return EMBCODE_RETURN_SYSTEM;
           }
           Py_DECREF(temp_bytes);
        }
      }
      else
      {
        if (GMSPYTHONMULTINST)
           data->pThreadState = PyThreadState_Swap(pyMainThread);
        embMessage(data->usrmem, "Unexpected exception message type");
        return EMBCODE_RETURN_SYSTEM;
      }
#else
      char* exception_msg = PyString_AsString(py_exception_msg);
      if(strlen(exception_msg))
      {
         if (GMSPYTHONMULTINST)
            data->pThreadState = PyThreadState_Swap(pyMainThread);
         embMessage(data->usrmem, "Exception from Python: %s", exception_msg);
         return EMBCODE_RETURN_SYSTEM;
      }
#endif
     }
   }

   /* Add potential new UELs from GMD */
   if (EMBCODE_RETURN_OK != addUELS(data))
   {
      if (GMSPYTHONMULTINST)
         data->pThreadState = PyThreadState_Swap(pyMainThread);
      embMessage(data->usrmem, "Could not add UELS");
      return EMBCODE_RETURN_SYSTEM;
   }

   /* Ensure that all output symbols have been set, provide load type */
   {
      int unAssigned = 0;
      PyObject *key, *value;
      int i, writtenTo, numGMDSymbols;
      PyObject* py_modSymList = PyObject_GetAttrString(data->py_gams, "_modSymList");
      Py_ssize_t pos;


      assert(PyDict_Check(py_modSymList));

      for (i=0; i<size; i++)
         gmsOutSymLoadType[i] = -1;

      pos = 0;
      while (PyDict_Next(py_modSymList, &pos, &key, &value))
      {
         void *symPtr;
         char buf[GMS_SSSIZE+1];
         int symbNr, loadType;
         int j;

         //assert(PyLong_Check(key));
         //assert(PyTuple_Check(value));
         //assert(PyTuple_Size(value)==2);
         //assert(PyLong_Check(PyTuple_GetItem(value,0)));
         //assert(PyLong_Check(PyTuple_GetItem(value,1)));

         symbNr    = PyLong_AsLong(key);
         loadType  = PyLong_AsLong(PyTuple_GetItem(value,0))*10;
         loadType += PyLong_AsLong(PyTuple_GetItem(value,1));

         if (!gmdGetSymbolByIndex(data->gmd, symbNr, &symPtr))
         {
            if (GMSPYTHONMULTINST)
               data->pThreadState = PyThreadState_Swap(pyMainThread);
            embMessage(data->usrmem, "Could not extract symbol number %d", symbNr);
            return EMBCODE_RETURN_SYSTEM;
         }
         if (!gmdSymbolInfo(data->gmd, symPtr, GMD_NAME, NULL, NULL, buf+1))
         {
            if (GMSPYTHONMULTINST)
               data->pThreadState = PyThreadState_Swap(pyMainThread);
            embMessage(data->usrmem, "Cannot access symbol information (name) for symbol number %d", symbNr);
            return EMBCODE_RETURN_SYSTEM;
         }
         buf[0] = strlen(buf+1);
         if (EMBCODE_RETURN_OK != embFindSymbolCB(buf, &symbNr, data->usrmem))
         {
            if (GMSPYTHONMULTINST)
               data->pThreadState = PyThreadState_Swap(pyMainThread);
            embMessage(data->usrmem, "Could not find symbol >%s< in GAMS", buf+1);
            return EMBCODE_RETURN_SYSTEM;
         }
         /* Find symbol in gmsOutSymNr */
         {
             int found = 0;
             for (j=0; j<size; j++)
             {
                if (gmsOutSymNr[j] == symbNr)
                {
                   gmsOutSymLoadType[j] = loadType;
                   found = 1;
                }
             }
             if (!found) /* not found */
             {
                embMessage(data->usrmem, "Python set symbol >%s< which is not in list of GAMS output symbols", buf+1);
                unAssigned++;
             }
         }
      }
      
      /* Iterate through all "written to" GMD symbols */
      if (!gmdInfo(data->gmd, GMD_NRSYMBOLS, &numGMDSymbols, NULL, NULL))
      {
         embMessage(data->usrmem, "Could not access number of symbols");
         return EMBCODE_RETURN_SYSTEM;
      }

      for (i=0; i<numGMDSymbols; i++)
      {
        char buf[GMS_SSSIZE+1];
        void *symPtr;
        int symbNr;
        if (!gmdGetSymbolByIndex(data->gmd, i, &symPtr))
        {
           if (GMSPYTHONMULTINST)
              data->pThreadState = PyThreadState_Swap(pyMainThread);
           embMessage(data->usrmem, "Could not extract symbol number %d", i);
           return EMBCODE_RETURN_SYSTEM;
        }
        if (!gmdSymbolInfo(data->gmd, symPtr, GMD_WRITTENTO, &writtenTo, NULL, NULL))
        {
           if (GMSPYTHONMULTINST)
              data->pThreadState = PyThreadState_Swap(pyMainThread);
           embMessage(data->usrmem, "Cannot access symbol information (writtento) for symbol number %d", i);
           return EMBCODE_RETURN_SYSTEM;
        }
        if (0==writtenTo)
           continue;
        
        
        if (!gmdSymbolInfo(data->gmd, symPtr, GMD_NAME, NULL, NULL, buf+1))
        {
           if (GMSPYTHONMULTINST)
              data->pThreadState = PyThreadState_Swap(pyMainThread);
           embMessage(data->usrmem, "Cannot access symbol information (name) for symbol number %d", i);
           return EMBCODE_RETURN_SYSTEM;
        }
        buf[0] = strlen(buf+1);
        if (EMBCODE_RETURN_OK != embFindSymbolCB(buf, &symbNr, data->usrmem))
        {
           if (GMSPYTHONMULTINST)
              data->pThreadState = PyThreadState_Swap(pyMainThread);
           embMessage(data->usrmem, "Could not find symbol >%s< in GAMS", buf+1);
           return EMBCODE_RETURN_SYSTEM;
        }
        /* Find symbol in gmsOutSymNr */
        {
            int j, found = 0;
            for (j=0; j<size; j++)
            {
               if (gmsOutSymNr[j] == symbNr)
               {
                  if (gmsOutSymLoadType[j]==-1)
                     gmsOutSymLoadType[j] = 1;
                  found = 1;
               }
            }
            if (!found) /* not found */
            {
               embMessage(data->usrmem, "Python OO-API symbol >%s< written to which is not in list of GAMS output symbols", buf+1);
               unAssigned++;
            }
        }
          
      }
      /* Check if requested GAMS output symbol has not been provided */
      for (i=0; i<size; i++)
      {
         if (-1 == gmsOutSymLoadType[i])
         {
            char buf[GMS_SSSIZE+1];
            embGetSymbolInfoCB(gmsOutSymNr[i],EMB_SYMBOLNAME,NULL,NULL,buf,sizeof(buf),data->usrmem);
            buf[(unsigned int)(unsigned char)buf[0]+1] = '\0';

            embMessage(data->usrmem, "Output symbol >%s< not set by Python code", buf+1);
            unAssigned++;
         }
      }
      if (unAssigned)
      {
         if (GMSPYTHONMULTINST)
            data->pThreadState = PyThreadState_Swap(pyMainThread);
         return EMBCODE_RETURN_SYSTEM;
      }
   }
   debug("Execute End");
   if (GMSPYTHONMULTINST)
      data->pThreadState = PyThreadState_Swap(pyMainThread);
   return EMBCODE_RETURN_OK;

}

/* Data access routines - Embedded Code -> GAMS */
EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embFindSymbol(
   EMBCODE_DATA*         data,               /**< embedded code library data structure */
   const char*           syId,               /**< Identifier name */
   int*                  syNr                /**< Identifier number */
)
{
   char symbol[EMBCODE_STRSIZE];
   void* symPtr;

   strncpy(symbol,syId+1,syId[0]);
   symbol[(unsigned int)(unsigned char)syId[0]] = '\0';

   *syNr = 0;
   if (!gmdFindSymbol(data->gmd, symbol, &symPtr))
   {
       embMessage(data->usrmem, "Could not find symbol >%s<", symbol);
       return EMBCODE_RETURN_SYSTEM;
   }
   if (!gmdSymbolInfo(data->gmd, symPtr, GMD_NUMBER, syNr, NULL, NULL))
   {
     embMessage(data->usrmem, "Cannot access symbol information (number) for symbol >%s<", symbol);
     return EMBCODE_RETURN_SYSTEM;
   }
   return EMBCODE_RETURN_OK;
}

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embDataReadRawStart(
   EMBCODE_DATA*         data,               /**< embedded code library data structure */
   int                   syNr,               /**< Identifier number */
   int*                  nrRecs              /**< Number of record */
)
{
   void* symPtr;
   int i;

   debug("embDataReadRawStart Start");
   if (!gmdGetSymbolByIndex(data->gmd, syNr, &symPtr))
   {
       embMessage(data->usrmem, "Could not extract symbol number %d", syNr);
       return EMBCODE_RETURN_SYSTEM;
   }
   if (!gmdSymbolInfo(data->gmd, symPtr, GMD_NRRECORDS, nrRecs, NULL, NULL))
   {
     embMessage(data->usrmem, "Cannot access symbol information (number of records) for symbol number %d", syNr);
     return EMBCODE_RETURN_SYSTEM;
   }

   if (!gmdSymbolInfo(data->gmd, symPtr, GMD_DIM, &(data->outSymDim), NULL, NULL))
   {
     embMessage(data->usrmem, "Cannot access symbol information (dim) for symbol number %d", syNr);
     return EMBCODE_RETURN_SYSTEM;
   }

   if (!gmdSymbolInfo(data->gmd, symPtr, GMD_USERINFO, &(data->outSymUserInfo), NULL, NULL))
   {
     embMessage(data->usrmem, "Cannot access symbol information (userinfo) for symbol number %d", syNr);
     return EMBCODE_RETURN_SYSTEM;
   }

   if (!gmdSymbolInfo(data->gmd, symPtr, GMD_TYPE, &(data->outSymType), NULL, NULL))
   {
     embMessage(data->usrmem, "Cannot access symbol information (type) for symbol number %d", syNr);
     return EMBCODE_RETURN_SYSTEM;
   }

   for (i=0; i<data->outSymDim; i++)
      data->outOldKeyInt[i] = -1;

   if (*nrRecs > 0)
   {
      if (!gmdFindFirstRecord (data->gmd, symPtr, &(data->outSymIterPtr)))
      {
        embMessage(data->usrmem, "Cannot access symbol information for symbol number %d", syNr);
        return EMBCODE_RETURN_SYSTEM;
      }
   }
   else
      data->outSymIterPtr = NULL;

   debug("embDataReadRawStart End");

   return EMBCODE_RETURN_OK;
}

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embDataReadRaw(
   EMBCODE_DATA*         data,               /**< embedded code library data structure */
   int                   keyInt[],           /**< uels */
   double                values[],           /**< values */
   int*                  dimFirst            /**< First dimension that changed from last call */
)
{
   debug("embDataReadRaw Start");

   if (NULL==data->outSymIterPtr)
   {
      if (0==data->outSymDim)
      {
         *dimFirst = 1;
         if (GMS_DT_VAR==data->outSymType)
         {
            if ((data->outSymUserInfo >= 0) && (data->outSymUserInfo < GMS_VARTYPE_MAX))
               memcpy(values,gmsDefRecVar[data->outSymUserInfo],sizeof(double)*GMS_VAL_MAX);
         }
         else if (GMS_DT_EQU==data->outSymType)
         {
            if ((data->outSymUserInfo >= 0) && (data->outSymUserInfo < GMS_EQUTYPE_MAX))
               memcpy(values,gmsDefRecEqu[data->outSymUserInfo],sizeof(double)*GMS_VAL_MAX);
         }
         else
            memset(values,0,sizeof(double)*GMS_VAL_MAX);
         return EMBCODE_RETURN_OK;
      }
      else
         return EMBCODE_RETURN_SYSTEM;
   }
   else
   {
      if (!gmdGetRecordRaw(data->gmd,data->outSymIterPtr,data->outSymDim,keyInt,values))
      {
        embMessage(data->usrmem, "Cannot access record information");
        return EMBCODE_RETURN_SYSTEM;
      }
      if (data->outSymDim <= 1)
         *dimFirst = 1;
      else
      {
         int i;
         for (i=1; i<=data->outSymDim; i++)
            if (keyInt[i-1] != data->outOldKeyInt[i-1])
               break;
         assert(i<=data->outSymDim);
         *dimFirst = i;
         for (;i<=data->outSymDim; i++)
            data->outOldKeyInt[i-1] = keyInt[i-1];
      }
      if ((GMS_DT_SET == data->outSymType) && (values[GMS_VAL_LEVEL] != 0.0))
         gmdGetElemText(data->gmd,data->outSymIterPtr,data->outEText+1);

      if (GMS_DT_PAR == data->outSymType)
      {
         if (values[GMS_VAL_LEVEL] != values[GMS_VAL_LEVEL])
            values[GMS_VAL_LEVEL] = GMS_SV_NA;
         else if (values[GMS_VAL_LEVEL] == data->gmdSpecVal[GMS_SVIDX_EPS])
            values[GMS_VAL_LEVEL] = GMS_SV_EPS;
         else if (values[GMS_VAL_LEVEL] == data->gmdSpecVal[GMS_SVIDX_PINF])
            values[GMS_VAL_LEVEL] = GMS_SV_PINF;
         else if (values[GMS_VAL_LEVEL] == data->gmdSpecVal[GMS_SVIDX_MINF])
            values[GMS_VAL_LEVEL] = GMS_SV_MINF;
      }

      if ((GMS_DT_VAR == data->outSymType) || (GMS_DT_EQU == data->outSymType))
      {
         int suf;
         for (suf=0; suf<GMS_VAL_MAX; suf++)
         {
            if (values[suf] != values[suf])
               values[suf] = GMS_SV_NA;
            else if (values[suf] == data->gmdSpecVal[GMS_SVIDX_EPS])
               values[suf] = GMS_SV_EPS;
            else if (values[suf] == data->gmdSpecVal[GMS_SVIDX_PINF])
               values[suf] = GMS_SV_PINF;
            else if (values[suf] == data->gmdSpecVal[GMS_SVIDX_MINF])
               values[suf] = GMS_SV_MINF;
         }
      }
      
      if (!gmdRecordMoveNext(data->gmd,data->outSymIterPtr))
      {
         gmdFreeSymbolIterator(data->gmd,data->outSymIterPtr);
         data->outSymIterPtr = NULL;
      }
      return EMBCODE_RETURN_OK;
   }
}

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embGetElemText(
   EMBCODE_DATA*         data,               /**< embedded code library data structure */
   int                   textNr,             /**< text number */
   char*                 eText               /**< Text */
 )
 {
    // textNr not used!!! We assume that we query the text from the last embDataReadRaw record
    debug("embGetElemText Start");
    strcpy(eText+1,data->outEText+1);
    eText[0] = strlen(eText+1);
    debug("embGetElemText end");
    return EMBCODE_RETURN_OK;
 }

 EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embDataReadDone(
   EMBCODE_DATA*         data                /**< embedded code library data structure */
)
{
   debug("embDataReadDone Begin");
   debug("embDataReadDone End");

   return EMBCODE_RETURN_OK;
}

EMBCODE_API EMBCODE_RETURN EMBCODE_CALLCONV embFini(
   EMBCODE_DATA*         data                /**< embedded code library data structure */
)
{
   debug("embFini Start");
   gmdFree(&(data->gmd));
   data->gmd=NULL;
   debug("embFini End");
   return EMBCODE_RETURN_OK;
}
