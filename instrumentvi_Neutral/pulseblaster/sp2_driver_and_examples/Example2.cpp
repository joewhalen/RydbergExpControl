// Filname: Example2.cpp
//
// SpinCore Technologies, Inc.
// February 2004
// http://www.spincore.com
//

// The following program code uses C Functions from 'pbdfuncs' to
// generate and execute a pulse sequence on the PB24 board.

// Be sure to include the DLL (pbd03pc.dll), the library file
// (pbd03pc.lib), the header files (pbd03pc.h and pbdfuncs.h), and source
// file (pbdfuncs.cpp) in the working directory of your C compiler .


#include <stdio.h>
#include "pbdfuncs.h"
#include "pbdfuncs.cpp"

void main(void)
{

		if (pb_init() != 0)
			printf("--- Error Initializing PulseBlaster ---\n");

		// Check for proper initialization of PB24

		// Set clock frequency
		set_clock(100);

		//Begin pulse program
		start_programming(PULSE_PROGRAM);

		int start, loop, sub; // define instruction labels

		sub = 5; // Since we are going to jump forward in our program, we need to 
				// define this variable by hand.  Instructions start at 0 and count up

		//Instruction format
		//int pb_inst(int flags, int inst, int inst_data, int length)

		// Instruction 0 - Jump to Subroutine at Instruction 4 in 1s
		start =	pb_inst(0xFFFFFF,JSR, sub, 1 * s);

		// Instruction 1 - Beginning of Loop (Loop 3 times).  Continue to next instruction in 1s
		loop =	pb_inst(0x0,LOOP,3,1 * s);
		
		// Instruction 2 - End of Loop.  Return to beginning of loop or continue to next instruction in .5 s
				pb_inst(0x0,END_LOOP,loop,50 * ms); 

		// Instruction 3 - Stay here for (5*100ms) then continue to Instruction 4
				pb_inst(0x0,LONG_DELAY,5, 100 * ms);

		// Instruction 4 - Branch to "start" (Instruction 0) in 1 s
				pb_inst(0x0,BRANCH,start,1*s);

		// Instruction 5 - Continue to next instruction in 1 * s
				pb_inst(0x0,CONTINUE,0,1*s);
		
		// Instruction 6 - Return from Subroutine to Instruction 1 in .5*s
				pb_inst(0xFFFFFF,RTS,0,.5*s);

		// End of programming registers and pulse program
		stop_programming();

		// Start execution of the pulse program
		start_pb();


		//read the status register
		int status = read_status();
		printf("status = %d", status);

		pb_close();

}