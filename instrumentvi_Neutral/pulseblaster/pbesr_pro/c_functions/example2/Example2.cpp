// Filname: Example2.cpp
//
// SpinCore Technologies, Inc.
// 8/4/04
// http://www.spincore.com
//

// The following program code uses C Functions from 'pbdfuncs' to
// generate and execute a pulse sequence on the PulseBlasterESRPro board.

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

		if (pb_init() != 0)
			printf("--- Error Initializing PulseBlaster ---\n");

		// Check for proper initialization of PulseBlasterESR

		// Set clock frequency
		set_clock(300);

		//Begin pulse program
		start_programming(PULSE_PROGRAM);

		int start, loop, sub; // define instruction labels

		sub = 5; // Since we are going to jump forward in our program, we need to 
				// define this variable by hand.  Instructions start at 0 and count up

		//Instruction format
		//int pb_inst(int flags, int inst, int inst_data, int length)

		// Instruction 0 - Jump to Subroutine at Instruction 4 in 100ns
		start =	pb_inst(ON|0x1FFFFF,JSR,sub,100*ns);

		// Instruction 1 - Beginning of Loop (Loop 3 times).  Continue to next instruction in 100ns
		loop =	pb_inst(0x0,LOOP,3,100*ns);
		
		// Instruction 2 - End of Loop.  Return to beginning of loop or continue to next instruction in 1us
				pb_inst(0x0,END_LOOP,loop,100*ns); 

		// Instruction 3 - Stay here for (5*800ns) then continue to Instruction 4
				pb_inst(0x0,LONG_DELAY,5,800*ns);

		// Instruction 4 - Branch to "start" (Instruction 0) in 100ns
				pb_inst(0x0,BRANCH,start,100*ns);

		// Instruction 5 - Continue to next instruction in 200ns
				pb_inst(0x0,CONTINUE,0,200*ns);
		
		// Instruction 6 - Return from Subroutine to Instruction 1 in 200ns
				pb_inst(0x0,RTS,0,200*ns);

		// End of programming registers and pulse program
		stop_programming();

		// Start execution of the pulse program
		start_pb();

		pb_close();

}