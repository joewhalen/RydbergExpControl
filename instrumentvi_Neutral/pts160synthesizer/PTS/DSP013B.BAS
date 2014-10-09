'============================================
'= PTS Control Program v013b 01-15-2000     =
'= Written by K3PGP http://www.k3pgp.org    =
'= Can be compiled by Microsoft Quick Basic =
'============================================
'Setup Port adr
'------------------------------------------------
'Printer Port 1 is at 378 Hex or 888 Decimal
'Printer Port 2 is at 278 Hex or 632 Decimal
'Printer Port 3 is at 3bc Hex or 956 Decimal
'------------------------------------------------
'You can use the calculator supplied with Windows
'to figure this stuff out.  Click on View and put
'it in Scientific mode!  Click Hex mode.
'Enter your hex number, then click Decimal.
'------------------------------------------------
  DataPort = 888              '378 hex printer port #1
  ControlPort = DataPort + 2  'Control port is ALWAYS base adr +2 !

'Setup CD4515 Control Data
'NOTE: Control Bits 1,2 & 8 are inverted!
'Only bits 1 and 2 are used here.
'--------------------------------------------------------------------
'                  Data Data
'  Name = Data     Sent Out               Function
'----------------- ---- ---- ----------------------------------------
  DataLatch = 11  '1011 0000 /LE Pin  1 CD4515 = Low  Latch Data
  DataAccept = 10 '1010 0001 /LE Pin  1 CD4515 = High Accept New Data
  StrobeOn = 11   '1011 0000 /En Pin 23 CD4515 = Low  Enable Output
  StrobeOff = 9   '1001 0010 /En Pin 23 CD4515 = High Disable Output

'Setup Strobe Adr
'All 15 are set up.  Only 5 (0-4) are used here.
'-----------------------------------------------
  DIM Strobe(15)
  FOR ctr = 0 TO 15
    Strobe(ctr) = ctr
  NEXT ctr

'Intialize
'---------
  OUT DataPort, 0
  OUT ControlPort, DataAccept AND StrobeOff
'+++++ OPEN "COM1:9600,N,8,2,RS,CS,DS,CD" FOR OUTPUT AS #2

'Max Freq of PTS
'---------------
 MaxFreq = 199

'IF frequency in Mhz & Khz
'-------------------------
  IFm = 40: IFk = 455

'Mixing Mode
'If SumDif = 1 then 1st Lo = Rx + IF
'If SumDif = 0 then 1st LO = Rx - IF
'NOTE: USB and LSB will swap when Mixing mode is changed !
'Program presently does NOT keep track of this.
'---------------------------------------------------------
 SumDif = 0

'Startup Freq
'------------
 Mhz = 144: Khz = 200: Hz = 0: mode$ = "U"

'Setup memory
'Any memory NOT programmed will default to 10.000 Mhz !
'------------------------------------------------------
  FOR ctr = 0 TO 10
    mm(ctr) = 10
    mk(ctr) = 0
    mh(ctr) = 0
    mo$(ctr) = mode$
  NEXT ctr

 mm(1) = 50: mk(1) = 200: mh(1) = 0: mo$(1) = "U"
 mm(2) = 144: mk(2) = 200: mh(2) = 0: mo$(2) = "U"
 mm(3) = 220: mk(3) = 200: mh(3) = 0: mo$(3) = "U"
'--------------------------------
'432 won't work yet with PTS-200!
'--------------------------------
 mm(4) = 432: mk(4) = 200: mh(4) = 0: mo$(4) = "U"
 mm(5) = 5: mk(5) = 0: mh(5) = 0: mo$(5) = "U"
 mm(6) = 10: mk(6) = 0: mh(6) = 0: mo$(6) = "U"
 mm(7) = 15: mk(7) = 0: mh(7) = 0: mo$(7) = "U"
 mm(8) = 3: mk(8) = 330: mh(8) = 0: mo$(8) = "U"
 mm(9) = 7: mk(9) = 335: mh(9) = 0: mo$(9) = "U"
 mm(10) = 3: mk(10) = 846: mh(10) = 0: mo$ = "U"

 CLS
 LOCATE 1, 1: PRINT "====DSP013b===="
 PRINT "|Mhz|Khz| Hz|M|"
 PRINT "|             |"
 PRINT "==============="
 GOSUB Convert: LOCATE 3, 2: GOSUB Display
 GOSUB SaveFreq
 IF SumDif = 0 THEN GOSUB MinusIFreq
 IF SumDif = 1 THEN GOSUB AddIFreq
 GOSUB Convert
