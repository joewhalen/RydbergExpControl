-------------------------------------------------------------------
 P C O   AG   -     TECHNICAL  INFORMATION  DOCUMENT
-------------------------------------------------------------------


README FOR SOFTWARE/VERSION:  
CamWare V2.20 - Camera Application Software

FOR PCO PRODUCT/VERSION:
PCI-Interface-Board 520xP
PCI-Interface-Board 525xP
PCI-Interface-Board 540xP
SensiCam, Dicam Pro, PixelFly
pco.camera

DESCRIPTION:
This package includes a setup, which installs the following files
in your WINDOWS system directory and the selected application directory.

WINDOWS 2000/XP:
 all files are copied to "APPDIR"/CamWare (see list below)

Where APPDIR is the selected application directory
(e.g. c:\program files\digital camera toolbox\camware).

Registry:
Following registry entries will be created during runtime of the software:
 HKCU\Software\PCO\CamWare 
 HKCU\Software\PCO\PixelFly x
Where x depends on the current number of the PixelFly camera (If there is one!).
In case of SensiCam, Dicam Pro, HSFC Pro please take a look at the SensiCam
driver disk readme.

CONTENTS:

README.TXT     (This file)
SW_CAMWAREWIN_220 (zipArchive File Name)

Files Included in Archive          Size            Date          Time

..\
LOGODS			B16	 5243392	01.04.2004	16:18
DATA1			CAB	  303114	22.11.2007	14:30
DATA1			HDR	   20622	22.11.2007	14:30
DATA2			CAB	 6688695	22.11.2007	14:30
ENGINE32		CAB	  459544	10.11.2003	19:55
FIND_NAT		EXE	   53248	17.09.2007	12:10
INFO			TXT	    2598	19.10.2006	15:40
LAYOUT			BIN	     585	22.11.2007	14:30
LOGO			B16	  614784	03.09.2002	13:11
README			TXT	this file!		
SETUP			SKIN	   48096	13.11.2007	13:15
SETUP			BMP	   67878	13.11.2007	12:58
SETUP			EXE	  116880	10.11.2003	19:55
SETUP			IBT	  361737	22.11.2007	14:30
SETUP			INI	     462	22.11.2007	14:30
SETUP			INX	  196130	22.11.2007	14:30

Application Related Files:
README			TXT	    5095	12.11.2004	14:22
CAMWARE			CHM	 1612521	14.11.2007	15:45
CAMWARE			EXE	 3727360	19.11.2007	12:33
FLOWDICAMDOUBLE		TXT	     167	12.04.2001	13:02
FLOWDICAMSINGLE		TXT	     173	18.04.2001	15:28
FLOWPIXELFLY		TXT	     101	09.05.2001	16:55
FLOWSENSICAM		TXT	     101	18.07.2001	09:43
LIESMICH		TXT	    5380	12.11.2004	14:29

Application Related DLLs:
SC2_DLG			DLL	  573440	16.11.2007	11:28
CLSERMTX		DLL	   69632	02.06.2005	14:07
GDIPLUS			DLL	 1645320	04.05.2004	11:53
LIBDSW-1.0.3		DLL	   31232	23.01.2006	00:0,2
LIBMCL-4.5.0		DLL	 1159680	23.01.2006	00:0,2
LIBMPG-1.0.2		DLL	 1679872	23.01.2006	00:0,2
MTXCLSERMIL		DLL	   17408	02.06.2005	14:07
PCOCNV			DLL	  270336	16.11.2007	11:33
PCOLTDLG		DLL	  507904	16.11.2007	11:33
SC2_CAM			DLL	  229376	16.11.2007	11:29
SC2_CL_ME3		DLL	  102400	17.09.2007	11:33
SC2_CL_MTX		DLL	  319488	17.09.2007	11:33
SC2_CL_NAT		DLL	  106496	17.09.2007	11:33

Additional Tools:
LOUPE			HLP	   42562	02.02.1998	02:01
LOUPE			CNT	    1138	02.02.1998	02:01
LOUPE			EXE	  147456	02.02.1998	02:01

