// Filname: Example1.cpp
//
// SpinCore Technologies, Inc.
// 8/4/04
// http://www.spincore.com
//

// The following program code uses C Functions from 'pbdfuncs' to
// generate and execute a pulse sequence on the PulseBlasterESR-Pro board.

// All four BNC connectors are high for one clock period, then 
// low for the duration of instruction 1, or 17.66 ns.  
// BNC0 is then high for 34.96 ns while BNCs1-3 are low.  
// BNC0 then goes low until the end of instruction 2, or 5ns.
// All four BNC connectors are low for 40ns and the program repeats.

// Flags 0-20 are high for 20 ns, low for 80ns and repeat.


// Be sure to include the DLL (pb04pc.dll), the library file
// (pb04pc.lib), the header files (pb04pc.h and pbdfuncs.h), and source
// file (pbdfuncs.cpp) in the working directory of your C compiler .

// The largest value for the delay field of the pb_inst is 850ns.
// For longer delays, use the LONG_DELAY instruction.  The maximum value
// for the data field of the LONG_DELAY is 1048576.  Even longer delays can
// be achieved using the LONG_DELAY instruction inside of a loop.


#include <stdio.h>
#include "pbdfuncs.h"
#include "pbdfuncs.cpp"

void main(void)
{

	pb_init();  // Locates & Initializes the PulseBlasterESR Board

	int start;

	set_clock(300);  // Set Because the Board Operates at 300MHz

	start_programming(PULSE_PROGRAM);	// Prepare the Board to Receive
										// Pulse Program Instructions

	// Instruction 0 - Continue to instruction 1 in 20ns
	// Flags = 0x1FFFFF, OPCODE = CONTINUE
	// ONE_PERIOD equals 1 for bits 23-21 ... other valid constants are 
	// TWO_PERIODS, THREE_PERIODS, FOUR_PERIODS, FIVE_PERIODS, and ON 
	start = pb_inst(ONE_PERIOD|0x1FFFFF, CONTINUE, 0, 20*ns);

	// Instruction 1 - Continue to instruction 2 in 40ns
	// Flags = 0x1, OPCODE = CONTINUE
	// inst length = 40 ns
	
	// 40*ns length = delay value of 8 in instruction word
	// pulse in BNC 0 high for (8 + 4) * 3.33 - 1.5 * 3.33 = 34.96
	pb_inst(ON|0x1, CONTINUE, 0, 40*ns);

	// Instruction 2 - Branch to "start" (Instruction 0) in 40ns
	// 0x0, OPCODE = BRANCH, Target = start
	pb_inst(0x0, BRANCH, start, 40*ns);

	stop_programming();				// Finished Sending Instructions
	start_pb();						// Run the Program

	pb_close();			    // Release Control of the 
    								// PulseBlasterESR board

}

