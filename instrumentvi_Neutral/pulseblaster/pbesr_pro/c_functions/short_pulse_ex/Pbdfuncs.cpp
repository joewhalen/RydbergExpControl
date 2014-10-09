//
// SpinCore Technologies, Inc.
// http://www.spincore.com
//
// Last modified: 11/13/02

#include <stdio.h>
#include <math.h>
#include "pbdfuncs.h"



//Global variables
#ifdef PB04PC
int port_base = 0;
#else
int port_base = 0x340; // Supplied for backwards compatibility
#endif

double clock = .127; // Default clock value of 50 MHz
int num_instructions; // Contains current number of instructions in pulse program


//Set ISA card base address.  Used for ISA cards only.  Default value is 0x340
void set_ISA_address(int address)
{
	port_base = address;
}

//Change clock value used to calculate frequency/delay words
//	clock_freq should be specified in MHz
void set_clock(double clock_freq)
{
	clock = clock_freq / 1000; // Put in GHz (for ns timescale)
}

//Initialize PulseBlasterDDS to accept data
	// Valid devices
	// 0 = PULSE_PROGRAM
	// 1 = FREQ_REGS
	// 2 = TX_PHASE_REGS
	// 3 = RX_PHASE_REGS
int start_programming(int device)
{

	int return_value;

	return_value = sp_outp(port_base + 0,0); // Reset PulseBlasterDDS
	if(return_value != 0 && (!(ISA_BOARD)))
	{
		return return_value;
	}

	if (device == PULSE_PROGRAM)
	{
		num_instructions = 0; // Clear number of instructions

		return_value = sp_outp(port_base + 2,10); // This is an instruction, therefore Bytes Per Word (BPW) = 10
		if(return_value != 0 && (!(ISA_BOARD)))
		{
			return return_value;
		}
		
		return_value = sp_outp(port_base + 3, device); // Device = RAM
		if(return_value != 0 && (!(ISA_BOARD)))
		{
			return return_value;
		}

		return_value = sp_outp(port_base + 4, 0); // Reset mem counter
		if(return_value != 0 && (!(ISA_BOARD)))
		{
			return return_value;
		}
		
	}
	else if (device == FREQ_REGS || device == TX_PHASE_REGS || device == RX_PHASE_REGS)
	{
		return_value = sp_outp(port_base + 2, 4); // This is a DDS reg, therefore BPW = 4
		if(return_value != 0 && (!(ISA_BOARD)))
		{
			return return_value;
		}

		return_value = sp_outp(port_base + 3, device); // Device = FREQ_REGS, TX_PHASE_REGS, or RX_PHASE_REGS
		if(return_value != 0 && (!(ISA_BOARD)))
		{
			return return_value;
		}

		return_value = sp_outp(port_base + 4, 0); // Reset mem counter
		if(return_value != 0 && (!(ISA_BOARD)))
		{
			return return_value;
		}
	}

	return 0;
}

//Write a frequency word to the FREQ_REGS
//	*** Assumes start_programming(FREQ_REGS) has been called
int set_freq(double freq)
{
	unsigned int freq_byte = 0xFF000000;//Bit Mask to send 1 byte at a time
	unsigned int freq_word = (unsigned int) (freq * (double)pow(2,32) / (clock*1000)); // Desired data to trasnfer
	unsigned int temp_byte;
	int return_value;
	
	for(int i = 0; i<4; i++) // Loop to send 4 bytes
	{

		temp_byte = freq_byte & freq_word;  // Get current byte to transfer
		temp_byte >>= 24; // Shift data into LSB
		return_value = sp_outp(port_base + 6, temp_byte); // Send byte to PulseBlasterDDS
		if(return_value != 0 && (!(ISA_BOARD)))
		{
			return return_value;
		}

		freq_word <<= 8; // Shift word up one byte so that next byte to transfer is in MSB

	}
	return 0;
}

int set_phase(double phase)
{
	
	unsigned int phase_byte = 0xFF000000;//Bit Mask to send 1 byte at a time
	unsigned int phase_word = (int) (phase * (double)pow(2,32) / 360); // Desired data to transfer
	unsigned int temp_byte;
	int return_value;

	for(int i = 0; i<4; i++) // Loop to send 4 bytes
	{
		temp_byte = phase_byte & phase_word; // Get current byte to transfer
		temp_byte >>= 24; // Shift data into LSB
		return_value = sp_outp(port_base + 6, temp_byte); // Send byte to PulseBlasterDDS
		if(return_value != 0 && (!(ISA_BOARD))) // conio's _outp returns value passed to it
		{
			return return_value;
		}

		phase_word <<= 8; // Shift word up one byte so that next byte to transfer is in MSB
	}
	return 0;
}

// Prepares PulseBlasterDDS to run pulse program.  This command should be sent
// after entire pulse program has been sent.
int stop_programming()
{
	int return_value;
	
	return_value = sp_outp(port_base + 7, 0);
	if(return_value != 0 && (!(ISA_BOARD)))
	{
		return return_value;
	}

	return 0;
	
}

// Starts execution of pulse program
// *** Assumes pulse program has already been written to board
int start_pb()
{
	int return_value;

	return_value = sp_outp(port_base + 0, 0);
	if(return_value != 0 && (!(ISA_BOARD)))
	{
		return return_value;
	}

	return_value = sp_outp(port_base + 2, 0xFF);
	if(return_value != 0 && (!(ISA_BOARD)))
	{
		return return_value;
	}
	
	return_value = sp_outp(port_base + 3, 0xFF);
	if(return_value != 0 && (!(ISA_BOARD)))
	{
		return return_value;
	}
	
	return_value = sp_outp(port_base + 4, 0xFF);
	if(return_value != 0 && (!(ISA_BOARD)))
	{
		return return_value;
	}
	
	return_value = sp_outp(port_base + 7, 0);
	if(return_value != 0 && (!(ISA_BOARD)))
	{
		return return_value;
	}
	
	return_value = sp_outp(port_base + 1, 0);
	if(return_value != 0 && (!(ISA_BOARD)))
	{
		return return_value;
	}

	return 0;
}

