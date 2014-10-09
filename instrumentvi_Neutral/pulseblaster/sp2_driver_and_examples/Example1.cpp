// Filname: Example1.cpp
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

	set_clock(100);  // Set Because the Board Operates at 100MHz

	//locate and initialize the board
	pb_init();

	int start;

	start_programming(PULSE_PROGRAM);	// Prepare the Board to Receive
	
	// Instruction 0 - Continue to instruction 1 in .1s
	// Flags = 0xFFFFFF, OPCODE = CONTINUE
	start = pb_inst(0xFFFFFF, CONTINUE, 0, .1*s);

	// Instruction 1 - Continue to instruction 2 in .1s
	// Flags = 0x0, OPCODE = CONTINUE
	pb_inst(0x0, CONTINUE, 0, .1*s);

	// Instruction 2 - Branch to "start" (Instruction 0) in .1s
	// 0x0, OPCODE = BRANCH, Target = start
	pb_inst(0x0, BRANCH, start, .1*s);


	stop_programming();

	start_pb();

	//read the status register
	int status = read_status();
	printf("status: %d", status);

	
	pb_close();
}

