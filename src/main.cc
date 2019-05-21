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

void ReportGDXError(gdxHandle_t PGX) {
	char S[GMS_SSSIZE];

	std::cout << "**** Fatal GDX Error" << endl;
	gdxErrorStr(PGX, gdxGetLastError(PGX), S);
	std::cout << "**** " << S << endl;
	exit(1);
}

void ReportIOError(int N, const std::string &msg) {
	std::cout << "**** Fatal I/O Error = " << N << " when calling "
	          << msg << endl;
	exit(1);
}


Napi::Promise ReadGDX(const Napi::CallbackInfo& info) {
	// setup default napi environment
	Napi::Env env = info.Env();
	auto deferred = Napi::Promise::Deferred::New(env);

	if (info.Length() != 1) {
		deferred.Reject(
			Napi::TypeError::New(env, "No path to GDX file given").Value()
		);
	} else if (!info[0].IsString()) {
		deferred.Reject(
      Napi::TypeError::New(env, "Invalid argument type").Value()
    );
	} else {
		std::string pathString = info[0].As<Napi::String>();
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
		strcpy(Sysdir, "dll");

		if (!gdxCreateD(&PGX, Sysdir, Msg, sizeof(Msg))) {
			cout << "**** Could not load GDX library" << endl << "**** "
					 << Msg << endl;
			exit(1);
		}

		GDXSTRINDEXPTRS_INIT(IndxXXX, Indx);

		gdxOpenRead(PGX, path, &ErrNr);
		if (ErrNr) ReportIOError(ErrNr, "gdxOpenRead");

		gdxSystemInfo(PGX, &SymNr, &UniqReqs);

		// init empty JS object
		Napi::Object data = Napi::Object::New(env);

		for (S = 1; S <= SymNr; S++) {
			VarNr = S;
			gdxSymbolInfo(PGX, VarNr, VarName, &Dim, &VarTyp);
			if (!gdxDataReadStrStart(PGX, VarNr, &NrRecs)) ReportGDXError(PGX);
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

		if ((ErrNr = gdxClose(PGX))) ReportIOError(ErrNr, "gdxClose");

		deferred.Resolve(data);
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
