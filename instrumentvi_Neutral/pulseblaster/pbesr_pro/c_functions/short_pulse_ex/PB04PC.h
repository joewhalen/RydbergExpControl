
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PBD03PC_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PBD03PC_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef PB04PC_EXPORTS
#define PB04PC_API __declspec(dllexport)
#else
#define PB04PC_API __declspec(dllimport)
#endif

// The following will ensure that when building an application (or another
// DLL) using this DLL, the appropriate .LIB file will automatically be used
// when linking.
#ifndef _PB04PC_NOAUTOLIB_
#ifdef _DEBUG
#pragma comment(lib, "PB04PC.lib")
#else
#pragma comment(lib, "PB04PC.lib")
#endif
#endif


// PulseBlaster's Exported DLL Functions ///////////////////////////
PB04PC_API int PB04PC_Init();
PB04PC_API int PB04PC_Close();
PB04PC_API int PB04PC_outp(unsigned short address, unsigned char data);
////////////////////////////////////////////////////////////////////





