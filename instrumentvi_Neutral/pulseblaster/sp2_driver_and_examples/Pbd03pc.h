
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PBD03PC_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PBD03PC_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef PBD03PC_EXPORTS
#define PBD03PC_API __declspec(dllexport)
#else
#define PBD03PC_API __declspec(dllimport)
#endif

// The following will ensure that when building an application (or another
// DLL) using this DLL, the appropriate .LIB file will automatically be used
// when linking.
#ifndef _PBD03PC_NOAUTOLIB_
#ifdef _DEBUG
#pragma comment(lib, "pbd03pc.lib")
#else
#pragma comment(lib, "pbd03pc.lib")
#endif
#endif


// PulseBlaster's Exported DLL Functions ///////////////////////////

extern "C" {
PBD03PC_API int InitPMster(); //PBD03PC_Init(); 
PBD03PC_API int ClosePMster();//PBD03PC_Close();
PBD03PC_API int pb_outp(unsigned short address, int data);//PBD03PC_outp(unsigned short address, int data);
PBD03PC_API int pb_inp(unsigned short address);
}
////////////////////////////////////////////////////////////////////