'+++++ GOSUB GPIB
 GOSUB Parallel
 GOSUB RecallFreq

 ti$ = ""

LOOP1:
'+++++ IF LOC(2) THEN PRINT INPUT$(LOC(2), 1); : GOTO LOOP1
 in$ = INKEY$
 IF in$ = CHR$(27) GOTO SHUTDOWN
'+++++ ctr2 = ctr2 + 1: IF ctr2 = 4000 THEN ctr2 = 0: GOSUB GPIB: GOSUB Parallel
'+++++ GOSUB GPIB: GOSUB Parallel
'+++++ IF ti$ <> TIME$ THEN ti$ = TIME$: GOSUB GPIB: GOSUB Parallel
 IF ti$ <> TIME$ THEN ti$ = TIME$: GOSUB Parallel
 IF in$ = "" GOTO LOOP1

 IF in$ = "=" THEN Mhz = mm(0): Khz = mk(0): Hz = mh(0): mode$ = mo$(0)
'Store last freq. Do NOT update if recalling memory!
 IF (in$ > "9") THEN mm(0) = Mhz: mk(0) = Khz: mh(0) = Hz: mo$(0) = mode$

 GOSUB MemoryStore
 GOSUB MemoryRecall

 GOSUB Command: GOSUB Convert: LOCATE 3, 2: GOSUB Display

 GOSUB SaveFreq
 IF SumDif = 0 THEN GOSUB MinusIFreq
 IF SumDif = 1 THEN GOSUB AddIFreq
 GOSUB Convert
'+++++ GOSUB GPIB
 GOSUB Parallel
 GOSUB RecallFreq
 GOTO LOOP1

'+++++ GPIB:
 F$ = "F" + Mhz$ + "." + Khz$ + "." + Hz$ + ".0"
 PRINT #2, F$
 LOCATE 5, 1: PRINT F$
 RETURN

SaveFreq:
 M2 = Mhz: K2 = Khz: H2 = Hz: RETURN

RecallFreq:
 Mhz = M2: Khz = K2: Hz = H2: RETURN

Display:
 PRINT Mhz$ + "." + Khz$ + "." + Hz$ + " " + mode$
RETURN

Command:
 IF in$ = "k" THEN Hz = Hz + 1
 IF in$ = "," THEN Hz = Hz - 1
 IF in$ = "j" THEN Hz = Hz + 10
 IF in$ = "m" THEN Hz = Hz - 10: IF Hz < 0 THEN Hz = 990: Khz = Khz - 1
 IF in$ = "h" THEN Hz = Hz + 100
 IF in$ = "n" THEN Hz = Hz - 100: IF Hz < 0 THEN Hz = 900: Khz = Khz - 1

 IF in$ = "g" THEN Khz = Khz + 1
 IF in$ = "b" THEN Khz = Khz - 1
 IF in$ = "f" THEN Khz = Khz + 10
 IF in$ = "v" THEN Khz = Khz - 10: IF Khz < 0 THEN Khz = 990: Mhz = Mhz - 1
 IF in$ = "d" THEN Khz = Khz + 100
 IF in$ = "c" THEN Khz = Khz - 100: IF Khz < 0 THEN Khz = 900: Mhz = Mhz - 1

 IF in$ = "s" THEN Mhz = Mhz + 1
 IF in$ = "x" THEN Mhz = Mhz - 1
 IF in$ = "a" THEN Mhz = Mhz + 10
 IF in$ = "z" THEN Mhz = Mhz - 10

 IF in$ = "u" THEN mode$ = "U": GOSUB Parallel
 IF in$ = "l" THEN mode$ = "L": GOSUB Parallel
