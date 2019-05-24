/**
 *
 * GAMS - General Algebraic Modeling System C++ API
 *
 * Copyright (c) 2017 GAMS Software GmbH <support@gams.com>
 * Copyright (c) 2017 GAMS Development Corp. <support@gams.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

 /*
   Use this command to compile the example:
   g++ ./src/test.cc ./src/api/gdxcc.c -o prebuilds/test
 */

#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <napi.h>
#include "api/gdxcc.h"

using namespace std;
using namespace Napi;

static gdxStrIndexPtrs_t Indx;
static gdxStrIndex_t     IndxXXX;
static gdxValues_t       Values;

Napi::Promise ReadGDX(const Napi::CallbackInfo& info) {
	// setup default napi environment
	Napi::Env env = info.Env();
	auto deferred = Napi::Promise::Deferred::New(env);

	if (info.Length() < 2) {
		deferred.Reject(
			Napi::TypeError::New(env, "No path to GDX file given").Value()
		);
	} else if (!info[1].IsString()) {
		deferred.Reject(
      Napi::TypeError::New(env, "Invalid argument type").Value()
    );
	} else if (info.Length() == 2) {
    std::string dllString  = info[0].As<Napi::String>();
		std::string pathString = info[1].As<Napi::String>();
    char* path = new char[pathString.size() + 1];
		strcpy(path, pathString.c_str());

		// define all variables used
		gdxHandle_t PGX = NULL;
		char        Msg[GMS_SSSIZE], Sysdir[GMS_SSSIZE], VarName[GMS_SSSIZE];
		int         ErrNr;
		int         VarNr;
		int         SymNr;
		int         UniqReqs;
		int         NrRecs;
		int         N;
		int         Dim;
		int         VarTyp;
		int         D;
		int         S;
		// set directory for dynamilk link files
		strcpy(Sysdir, dllString.c_str());

		if (!gdxCreateD(&PGX, Sysdir, Msg, sizeof(Msg))) {
			deferred.Reject(
		    Napi::TypeError::New(env, "Could not load GDX library").Value()
		  );
			return deferred.Promise();
		}

		GDXSTRINDEXPTRS_INIT(IndxXXX, Indx);

		gdxOpenRead(PGX, path, &ErrNr);
		if (ErrNr) {
			deferred.Reject(
				Napi::TypeError::New(env, "Failed to open GDX").Value()
			);
			return deferred.Promise();
		}

		gdxSystemInfo(PGX, &SymNr, &UniqReqs);

		// init empty JS object
		Napi::Object data = Napi::Object::New(env);

		for (S = 1; S <= SymNr; S++) {
			VarNr = S;
			gdxSymbolInfo(PGX, VarNr, VarName, &Dim, &VarTyp);
			if (!gdxDataReadStrStart(PGX, VarNr, &NrRecs)) {
				char S[GMS_SSSIZE];
				gdxErrorStr(PGX, gdxGetLastError(PGX), S);
				deferred.Reject(
					Napi::TypeError::New(env, S).Value()
				);
				return deferred.Promise();
			}
			// add VarName as object property and assign empty vector of
			// length NrRecs as its value
			Napi::Array array = Napi::Array::New(env);
			data.Set(VarName, array);

			for (int i = 0; i < NrRecs; i++) {
				Napi::Object row = Object::New(env);
				gdxDataReadStr(PGX, Indx, Values, &N);
				for (D = 0; D < Dim; D++) {
					row.Set(D, Indx[D]);
				};
				row.Set("Value", Values[GMS_VAL_LEVEL]);
				array[i] = row;
			};
		};
		gdxDataReadDone(PGX);

		if ((ErrNr = gdxClose(PGX))) {
			deferred.Reject(
				Napi::TypeError::New(env, "Could not close GDX file.").Value()
			);
			return deferred.Promise();
		};

		deferred.Resolve(data);
	} else if (info.Length() == 3) {
		std::string dllString  = info[0].As<Napi::String>();
		std::string pathString = info[1].As<Napi::String>();
		std::string symbolString = info[2].As<Napi::String>();

		char* symbol = new char[symbolString.size() + 1];
		char* path = new char[pathString.size() + 1];

		strcpy(symbol, symbolString.c_str());
		strcpy(path, pathString.c_str());

		// define all variables used
		gdxHandle_t PGX = NULL;
		char        Msg[GMS_SSSIZE], Sysdir[GMS_SSSIZE], VarName[GMS_SSSIZE];
		int         ErrNr;
		int         VarNr;
		int         NrRecs;
		int         N;
		int         Dim;
		int         VarTyp;
		int         D;
		// set directory for dynamilk link files
		strcpy(Sysdir, dllString.c_str());

		if (!gdxCreateD(&PGX, Sysdir, Msg, sizeof(Msg))) {
			deferred.Reject(
				Napi::TypeError::New(env, "Could not load GDX library").Value()
			);
			return deferred.Promise();
		}

		GDXSTRINDEXPTRS_INIT(IndxXXX, Indx);

		gdxOpenRead(PGX, path, &ErrNr);
		if (ErrNr) {
			deferred.Reject(
				Napi::TypeError::New(env, "Could not read GDX file.").Value()
			);
			return deferred.Promise();
		}

		if (!gdxFindSymbol(PGX, symbol, &VarNr)) {
			deferred.Reject(
				Napi::TypeError::New(env, "Could not find symbol.").Value()
			);
			return deferred.Promise();
		}

		gdxSymbolInfo(PGX, VarNr, VarName, &Dim, &VarTyp);
		if (!gdxDataReadStrStart(PGX, VarNr, &NrRecs)) {
			char S[GMS_SSSIZE];
			gdxErrorStr(PGX, gdxGetLastError(PGX), S);
			deferred.Reject(
				Napi::TypeError::New(env, S).Value()
			);
			return deferred.Promise();
		}
		// add VarName as object property and assign empty vector of
		// length NrRecs as its value
		Napi::Array array = Napi::Array::New(env);

		for (int i = 0; i < NrRecs; i++) {
			Napi::Object row = Object::New(env);
			gdxDataReadStr(PGX, Indx, Values, &N);
			for (D = 0; D < Dim; D++) {
				row.Set(D, Indx[D]);
			};
			row.Set("Value", Values[GMS_VAL_LEVEL]);
			array[i] = row;
		};

		gdxDataReadDone(PGX);

		if ((ErrNr = gdxClose(PGX))) {
			deferred.Reject(
				Napi::TypeError::New(env, "Could not close GDX").Value()
			);
			return deferred.Promise();
		}

		deferred.Resolve(array);
	} else {
		deferred.Reject(
			Napi::TypeError::New(env, "Too many arguments passed.").Value()
		);
	}

	return deferred.Promise();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(
    Napi::String::New(env, "read"),
    Napi::Function::New(env, ReadGDX)
  );
  return exports;
}

NODE_API_MODULE(addon, Init)
