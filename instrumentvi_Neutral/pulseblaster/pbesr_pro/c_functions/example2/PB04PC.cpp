///////////////////////////////////////////////////////////////////////////////////////////////////
//
// PulseBlaster PB04PC Driver, SpinCore Tech, June 2004
//
// This is the PulseBlaster04 PCI DLL Driver (Ver01)
//		"PB04PC" PB=PulseBlaster, 04=BoardLayout4, PC=PCI
//			BoardLayouts:
//			01: Phil, PBDDS (ISA, USB)
//			02: PMster01 (PCI)
//			03: PMster03_c (PCI, Serial)
//          04: PB04 (PCI on stratix directly)
//
// Last Updated: 06/24/2004, Ryan Grimm
// 
// Notes:
//		The indended application of this device driver is to provide all necessary communications
//		ports to the PulseBlaster
//
///////////////////////////////////////////////////////////////////////////////////////////////////
// PB04PC.cpp : Defines the entry point for the DLL application.
//
//#include "stdafx.h"
#include "PB04PC.h"


// PulseBlaster Includes ///////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
////////////////////////////////////////////////////////////////////


// Windriver's Includes ////////////////////////////////////////////
#include "pmster02_pci_lib.h"
#include "pci_diag_lib.h"
#include <stdio.h>
////////////////////////////////////////////////////////////////////


// Hardware Info ///////////////////////////////////////////////////
#define PMSTER02_PCI_VENDID	0x10e8
#define	PMSTER02_PCI_DEVID	0x8875		// SpinCore's Device ID!
#define FREQ_BITS			32

#define KILO	1000
#define MEGA	1000000
////////////////////////////////////////////////////////////////////


	// Driver Globals
    int cmd;
    PMSTER02_PCI_HANDLE hPMSTER02_PCI = NULL;
    HANDLE hWD;
    BOOL fUseInt = FALSE; // do not install interrupts
    BOOL fOpenedWithInt = FALSE; // do not install interrupts
	// R/W
    UINT addr, data = 0;
    PMSTER02_PCI_ADDR ad_sp = 0;
    PMSTER02_PCI_MODE ad_mode = PMSTER02_PCI_MODE_DWORD;
	static char line[256];	// input of command from user


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}


// PulseBlaster's Private DLL Functions ///////////////////////////////////////////////////////////

void FatalError(int ErrType)
{
	printf("ERRORERRORERROR\n");
	// Rather then axit, provide messages?
	// exit( 1 );
}

void RegisterWinDriver()
{
	HANDLE hWD;
	WD_LICENSE lic;

	hWD = WD_Open();
	if (hWD!=INVALID_HANDLE_VALUE)
	{
		// SpinCore's License String
		strcpy(lic.cLicense, "6f1ea8b41bd21a55301a33889753e5e93cf4a970307073.Spincore Technologies, Inc.");
		WD_License(hWD, &lic);
		WD_Close(hWD);
	}
}



PMSTER02_PCI_HANDLE PMSTER02_PCI_LocateAndOpenBoard (DWORD dwVendorID, DWORD dwDeviceID, BOOL fUseInt)
{
    DWORD cards, my_card;
    PMSTER02_PCI_HANDLE hPMSTER02_PCI = NULL;

    if (dwVendorID==0)
    {
        printf ("Enter VendorID: ");
        fgets(line, sizeof(line), stdin);
        sscanf (line, "%x",&dwVendorID);
        if (dwVendorID==0) return NULL;

        printf ("Enter DeviceID: ");
        fgets(line, sizeof(line), stdin);
        sscanf (line, "%x",&dwDeviceID);
    }

    cards = PMSTER02_PCI_CountCards (dwVendorID, dwDeviceID);
    if (cards==0)	// No PMster PCI Card Found
    {
        printf ("%s", PMSTER02_PCI_ErrorString);
        return NULL;
    }

    else if (cards==1)	// Only 1 Card Inserted, OK to Proceed
        my_card = 1;
    else				// More than 1, Work it Out
    {
        UINT i;

        printf ("Found %u matching PCI cards\n", (UINT)cards);
        printf ("Select card (1-%u): ", (UINT)cards);
        i = 0;
        fgets(line, sizeof(line), stdin);
        sscanf (line, "%d",&i);
        if (i>=1 && i <=cards) my_card = i;
        else 
        {
            printf ("Choice out of range\n");
            return NULL;
        }
    }

	// printf ("PMSTER02_PCI PCI card found!\n");
    if (!(PMSTER02_PCI_Open (&hPMSTER02_PCI, dwVendorID, dwDeviceID, my_card - 1, fUseInt ? PMSTER02_PCI_OPEN_USE_INT : 0)))
        printf ("%s", PMSTER02_PCI_ErrorString);
    return hPMSTER02_PCI;
}
///////////////////////////////////////////////////////////////////////////////////////////////////



// PulseBlaster's Exported DLL Functions //////////////////////////////////////////////////////////

PB04PC_API int PB04PC_Init()
{

	// Register Version Info
	RegisterWinDriver();

    // make sure WinDriver is loaded
    if (!PCI_Get_WD_handle(&hWD)) return -1;
    WD_Close (hWD);

    hPMSTER02_PCI = PMSTER02_PCI_LocateAndOpenBoard(PMSTER02_PCI_VENDID, PMSTER02_PCI_DEVID, fUseInt);

	// Can't Init PMster
	if (!hPMSTER02_PCI) return -1;

	return 0;
}

