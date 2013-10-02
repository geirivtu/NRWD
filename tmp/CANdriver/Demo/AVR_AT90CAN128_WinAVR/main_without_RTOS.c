/*! \file
	Purpose: \n
	Interrupt-driven reception of CAN packets \n
	Polled transmission of can packets \n
	This version can be linked with can.c without using FreeRTOS.

	CAN packets with ID 0x150 will switch the LEDs at port E. \n
	CAN packets with ID 0x151 will be echoed at ID 0x152.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "general.h"
#include "assert.h"
#include "can.h"

//! interrupt callback function for CAN receiver interrupt.
void receive150( CAN_packet *p, unsigned char mob) // interrupt callback
	{
	(void)mob;
	PORTE^=p->data[0];
	}

//! interrupt callback function for CAN receiver interrupt.
void receive151( CAN_packet *p, unsigned char mob) // interrupt callback
	{
	(void)mob;
	p->id=0x152;
	can_tx( 14, p);
	}

//! main program.

//! used to test and demonstrate the CAN rx+tx functionality \n
//! uncomment main() to use this version (without FreeRTOS)
int main (void)
//int main (void)
	{	
	DDRE=0xff;
	
	BOOL ret;	

	can_init();

	ret=prepare_rx( 0, 0x150, 0x7ff, receive150);
	ASSERT( ret==0);

	ret=prepare_rx( 1, 0x151, 0x7ff, receive151);
	ASSERT( ret==0);

	sei();	// CAN RX is interrupt driven, switch interrupts ON
	
	for(;;)
		asm("sleep");;
	return 0;
	}
