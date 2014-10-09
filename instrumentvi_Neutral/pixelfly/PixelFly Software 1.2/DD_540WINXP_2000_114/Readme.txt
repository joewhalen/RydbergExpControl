-------------------------------------------------------------------
                 P C O  AG
     TECHNICAL  INFORMATION  DOCUMENT
-------------------------------------------------------------------


README FOR SOFTWARE/VERSION:  
Driver Release 114

FOR PCO PRODUCT/VERSION:
PCO PCI-Interface-Board 540xP 

DESCRIPTION:
This packages includes the pccam.inf file to install the driver to your system.
It copies files and creates the neccessary registry entries.

WINDOWS XP:
WINDOWS 2000:
Files:
 pccwdm.sys is copied to "SYSDIR"\system32\drivers
 pccam.dll is copied to "SYSDIR"\system32
 pccamvb.dll is copied to "SYSDIR"\system32
 pco_ci.dll is copied to "SYSDIR"\system32
Registry:
 HKLM\system\CurrentControlSet\Services\pccwdm 


The system driver file pccwdm.sys is the primary interface to the Hardware of the
PCO PCI-Interface-Board 540xP.
The file pccam.dll includes a comfortable software interface to all applications.
The file pccamvb.dll must be used with VisualBasic applications.


CONTENTS:

Archive File Name: DD_540WINXP_2000_114.zip

Files Included                  Size          Date            Time

..\
      README.TXT     (This file)
  PCCAM               DLL       81.920     02.02.2007       14:53
  PCCAMVB             DLL       77.824     02.02.2007       14:54
  PCCWDM              INF        4.367     21.11.2006       11:19
  PCCWDM              SYS       70.528     29.01.2007       14:20
  PCCWDM_2K           SYS       70.400     29.01.2007       14:20
  PCO_CI2             DLL       69.632     29.03.2006       16:26
 

Installation Instructions:

Copy the DD_540WINXP_2000_114.zip to a distinct directory e.g PCO540. 
Unzip the file.

After installation of the PCO540 interface card the computer should automatically recognize
the new hardware and request you to insert the driver installation disk.

1.  Select the above directory (e.g. PCO540) with the hardware driver.
3.  Verify the selection of the file 'pccwdm.inf'.
4.  The necessary drivers will be installed now..
5.  Reboot your computer.
6.  You are now ready to install a camera control software.


During Installation you will get a message box 'Digital Signature not found'. Press the 'Yes'
button to continue installation.

(OPTIONAL: VERSION HISTORY)

Version 104
First release

Version 105
WindowsNT/2000
Driver creates a log file when started 
INIT starts correct when logged in as normal USER
includes INIT Function without additional boardtest

Version 106
Driver Start type changed 
DMA timeout value increased
Problems with SVGA cameras solved

Version 107
ImagePro driver problems solved
additional call to change Exposure time in async mode without stopping the camera
(this requires latest firmware revision for the PCI-board)
Init time increased, to solve problems with special camera types  

Version 108
new ccd_types added
new board_types with additional features added
power_down SDK functions included
shortest async exposure time 5us 

Version 109
new ccd_types added

Version 110
first version of WDM driver

Version 111
W2k memory problem solved
SDK Function can be called from C-programs 
new ccd_types added


Version 112
bug in get_sizes with vbinning>2 solved
driver IO communication (dma) adapted


Version 114
new ccd_type added
driver IO communication changed to support faster CPU's
new functions in dll to get settings of camera


KNOWN BUGS:
Not more than 2 Boards can be installed in one PC

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
