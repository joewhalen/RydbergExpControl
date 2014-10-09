/*
 * MATLAB Compiler: 4.2 (R14SP2)
 * Date: Wed Aug 16 14:25:17 2006
 * Arguments: "-B" "macro_default" "-W" "lib:liba" "-T" "link:lib" "nlinfit.m"
 * "gaussfitfunctionerrorsslope.m" 
 */

#include <stdio.h>
#define EXPORTING_liba 1
#include "liba.h"
#ifdef __cplusplus
extern "C" {
#endif
extern const unsigned char __MCC_liba_public_data[];
extern const char *__MCC_liba_name_data;
extern const char *__MCC_liba_root_data;
extern const unsigned char __MCC_liba_session_data[];
extern const char *__MCC_liba_matlabpath_data[];
extern const int __MCC_liba_matlabpath_data_count;
extern const char *__MCC_liba_classpath_data[];
extern const int __MCC_liba_classpath_data_count;
extern const char *__MCC_liba_lib_path_data[];
extern const int __MCC_liba_lib_path_data_count;
extern const char *__MCC_liba_mcr_runtime_options[];
extern const int __MCC_liba_mcr_runtime_option_count;
extern const char *__MCC_liba_mcr_application_options[];
extern const int __MCC_liba_mcr_application_option_count;
#ifdef __cplusplus
}
#endif


static HMCRINSTANCE _mcr_inst = NULL;


#if defined( _MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__) || defined(__LCC__)
#include <windows.h>

static char path_to_dll[_MAX_PATH];

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, void *pv)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        char szDllPath[_MAX_PATH];
        char szDir[_MAX_DIR];
        if (GetModuleFileName(hInstance, szDllPath, _MAX_PATH) > 0)
        {
             _splitpath(szDllPath, path_to_dll, szDir, NULL, NULL);
            strcat(path_to_dll, szDir);
        }
	else return FALSE;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
    }
    return TRUE;
}
#endif
static int mclDefaultPrintHandler(const char *s)
{
    return fwrite(s, sizeof(char), strlen(s), stdout);
}

static int mclDefaultErrorHandler(const char *s)
{
    int written = 0, len = 0;
    len = strlen(s);
    written = fwrite(s, sizeof(char), len, stderr);
    if (len > 0 && s[ len-1 ] != '\n')
        written += fwrite("\n", sizeof(char), 1, stderr);
    return written;
}


/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_liba_C_API 
#define LIB_liba_C_API /* No special import/export declaration */
#endif

LIB_liba_C_API 
bool libaInitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler
)
{
    if (_mcr_inst != NULL)
        return true;
    if (!mclmcrInitialize())
        return false;
    if (!mclInitializeComponentInstance(&_mcr_inst, __MCC_liba_public_data,
                                        __MCC_liba_name_data,
                                        __MCC_liba_root_data,
                                        __MCC_liba_session_data,
                                        __MCC_liba_matlabpath_data,
                                        __MCC_liba_matlabpath_data_count,
                                        __MCC_liba_classpath_data,
                                        __MCC_liba_classpath_data_count,
                                        __MCC_liba_lib_path_data,
                                        __MCC_liba_lib_path_data_count,
                                        __MCC_liba_mcr_runtime_options,
                                        __MCC_liba_mcr_runtime_option_count,
                                        true, NoObjectType, LibTarget,
                                        path_to_dll, error_handler,
                                        print_handler))
        return false;
    return true;
}

LIB_liba_C_API 
bool libaInitialize(void)
{
    return libaInitializeWithHandlers(mclDefaultErrorHandler,
                                      mclDefaultPrintHandler);
}

LIB_liba_C_API 
void libaTerminate(void)
{
    if (_mcr_inst != NULL)
        mclTerminateInstance(&_mcr_inst);
}


LIB_liba_C_API 
void mlxNlinfit(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    mclFeval(_mcr_inst, "nlinfit", nlhs, plhs, nrhs, prhs);
}

LIB_liba_C_API 
void mlxGaussfitfunctionerrorsslope(int nlhs, mxArray *plhs[],
                                    int nrhs, mxArray *prhs[])
{
    mclFeval(_mcr_inst, "gaussfitfunctionerrorsslope",
             nlhs, plhs, nrhs, prhs);
}

LIB_liba_C_API 
void mlfNlinfit(int nargout, mxArray** beta, mxArray** r, mxArray** J
                , mxArray** iter, mxArray* X, mxArray* y
                , mxArray* model, mxArray* beta_in, mxArray* options)
{
    mclMlfFeval(_mcr_inst, "nlinfit", nargout, 4, 5, beta,
                r, J, iter, X, y, model, beta_in, options);
}

LIB_liba_C_API 
void mlfGaussfitfunctionerrorsslope(int nargout, mxArray** Z
                                    , mxArray* coeffs, mxArray* data)
{
    mclMlfFeval(_mcr_inst, "gaussfitfunctionerrorsslope",
                nargout, 1, 2, Z, coeffs, data);
}
