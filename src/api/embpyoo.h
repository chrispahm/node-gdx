/* include for Python Embedded Code library */
#ifndef EMBPYOO_H_
#define EMBPYOO_H_

#include "emblib.h"
#include "gclgms.h"
#include "gmdcc.h"
#include "Python.h"

typedef struct {
   PyObject_HEAD
   void *ptr;
} SwigPyObject;

/** embedded code library data
 *
 * The struct EMBCODE_Data has been predefined in emblib.h.
 * An instantiation of this struct is used to store the libraries own data.
 * In this example, we have to store the function mode that the library
 * is currently operating in.
 *
 * The type EMBCODE_DATA has been typedef'ed to struct EMBCODE_Data.
 */
struct EMBCODE_Data
{
   gmdHandle_t gmd;                                   /**< GMD Handle */
   PyObject*      py_main;                            /**< Python handle */
   PyObject*      py_gams;                            /**< Python handle to GAMS object */
   PyThreadState* pThreadState;                       /**< Python subinterpreter handle */
   void*          usrmem;                             /**< GAMS user memory */
   void*          outSymIterPtr;                      /**< Symbol iterator for symbol begin read by cmex */
   int            outOldKeyInt[GLOBAL_MAX_INDEX_DIM]; /**< Keys of last record read by cmex */
   int            outSymDim;                          /**< Symbol dimension being read by cmex*/
   int            outSymType;                         /**< Symbol type being read by cmex*/
   int            outSymUserInfo;                     /**< Symbol user info being read by cmex*/
   int            lastUel;                            /**< Last UEL known to GAMS */
   int            lastSymb;                           /**< Last Symbol known to GAMS */
   char           outEText[GMS_SSSIZE+1];             /**< Last element text of set symbol */
   double         gmdSpecVal[GMS_SVIDX_MAX];          /**< GMS special values for remapping to GAMS */
};

#endif /* EMBPYOO_H_ */
