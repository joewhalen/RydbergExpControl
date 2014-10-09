//Example for PulseBlasterESR-Pro
//
//8/4/2004
//SpinCore Technologies, Inc
//

/*
This example is intended for the PulseBlasterESR-Pro board.

It shows how to construct a short pulse program that will
generate a pulse of length 1, 2, 3, 4, 4.5, 5, 5.5, 6.5, ... clock periods
*/

#include "PB04PC.h"
#include "Pbdfuncs.h"
#include <stdio.h>

int main()
{
	//request and initialize control of PB
	PB04PC_Init();

	//tell the PB to start recieving pulse program instructions	
	
	//issue device reset
	PB04PC_outp(0,0);
	//select number of bytes per word
	PB04PC_outp(2,10);
	//select device to program (RAM)
	PB04PC_outp(3,0);
	//reset address counter
	PB04PC_outp(4,0);

	/////////////////////
	//Bit pattern details

	//bits 0 through 23 control the output of the four BNC connectors and 
	//the 21 IDC Flag outputs
	
	//bits 0 through 3 control the output of the four BNC connectors and 
	//IDC flags 0 through 3

	//bits 4 through 20 control the output of the IDC flags 4 through 20
	
	//bits 21 through 23 select the length of the pulse for the BNC connectors

	
	//for delay = 2
	//1 on bits 23-21 results in a pulse high for 1 clock period
	//2 on bits 23-21 results in a pulse high for 2 clock periods
	//3 on bits 23-21 results in a pulse high for 3 clock periods
	//4 on bits 23-21 results in a pulse high for 4 clock periods
	//5 on bits 23-21 results in a pulse high for 4.5 clock periods
	
	//for delay = 3
	//5 on bits 23-21 results in a pulse high for 5 clock periods
	
	//for delay >= 3
	//6 on bits 23 through 21 results in a pulse high for:
	//(delay+2.5)*(clock period)
	
	//instruction length = (delay + 4) * clock period

	////////////////////////////////
	//Instruction 1

	PB04PC_outp(6,0x20);		//1 on bits 21-23 for pulse of length one clock cycle on BNCs
	PB04PC_outp(6,0x00);		
	PB04PC_outp(6,0x0F);		//select BNC connectors 0-3
	
	//opcode
	PB04PC_outp(6,0x00);		
	PB04PC_outp(6,0x00);		
	PB04PC_outp(6,0x00);		//opcode = CONTINUE
	
	//delay
	PB04PC_outp(6,0x00);		
	PB04PC_outp(6,0x00);		
	PB04PC_outp(6,0x00);		
	PB04PC_outp(6,0x02);		//delay = 2, inst length = (2+4)*(clock period)

	////////////////////////////////
	//Instruction 2

	//pattern
	PB04PC_outp(6,0x00);		
	PB04PC_outp(6,0x00);		
	PB04PC_outp(6,0x00);		
	
	//opcode
	PB04PC_outp(6,0x00);		//data = 0
	PB04PC_outp(6,0x00);		
	PB04PC_outp(6,0x06);		//opcode = BRANCH 
	
	//delay
	PB04PC_outp(6,0x00);		
	PB04PC_outp(6,0x00);		
	PB04PC_outp(6,0x00);		
	PB04PC_outp(6,0x02);		//delay = 2, inst length = (2+4)*(clock period)


	//end of programming
	PB04PC_outp(7,0);

	//put device in run mode
	PB04PC_outp(1,0);
	
	//relase control of PB
	PB04PC_Close();

	return 0;
}

