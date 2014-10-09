//
// SpinCore Technologies, Inc.
// http://www.spincore.com
//
// Last modified: 11/20/02

// Define the PB/PBDDS model type
// Valid type are:
// PB01IS - PulseBlaster on ISA
// PB02PC - PulseBlaster on PCI revision 1
// PB03PC - PulseBlaster on PCI revision 2
// PBD01IS - PulseBlasterDDS on ISA
// PBD02PC - PulseBlasterDDS on PCI revision 1
// PBD03PC - PulseBlasterDDS on PCI revision 2

#define PB03PC

//Defines for start_programming
#define PULSE_PROGRAM 0
#define FREQ_REGS 1
#define PHASE_REGS 2
#define TX_PHASE_REGS 2
#define RX_PHASE_REGS 3


//Defines for enabling analog output
#define ANALOG_ON 1
#define ANALOG_OFF 0
#define TX_ANALOG_ON 1
#define TX_ANALOG_OFF 0
#define RX_ANALOG_ON 1
#define RX_ANALOG_OFF 0

//Defines for different pb_inst instruction types
#define CONTINUE 0
#define STOP 1
#define LOOP 2
#define END_LOOP 3
#define JSR 4
#define RTS 5
#define BRANCH 6
#define LONG_DELAY 7
#define WAIT 8

//Defines for using different units of time
#define ns 1.0
#define us 1000.0
#define ms 1000000.0
#define s 1000000000.0

//Defines for using different units of frequency
#define MHz 1.0
#define kHz .001
#define Hz .000001

#define PARAM_ERROR -99

//Variables for max number of registers (Currently the same across models)
#define MAX_PHASE_REGS 16
#define MAX_FREQ_REGS 16

//Variable defines for different models of the PB/PBDDS

// Model Definition:
// #ifdef PBXYYZZ - X (DDS/NonDDS), YY - Board Revision, ZZ - Interface Style
// #define pb_init - Function called to grab PBDDS resources (if exists, otherwise 0)
// #define pb_close - Function called to release PBDDS resources (if exists, otherwise 0)
// #define outp - Function used to output 8 bits of data to board
// #define MAX_FLAG_BITS - Bit mask so that only valid flag bits are set by pb_inst
// #define ISA_BOARD - used to disable error checking, since _outp will return value written instead of error codes
// #define RF_STATE - used to disable RF outputs on PBDDS boards while not setting a bit for non-DDS boards for overloading pb_inst

#ifdef PB01IS
#include <conio.h>
#define pb_init			0
#define pb_close		0
#define sp_outp			_outp
#define MAX_FLAG_BITS	0xFFFFFF
#define ISA_BOARD		true
#define PB_ONLY			true
#define RF_STATE		0
#endif

#ifdef PBD01IS
#include <conio.h>
#define pb_init			0
#define pb_close		0
#define sp_outp			_outp
#define MAX_FLAG_BITS	0x3FF
#define ISA_BOARD		true
#define PB_ONLY			false
#define RF_STATE		1
#endif

#ifdef PBD02PC
#include "PBD02PC.h"
#define pb_init			PBD02PC_Init
#define pb_close		PBD02PC_Close
#define sp_outp			PBD02PC_outp
#define MAX_FLAG_BITS	0x3FF
#define ISA_BOARD		false
#define PB_ONLY			false
#define RF_STATE		1
#endif

#ifdef PB02PC
#include "PBD02PC.h"
#define pb_init			PBD02PC_Init
#define pb_close		PBD02PC_Close
#define sp_outp			PBD02PC_outp
#define MAX_FLAG_BITS	0xFFFFFF
#define ISA_BOARD		false
#define PB_ONLY			true
#define RF_STATE		0
#endif

#ifdef PBD03PC
#include "PBD03PC.h"
#define pb_init			PBD03PC_Init
#define pb_close		PBD03PC_Close
#define sp_outp			PBD03PC_outp
#define MAX_FLAG_BITS	0x3FF
#define ISA_BOARD		false
#define PB_ONLY			false
#define RF_STATE		1
#endif

#ifdef PB03PC
#include "PBD03PC.h"
#define pb_init			InitPMster//PBD03PC_Init
#define pb_close		ClosePMster//PBD03PC_Close
#define sp_outp			pb_outp//PBD03PC_outp
#define sp_inp			pb_inp
#define MAX_FLAG_BITS	0xFFFFFF
#define ISA_BOARD		false
#define PB_ONLY			true
#define RF_STATE		0
#endif

//Set ISA card base address.  Used for ISA cards only.  Default value is 0x340
void set_ISA_address(int address);

//Change clock value used to calculate frequency/delay words
//	clock_freq should be specified in MHz
void set_clock(double clock_freq);

//Initialize PulseBlasterDDS to accept data
	// Valid devices
	// 0 = PULSE_PROGRAM
	// 1 = FREQ_REGS
	// 2 = PHASE_REGS or TX_PHASE REGS
	// 3 = RX_PHASE_REGS
int start_programming(int device);

//Write a frequency word to the FREQ_REGS
// *** Assumes start_programming(FREQ_REGS) has been called
int set_freq(double freq);

//Write a phase word to the PHASE_REGS, TX_PHASE_REGS, or RX_PHASE_REGS
// *** Assumes start_programming(PHASE_REGS) has been called
int set_phase(double phase);

// Prepares PulseBlasterDDS to run pulse program.  This command should be sent
// after entire pulse program has been sent.
int stop_programming();

// Starts execution of pulse program
// *** Assumes pulse program has already been written to board
int start_pb();

// Stops execution of pulse program
int stop_pb();

// Sends one pulse program instruction word (10 bytes) to board
int pb_inst(int freq, int tx_phase, int tx_output_enable, int rx_phase, int rx_output_enable, int flags, int inst, int inst_data, double length);
/*

  valid values are:

	freq - 0 to 15
	tx_phase - 0 to 15
	tx_output_enable - 1 or 0 (TX_ANALOG_ON or TX_ANALOG_OFF)
	rx_phase - 0 to 15
	rx_output_enable - 1 or 0 (RX_ANALOG_ON or RX_ANALOG_OFF
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
	length - depends on clock speed used.  10 clock cycles to 32k clock cycles


	function returns instruction number which can be used for loops/branches, etc.
	If return value is negative an error has ocurred.  -99 Means an invalid parameter was
	passed to the function.  Other errors indicate problems with data transfer.
*/
// Overloaded function for boards with 1 RF channel only (PCI Boards)
int pb_inst(int freq, int phase, int rf_output_enable, int flags, int inst, int inst_data, double length);

// Overloaded function for PB only boards
int pb_inst(int flags, int inst, int inst_data, double length);

//read the status register
int read_status();