PB04PC_API int PB04PC_Close()
{
	if (hPMSTER02_PCI)
	{
		PMSTER02_PCI_Close(hPMSTER02_PCI);
		return 0;
	}
	else	// None Opened to Close
		return -1;
}




PB04PC_API int PB04PC_outp(unsigned short address, unsigned char data)
{


    //write one byte ... function prototype is:
	//void PMSTER02_PCI_WriteByte (PMSTER02_PCI_HANDLE hPMSTER02_PCI, PMSTER02_PCI_ADDR addrSpace, DWORD dwOffset, BYTE data)

	if (hPMSTER02_PCI)
	{
		PMSTER02_PCI_WriteByte(hPMSTER02_PCI, ad_sp, address, data);
		return 0;
	}
	else
	{
		return -1;
	}

	/* 
	////////////////////////
	//OLD PBD03PC code 
	////////////////////////
	unsigned int MAX_RECV_TIMEOUT = 10;
	unsigned int RECV_START, RECV_TOGGLE, RECV_TIMEOUT = 0;
	int XFER_ERROR = 0;
	int RECV_POLLING = 0;

	unsigned int OGMB = 0x0C;
	unsigned int CHK_RECV = 0x1F;
	unsigned int SIG_TRNS = 0x0F;

	unsigned int CLEAR31 = 0x00000001;
	unsigned int CLEAR24 = 0x000000FF;
	unsigned int CLEAR28 = 0x0000000F;
	unsigned int SET_XFER = 0x01000000;

	unsigned int Temp_Address = address;
	unsigned int Temp_Data = data;

		// Prepare Address Transfer
		Temp_Address &= CLEAR28;
		Temp_Address |= SET_XFER;

		// Prepare Data Transfer
		Temp_Data &= CLEAR24;
		Temp_Data |= SET_XFER;

		// Clear the XFER bit (Should already be cleared)
		if (hPMSTER02_PCI)
		{
			PMSTER02_PCI_WriteByte(hPMSTER02_PCI, ad_sp, SIG_TRNS, 0);
		}
		else
		{
			return -1;
		}

		// Transfer Address
		
		// Read RECV bit from the Board
		if (hPMSTER02_PCI)
		{
			RECV_START = PMSTER02_PCI_ReadByte(hPMSTER02_PCI, ad_sp, CHK_RECV);
		}
		else
		{
			return -1;
		}
		RECV_START &= CLEAR31;	// Only Save LSB


		// Send Address to OGMB
		if (hPMSTER02_PCI)
		{
			PMSTER02_PCI_WriteDword(hPMSTER02_PCI, ad_sp, OGMB, Temp_Address);
		}
		else
		{
			return -1;
		}

		RECV_POLLING = 1;	// Set Polling Flag
		RECV_TIMEOUT = 0;
		while ((RECV_POLLING == 1) && (RECV_TIMEOUT < MAX_RECV_TIMEOUT)) 
		{
			// Check for Toggled RECV
			if (hPMSTER02_PCI)
			{
				RECV_TOGGLE = PMSTER02_PCI_ReadByte(hPMSTER02_PCI, ad_sp, CHK_RECV);
			}
			else
			{
				return -1;
			}
			RECV_TOGGLE &= CLEAR31;	// Only Save LSB
			if (RECV_TOGGLE != RECV_START) RECV_POLLING = 0;	// Finished if Different
			else RECV_TIMEOUT++;
			if (RECV_TIMEOUT == MAX_RECV_TIMEOUT) XFER_ERROR = -2;
		}

		// Transfer Complete (Clear) Signal
		if (hPMSTER02_PCI)
		{
			PMSTER02_PCI_WriteByte(hPMSTER02_PCI, ad_sp, SIG_TRNS, 0);
		}
		else
		{
			return -1;
		}

		// Transfer Data

		// Read RECV bit from the Board
		if (hPMSTER02_PCI)
		{
			RECV_START = PMSTER02_PCI_ReadByte(hPMSTER02_PCI, ad_sp, CHK_RECV);
		}7
		else
		{
			return -1;
		}
		RECV_START &= CLEAR31;	// Only Save LSB

		// Send Data to OGMB
		if (hPMSTER02_PCI)
		{
			PMSTER02_PCI_WriteDword(hPMSTER02_PCI, ad_sp, OGMB, Temp_Data);
		}
		else
		{
			return -1;
		}

		RECV_POLLING = 1;	// Set Polling Flag
		RECV_TIMEOUT = 0;
		while ((RECV_POLLING == 1) && (RECV_TIMEOUT < MAX_RECV_TIMEOUT)) 
		{
			// Check for Toggled RECV
			if (hPMSTER02_PCI)
			{
				RECV_TOGGLE = PMSTER02_PCI_ReadByte(hPMSTER02_PCI, ad_sp, CHK_RECV);
			}
			else
			{
				return -1;
			}
			RECV_TOGGLE &= CLEAR31;	// Only Save LSB
			if (RECV_TOGGLE != RECV_START) RECV_POLLING = 0;	// Finished if Different
			else RECV_TIMEOUT++;
			if (RECV_TIMEOUT == MAX_RECV_TIMEOUT) XFER_ERROR = -2;
		}

		// Transfer Complete (Clear) Signal
		if (hPMSTER02_PCI)
		{
			PMSTER02_PCI_WriteByte(hPMSTER02_PCI, ad_sp, SIG_TRNS, 0);
			//PMSTER02_PCI_WriteDword(hPMSTER02_PCI, ad_sp, pm_offset, Temp_Data);
		}
		else
		{
			return -1;
		}



	return XFER_ERROR;
	*/
}

///////////////////////////////////////////////////////////////////////////////////////////////////