'IF In$ = "c" THEN mode$ = "C"

 IF in$ = "[" AND SumDif = 1 THEN SumDif = 0
 IF in$ = "]" AND SumDif = 0 THEN SumDif = 1

 IF SumDif = 0 AND Mhz > (MaxFreq + IFm) THEN Mhz = (MaxFreq + IFm + 9)
 IF SumDif = 1 AND Mhz > (MaxFreq - IFm) THEN Mhz = (MaxFreq - IFm - 9)

RETURN

Convert:
'=======
 IF Hz > 999 THEN Hz = 0: Khz = Khz + 1
 IF Hz < 0 THEN Hz = 999: Khz = Khz - 1: IF Khz < 0 THEN Khz = 999: Mhz = Mhz - 1

 IF Khz > 999 THEN Khz = 0: Mhz = Mhz + 1
 IF Khz < 0 THEN Khz = 999: Mhz = Mhz - 1

 IF Mhz > MaxFreq + IFm THEN Mhz = MaxFreq + IFm
 IF Mhz < 0 THEN Mhz = 0

 IF Mhz > 99 THEN Mhz$ = RIGHT$(STR$(Mhz), 3)
 IF Mhz < 100 THEN Mhz$ = "0" + RIGHT$(STR$(Mhz), 2)
 IF Mhz < 10 THEN Mhz$ = "00" + RIGHT$(STR$(Mhz), 1)

 IF Khz > 99 THEN Khz$ = RIGHT$(STR$(Khz), 3)
 IF Khz < 100 THEN Khz$ = "0" + RIGHT$(STR$(Khz), 2)
 IF Khz < 10 THEN Khz$ = "00" + RIGHT$(STR$(Khz), 1)
                                                    
 IF Hz > 99 THEN Hz$ = RIGHT$(STR$(Hz), 3)
 IF Hz < 100 THEN Hz$ = "0" + RIGHT$(STR$(Hz), 2)
 IF Hz < 10 THEN Hz$ = "00" + RIGHT$(STR$(Hz), 1)

RETURN

AddIFreq:
'=======
 Khz = Khz + IFk
 Mhz = Mhz + IFm
 IF Khz > 999 THEN Mhz = Mhz + 1: Khz = Khz - 1000
 IF Mhz > MaxFreq THEN Mhz = MaxFreq
 RETURN

MinusIFreq:
'=======
 Khz = Khz - IFk
 Mhz = Mhz - IFm
 IF Khz < 0 THEN Mhz = Mhz - 1: Khz = Khz + 1000
 IF Mhz > MaxFreq THEN Mhz = MaxFreq
 RETURN

MemoryStore:                         
'===========
 IF in$ = "!" THEN mm(1) = Mhz: mk(1) = Khz: mh(1) = Hz: mo$(1) = mode$: RETURN
 IF in$ = "@" THEN mm(2) = Mhz: mk(2) = Khz: mh(2) = Hz: mo$(2) = mode$: RETURN
 IF in$ = "#" THEN mm(3) = Mhz: mk(3) = Khz: mh(3) = Hz: mo$(3) = mode$: RETURN
 IF in$ = "$" THEN mm(4) = Mhz: mk(4) = Khz: mh(4) = Hz: mo$(4) = mode$: RETURN
 IF in$ = "%" THEN mm(5) = Mhz: mk(5) = Khz: mh(5) = Hz: mo$(5) = mode$: RETURN
 IF in$ = "^" THEN mm(6) = Mhz: mk(6) = Khz: mh(6) = Hz: mo$(6) = mode$: RETURN
 IF in$ = "&" THEN mm(7) = Mhz: mk(7) = Khz: mh(7) = Hz: mo$(7) = mode$: RETURN
 IF in$ = "*" THEN mm(8) = Mhz: mk(8) = Khz: mh(8) = Hz: mo$(8) = mode$: RETURN
 IF in$ = "(" THEN mm(9) = Mhz: mk(9) = Khz: mh(9) = Hz: mo$(9) = mode$: RETURN
 IF in$ = ")" THEN mm(10) = Mhz: mk(10) = Khz: mh(10) = Hz: mo$(10) = mode$: RETURN
 RETURN