Pseudo Color Lookup Table Files:
LUT_RGBSOFT		LT1	    2097	22.12.2000	13:10
3300			LTC	     136	09.10.2000	16:20
3600			LTC	     136	09.10.2000	16:20
4000			LTC	     136	09.10.2000	16:20
4600			LTC	     136	09.10.2000	16:20
5600			LTC	     136	09.10.2000	16:20
7700			LTC	     136	09.10.2000	16:21
12000			LTC	     136	09.10.2000	16:21
15000			LTC	     136	09.10.2000	16:21
BG2200			LTC	     136	09.10.2000	16:23
BG2300			LTC	     136	09.10.2000	16:23
BG2500			LTC	     136	09.10.2000	16:23
BG2800			LTC	     136	09.10.2000	16:23
BG3300			LTC	     136	09.10.2000	16:23
BG4200			LTC	     136	09.10.2000	16:23
BG5600			LTC	     136	09.10.2000	16:22
BG9000			LTC	     136	09.10.2000	16:22
LUT_BGRSOFT		LT1	    2248	11.05.1998	12:18
LUT_BLUE		LT4	     768	22.05.1998	14:52
LUT_COMPRESSED		LT1	    2645	22.12.2000	13:10
LUT_EXPANDED		LT1	    3077	11.05.1998	11:18
LUT_EXPONENTIAL		LT1	    2263	11.05.1998	11:13
LUT_GREEN		LT2	    3162	22.12.2000	13:10
LUT_GREEN		LT4	     768	07.04.1995	18:24
LUT_GREEN_INVERS	LT3	     768	22.05.1998	13:41
LUT_INVERTED		LT1	    3176	22.12.2000	13:10
LUT_ISO7_COLOR		LT1	    2878	22.12.2000	13:10
LUT_LINEAR		LT1	    3162	22.12.2000	13:10
LUT_LINEAR		LT4	     768	07.04.1995	18:27
LUT_LOGARITHMIC		LT1	    3173	22.12.2000	13:10
LUT_MIDDLEQUADRANT_BW	LT1	    2603	11.05.1998	11:33
LUT_OVEREXPOSED		LT1	    2832	22.12.2000	13:10
LUT_QUANTIZED8_BW	LT1	    2694	11.05.1998	11:31
LUT_QUANTIZED8SOFT_COLOR	LT1	    2434	11.05.1998	11:56
LUT_QUANTIZED16_COLOR	LT1	    2510	11.05.1998	11:54
LUT_RAINBOW		LT1	    2418	22.12.2000	13:10
LUT_RED			LT4	     768	22.05.1998	13:50
LUT_RGB			LT1	    2046	11.05.1998	11:49


The 'Manufacturer' files are containing the camera manufacturer informations.

The 'Example' files can be loaded into the application to play around with the converter and
different file types.

The 'Application Related' files are the application itself including the help file and
neccessary runtime dlls.

The 'Additional Tool' files are an image converter and a display loupe.

The 'Pseudo Color Lookup Table' files can be used to convert b/w images into pseudo color images.

The 'Color Lookup Table' files can be used to set the color conversion to a certain color temperature.


Installation Instructions:

Copy the SW_CAMWAREWIN_220.zip to a distinct directory ( e.g. 'PCOTEMP').
Unzip the file.

1.  Select above directory ( e.g. 'PCOTEMP').
2.  Start 'setup.exe' to run setup.
3.  The necessary files will be installed automatically.
4.  Now you are ready to run the camera control software.

If you have problems during the installation, please check your firewall and / or disable it.

VERSION HISTORY:
Version 220:
- Various bugfixes
- Changed Lookuptable dialog
- Added Modulate Mode
- Vista compatibility

Version 219:
- Fixed 9999 problem while saving (Single file format is still fixed to _xxxx).
- MPeg FPS setting corrected to real configurable values.
- Settransferparameter in SC2 does not change the Transfer Parameter any longer
- Fixed error with small image sizes: min size set to 4096 Byte.
- Fixed error in KamSC2.cpp while setting ROI and getting ROI-Offset (Binning not kept in mind)
- PcCamDialog.cpp Doubleshutter two-way setting locked.
- KamSC2.cpp: Cancelstate in CamReady ignored.
- Added enum key from HKLM to support-file.
- Driverlogging starts before SC2 is opened.
- Timeout set to 7s for SC2

KNOWN BUGS:
- If flowfile is active changing settings is blocked. To work around this issue change settings stop
 and restart Camware, then activate record with flowfile.

Version 218:
- Segment confusion with pco.camera removed (auto exp. in context menu disabled while recording).
- Doubleshutter export can split bmp and tif, again.
- 16bit RGB export works for all conv. routines now.
- Fixed 9999 problem (Single file names are still bound to _xxxx format!)
- Mpeg FPS settings corrected.
- bugfixes

Version 217:
- Added Modulate Mode to pco.camera control dialog
- Added Sensicam EM functionality
- bugfixes

