/*
 * MATLAB Compiler: 4.2 (R14SP2)
 * Date: Wed Aug 16 14:25:17 2006
 * Arguments: "-B" "macro_default" "-W" "lib:liba" "-T" "link:lib" "nlinfit.m"
 * "gaussfitfunctionerrorsslope.m" 
 */

#ifndef __liba_h
#define __liba_h 1

#if defined(__cplusplus) && !defined(mclmcr_h) && defined(__linux__)
#  pragma implementation "mclmcr.h"
#endif
#include "mclmcr.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_liba
#define PUBLIC_liba_C_API __global
#else
#define PUBLIC_liba_C_API /* No import statement needed. */
#endif

#define LIB_liba_C_API PUBLIC_liba_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_liba
#define PUBLIC_liba_C_API __declspec(dllexport)
#else
#define PUBLIC_liba_C_API __declspec(dllimport)
#endif

#define LIB_liba_C_API PUBLIC_liba_C_API


#else

#define LIB_liba_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_liba_C_API 
#define LIB_liba_C_API /* No special import/export declaration */
#endif

extern LIB_liba_C_API 
bool libaInitializeWithHandlers(mclOutputHandlerFcn error_handler,
                                mclOutputHandlerFcn print_handler);

extern LIB_liba_C_API 
bool libaInitialize(void);

extern LIB_liba_C_API 
void libaTerminate(void);


extern LIB_liba_C_API 
void mlxNlinfit(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_liba_C_API 
void mlxGaussfitfunctionerrorsslope(int nlhs, mxArray *plhs[],
                                    int nrhs, mxArray *prhs[]);


extern LIB_liba_C_API void mlfNlinfit(int nargout, mxArray** beta, mxArray** r
                                      , mxArray** J, mxArray** iter
                                      , mxArray* X, mxArray* y, mxArray* model
                                      , mxArray* beta_in, mxArray* options);

extern LIB_liba_C_API void mlfGaussfitfunctionerrorsslope(int nargout
                                                          , mxArray** Z
                                                          , mxArray* coeffs
                                                          , mxArray* data);

#ifdef __cplusplus
}
#endif

#endif