MemoryRecall:
'============
'IF (in$ <= "9") THEN mm(0) = MHz: mk(0) = KHz: mh(0) = Hz: mo$(0) = mode$
 IF in$ = "1" THEN Mhz = mm(1): Khz = mk(1): Hz = mh(1): mode$ = mo$(1): RETURN
 IF in$ = "2" THEN Mhz = mm(2): Khz = mk(2): Hz = mh(2): mode$ = mo$(2): RETURN
 IF in$ = "3" THEN Mhz = mm(3): Khz = mk(3): Hz = mh(3): mode$ = mo$(3): RETURN
 IF in$ = "4" THEN Mhz = mm(4): Khz = mk(4): Hz = mh(4): mode$ = mo$(4): RETURN
 IF in$ = "5" THEN Mhz = mm(5): Khz = mk(5): Hz = mh(5): mode$ = mo$(5): RETURN
 IF in$ = "6" THEN Mhz = mm(6): Khz = mk(6): Hz = mh(6): mode$ = mo$(6): RETURN
 IF in$ = "7" THEN Mhz = mm(7): Khz = mk(7): Hz = mh(7): mode$ = mo$(7): RETURN
 IF in$ = "8" THEN Mhz = mm(8): Khz = mk(8): Hz = mh(8): mode$ = mo$(8): RETURN
 IF in$ = "9" THEN Mhz = mm(9): Khz = mk(9): Hz = mh(9): mode$ = mo$(9): RETURN
 IF in$ = "0" THEN Mhz = mm(10): Khz = mk(10): Hz = mh(10): mode$ = mo$(10): RETURN
 RETURN

'---------------

ParallelOld:
 pp = 888
 IF mode$ = "U" THEN f4 = 4
 IF mode$ = "L" THEN f4 = 7
 f1 = 4
 f2 = 0
 f3 = 4
'+++++ f4 = 7
 f5 = 0
 f6 = 0
 f7 = 0
 f8 = 0
'=====
 fi1 = (15 - f1) * 16
 fi2 = (15 - f2) * 16
 fi3 = 15 - f3
 fi4 = (15 - f4) * 16
 fi5 = 15 - f5
 fi6 = (15 - f6) * 16
 fi7 = 15 - f7
 fi8 = 15 - f8
'====> 10 Mhz & 1 Hz
 OUT pp, fi1 + fi8
 OUT pp + 2, 3
 OUT pp + 2, 11
'=====> 1 Mhz & 100 Khz
 OUT pp, fi2 + fi3
 OUT pp + 2, 15
 OUT pp + 2, 11
'=====> 10 Khz & 1 Khz
 OUT pp, fi4 + fi5
 OUT pp + 2, 9
 OUT pp + 2, 11
'=====> 100 hz & 10 Hz
 OUT pp, fi6 + fi7
 OUT pp + 2, 10
 OUT pp + 2, 11
'=====
 RETURN

Parallel:
'---------------------------------------------------------------
'Programming is in Hex / Binary active LOW!
'         Hex =  80 + 40 + 20 + 10 + 8 + 4 + 2 + 1
'     Decimal = 128 + 64 + 32 + 16 + 8 + 4 + 2 + 1
'---------------------------------------------------------------
'When programming 3 and 6 your output line would look like this:
' OUT DataPort, 128 + 64 + 0 + 0 + 8 + 0 + 0 + 1 (decimal)
'                         20h+ 10h= 30           (hex)
'                                     4h + 2h= 6 (hex)
'---------------------------------------------------------------
f1 = VAL(LEFT$(Mhz$, 1))
f2 = VAL(MID$(Mhz$, 2, 1))
f3 = VAL(RIGHT$(Mhz$, 1))
'-----
f4 = VAL(LEFT$(Khz$, 1))
f5 = VAL(MID$(Khz$, 2, 1))
f6 = VAL(RIGHT$(Khz$, 1))
'-----
f7 = VAL(LEFT$(Hz$, 1))
f8 = VAL(MID$(Hz$, 2, 1))
f9 = VAL(RIGHT$(Hz$, 1))

'Show where 1st LO is !
'----------------------
LOCATE 5, 1: PRINT "LO="; f1; f2; f3; "."; f4; f5; f6; "."; f7; f8; f9

