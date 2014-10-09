2005/04/07, Pascal Mickelson, mickelsp@rice.edu

NOTE
These LabView VI's are provided as is, with no guarantee that they will work for you.  Use them at your own risk.  

Furthermore, no one guarantees support for these:  not me (Pascal), not NI (who makes LabView), not NIST (whose work some of these VI's are based upon), and not Spincore (who makes the PulseBlaster boards).  That said, should you have questions, you may e-mail me at mickelsp@rice.edu, and I'll do what I can to help.

Finally, you may not profit from the work included here.  The intellectual property is complicated.


VI's NECESSARY TO RUN THE PULSEBLASTER
PB_add_VLIW
PB-defines
pbcomm (this simply makes pbcomm8, pbcomm16, and pbcomm32 into a polymorphic VI)
pbcomm8
pbcomm16
pbcomm32
PBPCIcard_close
PBPCIcard_init
PBPCIcard_load
PBPCIcard_nostart
PBPCIcard_start
trapwithimagePCIstandalone

All of these VI's are made in LabView 7.1.  They are not backwards compatible with LabView 6.

The last VI, "trapwithimagePCIstandalone" is the highest level VI, and can be used to run the PulseBlaster without intimate knowledge of the guts of LabView.  However, depending on your installation, you may need "intimate knowledge" to configure the VI.  I've included some notes on that below.


RUNNING THE HIGH LEVEL VI
This VI allows one to program a PulseBlaster board's channels without having to deal with the "very long instruction word" (VLIW) commands directly.  One ought to consult the reference material in the "Programming the PulseBlaster: Instruction Set Architecture" section of the manual for more information.

The default settings should output HI-LO-HI in 10 ms intervals on even-numbered channels and LO-HI-LO on odd-numbered channels.  The default settings use the first 6 columns of input; note that the first 5 columns use the "Continue" command while the sixth column specifies "Go To" column zero to create the loop.

IMPORTANT:  this VI configures the PulseBlaster to look for an external trigger.  Provide a TTL pulse to the correct pin on the PulseBlaster board in order to make it do what you want.


CONFIGURING THE SUBVI's TO CORRECTLY TALK TO PULSEBLASTER
Initially, you will likely find it necessary to locate the library from which this VI needs to pull C-code to run the PulseBlaster.  The library is (probably) called "PDB03.dll" and (probably) resides in a directory like this one: C:\WINDOWS\system32

To connect to this library:
-open PBPCcard_close, PBPCcard_init, pbcomm8, pbcomm16, and pbcomm32.
-in each of these VI's, there will be a "Call Library Function Node". Right click on the node and select "Configure" from the menu.
-Enter the path for the library file (something like C:\WINDOWS\system32\PBD03PC.dll).
-From the function name menu, select "PBD03PC_Close" for PBPCcard_close.vi, "PDB03PC_Init" for PBPCcard_init, and "PBD03PC_outp" for all the other VI's.
-If you have different choices in the function name menu, you (probably) have the wrong .dll.  You need the c-style dll for your board.  In my case, I used the c-style dll from another board because one didn't exist (or at least it didn't work) for my board.
-Save the VI's and, in principle, the high level VI, "trapwithimagePCIstandalone", should work.