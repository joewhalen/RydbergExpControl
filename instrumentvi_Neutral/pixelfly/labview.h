
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LABVIEW_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LABVIEW_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//#ifdef LABVIEW_EXPORTS
#define LABVIEW_API __declspec(dllexport) 
//#else
//#define LABVIEW_API __declspec(dllimport)
//#endif


//int WINAPI  fnLabview(void);

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */


HANDLE hdriver0,hdriver1, hdriver2, hdriver3, hevent, hhead;
HINSTANCE PccamLib=NULL;

int WINAPI   pinitboard(int board);
int WINAPI   pcloseboard(int board);
int WINAPI   pgetboardpar(int board, unsigned int *buf, int len);
int WINAPI   pgetsizes(int board, int *ccdxsize, int *ccdysize,
                int *actxsize, int *actysize,
                int *bit_pix);
int WINAPI    preadtemperature(int board, int *ccd);
int WINAPI    pwrrdorion(int board, int cmd, int *data);
int WINAPI	psetorionint(int board, int bufnr, int mode, unsigned char * cmnd, int len);
int WINAPI	pgetorionint(int board, int bufnr, int mode, unsigned char * data, int len);
int WINAPI	preadeeprom(int board, int mode, int adr, char * data);
int WINAPI	pwriteeeprom(int board, int mode, int adr, char data);
int WINAPI	psettimeouts(int board, DWORD dma, DWORD proc, DWORD head);


int WINAPI    psetbuffer_event(int board, int bufnr);
int WINAPI	psetdriver_event(int board, int mode);
int WINAPI   psetmode(int board,int mode,
			               int explevel,int exptime, 
			               int hbin,int vbin,
						   int gain,int offset,
						   int bit_pix,int shift);
int WINAPI   pstart_camera(int board); 
int WINAPI   pstop_camera(int board);
int WINAPI   ptrigger_camera(int board);

int WINAPI  pallocate_buffer(int board,int *bufnr,int *size);
int WINAPI  pfree_buffer(int board,int bufnr);
int WINAPI  pgetbuffer_status(int board,int bufnr,int mode,int *stat,int len);
int WINAPI  padd_buffer_to_list(int board,int bufnr,int size,int offset,int data);
int WINAPI  premove_buffer_from_list(int board,int bufnr);

int WINAPI  pmap_buffer(int board,int bufnr,int size,int offset,DWORD *linadr);
int WINAPI  punmap_buffer(int board,int bufnr);

#ifdef __cplusplus
}
#endif