'----- 100 / 10 MHz -----
Fo1 = (15 - f1) * 16
Fo2 = (15 - f2)
'----- 1 Mhz / 100 KHz -----
Fo3 = (15 - f3) * 16
Fo4 = 15 - f4
'----- 10 / 1 KHz -----
Fo5 = (15 - f5) * 16
Fo6 = 15 - f6
'----- 100 / 10 Hz -----
Fo7 = (15 - f7) * 16
Fo8 = 15 - f8
'----- 1 / 0.1 Hz -----
Fo9 = (15 - f9) * 16
Fo10 = 0                 '<0.1 Hz NOT used in this program!

'--------------------------------
'-----> 100 / 10 Mhz Digits -----
'--------------------------------
  OUT DataPort, Strobe(0)                   '<Controls which pin is active on the CD4515
  OUT ControlPort, DataAccept AND StrobeOff 'Enters data in CD4515
  OUT ControlPort, DataLatch AND StrobeOff  'Latches data in CD4515
'Remember to AND both DataLatch and StrobeOff or you will affect the other signal line!
'-------------------------------------------------
'PTS-160 has NO 100 Mhz digit.       10 Mhz digit goes to 15 (150 Mhz)
'               Not Used On PTS160   8+4=12x10 Mhz
'               ------------------   -------------
' OUT DataPort, 128 + 64 + 32 + 16 + 0 + 0 + 2 + 1
'-------------------------------------------------
' Next line is for PTS-200 and PTS 500!
'               10 x 10 = 100 Mhz   2x10= +20 Mhz
'               -----------------   -------------
  OUT DataPort, Fo1 + Fo2
'------------------------------------------------
  OUT ControlPort, DataLatch AND StrobeOn    '<Enable CD4515
  OUT ControlPort, DataLatch AND StrobeOff   '<Disable CD4515

'-----------------------------------
'-----> 1 Mhz / 100 Khz Digits -----
'-----------------------------------
  OUT DataPort, Strobe(1)
  OUT ControlPort, DataAccept AND StrobeOff
  OUT ControlPort, DataLatch AND StrobeOff
'               20 + 10 = +3 Mhz   4 = +400 Khz
'               ----------------   -------------
  OUT DataPort, Fo3 + Fo4
  OUT ControlPort, DataLatch AND StrobeOn
  OUT ControlPort, DataLatch AND StrobeOff

'------------------------------
'-----> 10 / 1 Khz Digits -----
'------------------------------
  OUT DataPort, Strobe(2)
  OUT ControlPort, DataAccept AND StrobeOff
  OUT ControlPort, DataLatch AND StrobeOff
'               40 + 10= +50 Khz   4 + 2= +6 Khz
'               ----------------   -------------
  OUT DataPort, Fo5 + Fo6
  OUT ControlPort, DataLatch AND StrobeOn
  OUT ControlPort, DataLatch AND StrobeOff

'-------------------------------
'-----> 100 / 10 Hz Digits -----
'-------------------------------
  OUT DataPort, Strobe(3)
  OUT ControlPort, DataAccept AND StrobeOff
  OUT ControlPort, DataLatch AND StrobeOff
'             40+20+10= +700 Hz   8 = +80 Hz
'               ---------------   -------------
  OUT DataPort, Fo7 + Fo8
  OUT ControlPort, DataLatch AND StrobeOn
  OUT ControlPort, DataLatch AND StrobeOff

'------------------------------
'-----> 1 / 0.1 Hz Digits -----
'------------------------------
  OUT DataPort, Strobe(4)
  OUT ControlPort, DataAccept AND StrobeOff
  OUT ControlPort, DataLatch AND StrobeOff
'               80 + 10 = 9 Hz    0.1 Hz Not used on PTS-160
'               ---------------   -------------
  OUT DataPort, Fo9 + Fo10
  OUT ControlPort, DataLatch AND StrobeOn
  OUT ControlPort, DataLatch AND StrobeOff
RETURN

SHUTDOWN:
'+++++ F$ = CHR$(1)
'+++++ PRINT #2, F$
'+++++ CLOSE #2
END

