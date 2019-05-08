#include <node_api.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "api/gdxcc.h"

using namespace std;

static gdxStrIndexPtrs_t Indx;
static gdxStrIndex_t     IndxXXX;
static gdxValues_t       Values;

void ReportGDXError(gdxHandle_t PGX) {
	char S[GMS_SSSIZE];

	std::cout << "**** Fatal GDX Error" << endl;
	gdxErrorStr(PGX, gdxGetLastError(PGX), S);
	std::cout << "**** " << S << endl;
	exit(1);
}

void ReportIOError(int N, const std::string &msg) {
	std::cout << "**** Fatal I/O Error = " << N << " when calling " << msg << endl;
	exit(1);
}

void WriteData(gdxHandle_t PGX, const char *s, const double V) {
	strcpy(Indx[0], s);
	Values[GMS_VAL_LEVEL] = V;
	gdxDataWriteStr(PGX, (const char **)Indx, Values);
}


napi_value readGDX(napi_env, napi_callback_info info) {
  // pointer für Lesen/Schreiben auf gdx file
  gdxHandle_t PGX = NULL;
  char        Msg[GMS_SSSIZE], Producer[GMS_SSSIZE], Sysdir[GMS_SSSIZE], VarName[GMS_SSSIZE];
  int         ErrNr;
  int         VarNr;
  int         NrRecs;
  int         N;
  int         Dim;
  int         VarTyp;
  int         D;
  
  // nrSy Anzahl Symbole im gdx file, NrUel Anzahl elements in gdx file 
  int NrSy, NrUel;
  
  if (!gdxCreateD(&PGX, Sysdir, Msg, sizeof(Msg))) {
    cout << "**** Could not load GDX library" << endl << "**** " << Msg << endl;
    exit(1);
  }
   
  PGX.GetDLLVersion(Msg);
  cout << "Using GDX DLL version: " << Msg << endl;
  
  napi_value argv[1];
  size_t argc = 1;
  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  
  if (argc < 1) {
    napi_throw_error(env, "EINVAL", "Too few arguments");
    return NULL;
  }

  char FileName[1024];
  size_t str_len;

  if (napi_get_value_string_utf8(env, argv[0], (char *) &FileName, 1024, &str_len) != napi_ok) {
    napi_throw_error(env, "EINVAL", "Expected string");
    return NULL;
  }

  PGX.OpenRead(FileName, ErrNr);
  if (ErrNr) ReportIOError(ErrNr,"gdxOpenRead");
  PGX.FileVersion(Msg,Producer);
  cout << "GDX file written using version: " << Msg << endl;
  cout << "GDX file written by: " << Producer << endl;
  
  std::string VarName;
  int VarNr;
  int Dim;
  int VarTyp;
  
  // File infos abrufen
  PGX.gdxSystemInfo(Tptr,&NrSy,&NrUel);
  
  std::string* VarNames = malloc(sizeof(std::string)*(NrSy+1));
  int* VarNrs = malloc(sizeof(int)*(NrSy+1));
  int* Dims = malloc(sizeof(int)*(NrSy+1));
  int* VarTyps = malloc(sizeof(int)*(NrSy+1));
  
  if (!symbol) {
    for(int i = 1; i <= NrSy; i++;) {
      PGX.SymbolInfo(i,VarNames[i],Dims[i],VarTyps[i]);
      //VarName, Dim, und VarTyp haben jetzt coole werte
    }  
  } else {
    int check_symbol = PGX.FindSymbol(symbol,VarNr)
    //Check, ob symbol gefunden (PGX.FindSymbol == 0, nicht gefunden)
    if (!check_symbol) { 
      delete Varnames;
      delete VarNrs;
      delete Dims;
      delete VarTyps;
    
      exit(1); 
    }
    PGX.SymbolInfo(VarNr,VarName,Dim,VarTyp);
    //TODO: ein symbol lesen und dann return
    
    delete VarNames;
    delete VarNrs;
    delete Dims;
    delete VarTyps;
    return 0;
  }
  
  napi_env env;
   //Lesen (alle symbole)
   napi_status status_symbols; 
   napi_value obj_symbols;
   status_symbols = napi_create_object(env, &)
   
   napi_value arr_i;
   napi_status status_i; 
  for(int i = 1; i <= NrSy; i++;) {
    if (!PGX.DataReadStrStart(i,NrRecs)) ReportGDXError(PGX);
    //cout << "Variable X has " << NrRecs << " records" << endl;
    VarName = VarNames[i];
    VarNr = VarNrs[i];
    Dim = Dims[i];
    VarTyp = VarTyps[i];
    
    napi_value arr_i;
    status_i = napi_create_array(env,
                                &arr_i);
    napi_status status_j; 
    int j=1;
    //n_api_value für symbol i
    while (PGX.DataReadStr(Indx,Values,N)) {
      if (0 == Values[GMS_VAL_LEVEL]) continue; /* skip level 0.0 is default */
      //n_api_value für record j von symbol i
      napi_value arr_j;
      status_j = napi_create_array_with_length(env,
                                              Dim,
                                              &arr_j);
      //check status_j
      for (D=0; D<Dim; D++) {
        napi_value napi_Dval = napi_stringfromutf8(Indx[D]);
        status_j = napi_set_element(env,
                                 arr_j,
                                 D,
                                 napi_Dval);
      //check status_j
      }
      //cout << " = " << Values[GMS_VAL_LEVEL] << endl;
      
      status_i = napi_set_element(env,
                                    arr_i,
                                    j-1,
                                    napi_Dval);
      j++;
    }
    
    // symbol napi
    status_symbols = napi_set_property(env,
                                obj_symbols,
                                VarName,
                                arr_i);
    cout << "All solution values shown" << endl;
    PGX.DataReadDone();
  }
  
  delete Varnames;
  delete VarNrs;
  delete Dims;
  delete VarTyps;
  
  return obj_symbols;
}

 

napi_value init_all (napi_env env, napi_value exports ) {
  napi_value readGDX_fn;
  napi_create_funciton(env, NULL, 0, readGDX, NULL, &readGDX_fn);
  napi_set_named_property(env, exports, "readGDX", readGDX_fn);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init_all)