// Stops execution of pulse program
int stop_pb()
{
	int return_value;

	return_value = sp_outp(port_base + 0,0);
	if(return_value != 0 && (!(ISA_BOARD)))
	{
		return return_value;
	}

	return 0;

}

// Sends one pulse program instruction word (10 bytes) to board

int pb_inst(int freq, int tx_phase, int tx_output_enable, int rx_phase, int rx_output_enable, int flags, int inst, int inst_data, double length)
{
/*

  valid values are:

	freq - 0 to 15
	tx_phase - 0 to 15
	tx_output_enable - 1 or 0 (TX_ANALOG_ON or TX_ANALOG_OFF)
	rx_phase - 0 to 15
	rx_output_enable - 1 or 0 (RX_ANALOG_ON or RX_ANALOG_OFF)
	flags - current state of flags (0x3FF is highest value)
	inst ->


	OpCode #	inst Meaning			inst_data field used for
	0			CONTINUE				Ignored
	1			STOP					Ignored
	2			LOOP					Number of desired Loops - 1
	3			END_LOOP				Address of Instruction originating loop
	4			JSR	(Jump Subroutine)	Address of first subroutine instruction
	5			RTS	(Return Subroutine)	Ignored
	6			BRANCH					Address of next instruction
	7			LONG_DELAY				Number of desired loops - 2
	8			WAIT					Ignored

	inst_data - Valid range is 0 to 1048575 (20 bit number)
	lenght - depends on clock speed used.  10 clock cycles to 32k clock cycles


	function returns instruction number (or -1 for an error);
		instruction number can be used for loops/branches, etc.
*/

	int return_value;

	//Check for valid passed parameters
	if(freq <0 || freq > MAX_FREQ_REGS)
	{
		return -99;
	}
	if(tx_phase < 0 || tx_phase > MAX_FREQ_REGS)
	{
		return -98;
	}
	if(tx_output_enable != ANALOG_ON && tx_output_enable != ANALOG_OFF)
	{
		return -97;
	}
	if(rx_phase < 0 || rx_phase > MAX_PHASE_REGS)
	{
		return -96;
	}
	if(rx_output_enable != ANALOG_ON && rx_output_enable != ANALOG_OFF)
	{
		return -95;
	}
	if(flags < 0 || flags > MAX_FLAG_BITS)
	{
		return -94;
	}
	if (inst < 0 || inst > 8)
	{
		return -93;
	}
	if(inst == LOOP)
	{
		inst_data -= 1;
	}
	if(inst == LONG_DELAY)
	{
		inst_data -= 2;
	}
	if (inst_data < 0 || inst_data > 1048575)
	{
		return -92;
	}
	
	unsigned int OCW = 0;
	if (PB_ONLY)
	{
		OCW = flags;
	}
	else
	{
		OCW = OCW | (freq << 20) | (tx_phase << 16) | (!(tx_output_enable) << 11) | (rx_phase << 12) | (!(rx_output_enable) << 10) | (flags & MAX_FLAG_BITS);
	}

	unsigned int OPCODE = 0;

	OPCODE = inst | inst_data << 4;

	unsigned int DELAY = 0;
	double temp_delay = ((length * clock) - 4); //(Assumes clock in GHz and length in ns)

	printf("%f\n", temp_delay);
	
	if (temp_delay < 2 || temp_delay > ((double)pow(2,32) - 1)) // Outside Valid Range
	{
		//intf("%f\n", temp_delay);
		return -91;
	}

	DELAY = (unsigned int) temp_delay;
	printf("%d\n", DELAY);

	unsigned int temp_byte;

	unsigned int BIT_MASK = 0xFF0000;
	for(int i =0; i<3; i++)
	{
		temp_byte = BIT_MASK & OCW;
		temp_byte >>= 16;
		return_value = sp_outp(port_base + 6, temp_byte);
		if(return_value != 0 && (!(ISA_BOARD)))
		{
			return return_value;
		}
		OCW <<= 8;
	}
	BIT_MASK = 0xFF0000;
	for(i = 0; i<3; i++)
	{
	
		temp_byte = BIT_MASK & OPCODE;
		temp_byte >>= 16;
		return_value = sp_outp(port_base + 6, temp_byte);
		if(return_value != 0 && (!(ISA_BOARD)))
		{
			return return_value;
		}
		OPCODE <<= 8;
	}
	BIT_MASK = 0xFF000000;
	for(i = 0; i<4; i++)
	{
		temp_byte = BIT_MASK & DELAY;
		temp_byte >>= 24;
		return_value = sp_outp(port_base + 6, temp_byte);
		if(return_value != 0 && (!(ISA_BOARD)))
		{
			return return_value;
		}
		DELAY <<= 8;
	}

	num_instructions +=1;
	return num_instructions - 1;

}

// Overloaded function for 1 RF channel boards (PCI Boards)
int pb_inst(int freq, int phase, int rf_output_enable, int flags, int inst, int inst_data, double length)
{
	return pb_inst(freq, phase, rf_output_enable, 0, 1, flags, inst, inst_data, length);
}

// Overloaded function for PB only boards
int pb_inst(int flags, int inst, int inst_data, double length)
{
	return pb_inst(0,0,RF_STATE,0,RF_STATE,flags,inst,inst_data,length);
}



int read_status()
{

	return sp_inp(0);

}