KNOWN BUGS:
- Exporting double shutter images produces files with double size, but same content for A and B.

Version 216 not released

Version 215:
- Changing the binning and/or ROI multiple times crashed CamWare used with SensiCam. Fixed.

Version 214:
- GUI changed
- bugfixes
- avi mpeg dialog enabled
- splitted file and view convert
- added mean value to histogram

Version 213:
- Default file type enhanced to MULTI-TIFF.
- Four color conversion algorythms are available.
- Export and save splitted to reflect application functionality and correct file types.
- Long lasting file operations can be stopped by pressing the ESC-key.
- Record stop event mode and noisefilter mode added.
- Export to avi (max. 2048x2048) and mpeg (DV resolution) added.
- bugfixes

Version 212:
- Corrected some errors while using more than one camera.
- various bugfixes

Version 210
- enabled CamLink (R) interface
- enabled up to eight cameras within one session
- various bugfixes

KNOWN LIMITATIONS:
- CamWare is not able to handle more than 9999 files up to now.

Version 204
- corrected some errors, one (doubleshutter) implemented with SensiCam QE in 203
- corrected the fps information for 1200hs

Version 203

- added command line /csc2=x to start with a different pco.camera connected (x=0,1,2...)
- enabled SensiCam QE color to be color
- reviewed SensiCam QE to work with CamWare
- released for PixelFly and SensiCam

Version 202

- added color conversion routines for pco.camera
- enhanced white balancing algorythm
- bugfixing (removed busreset for SC, PF; file handling issues)

KNOWN BUGS:
- Direct Record To File does not work with the pco.camera up to now.

Version 201

- added Exp = 1 / FPS mode for pco.1200hs
- added EM chip functionality

KNOWN BUGS:
- none

Version 200
- splitted up to 12x (PixelFly and SensiCam) and 20x (pco.camera)

KNOWN BUGS:
- none

Version 120

KNOWN BUGS:
- Crash in auto exposure mode
- Added: Preview for Doubleshutter mode, Mode for Fastshutter Modulation
- Fixed some unattractive behaviour

Version 110,111,112

KNOWN BUGS:
- After working with a doubleshutter PixelFly plug in a PixelFly without
  doubleshutter. Camware produces an error while initializing the camera.
- Averaging with start = 1 and stop = 2 in recorder triggers only first image.
- Some irregular behaviour with doubleshutter cameras.
- Window title is wrong after import closing window and import.
- Mathtoolbar off does not switch off math functionality inside the camera
  module.
- Import set does not update all images and the datawindow is in background.

Version 100

KNOWN BUGS:
- The menu items PgUp and PgDn are mixed up inside the local menu of the
  browser window.
- If you have the bw and color window open and they are overlayed and you
  change the picture size in the camera dialog and aquire images (single,
  preview or record) the content of the underlying window is not repainted.
- If you change printer settings in 'Print Setup' the settings are not
  transferred to the 'Print...' dialog! You have to apply the settings again.
- After you load a hotpixel file the application may crash.
- If you have installed more than one PCI-Interface-Board 52Xxx and you
  have only one camera (SensiCam...) switched on and you alter the actual
  picture size by changing the ROI or binning the recorder is not updated
  correctly. This results in corrupted images and application crash.
  Remove the unused board.

Not included features (Yet!):
Auto exposure mode. SensiCam in multichannel mode.

If you run into problems during the installation you could delete the 
following directory and its contents (if existent):
C:\program files\installshield installation information\{2C73D902-C93D-4893-912D-58241DDBA8AA}
'C:\program files\' depends on your sytem and might be different.

-------------------------------------------------------------------
 PCO AG
 DONAUPARK 11
 93309 KELHEIM / GERMANY
 PHONE +49 (9441) 20050
 FAX   +49 (9441) 200520
 info@pco.de, support@pco.de
 http://www.pco.de
-------------------------------------------------------------------
 DISCLAIMER
 THE ORIGIN OF THIS INFORMATION MAY BE INTERNAL OR EXTERNAL TO PCO.
 PCO MAKES EVERY EFFORT WITHIN ITS MEANS TO VERIFY THIS INFORMATION.
 HOWEVER, THE INFORMATION PROVIDED IN THIS DOCUMENT IS FOR YOUR
 INFORMATION ONLY. PCO MAKES NO EXPLICIT OR IMPLIED CLAIMS TO THE
 VALIDITY OF THIS INFORMATION.
-------------------------------------------------------------------
 Any trademarks referenced in this document are the property of
 their respective owners.
-------------------------------------------------------------------

