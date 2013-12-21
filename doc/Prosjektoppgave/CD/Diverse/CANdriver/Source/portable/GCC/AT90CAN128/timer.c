/*
	FreeRTOS V3.0.0 - Copyright (C) 2003 - 2005 Richard Barry.

	This file is part of the FreeRTOS distribution.

	FreeRTOS is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	FreeRTOS is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with FreeRTOS; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

	A special exception to the GPL can be applied should you wish to distribute
	a combined work that includes FreeRTOS, without being obliged to provide
	the source code for any proprietary components.  See the licensing section 
	of http://www.FreeRTOS.org for full details of how and when the exception
	can be applied.

	***************************************************************************
	See http://www.FreeRTOS.org for documentation, latest information, license 
	and contact details.  Please ensure to read the configuration and relevant 
	port sections of the online documentation.
	***************************************************************************
*/

/* 

Changes from V2.6.0

	+ AVR port - Replaced the inb() and outb() functions with direct memory
	  access.  This allows the port to be built with the 20050414 build of
	  WinAVR.
	
	
	  AVR Port - extracted new file timer.c to deal with the slight differences
	  vetween ATMegaxyz processors. (K.Schaefer)

*/
#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"

/* Hardware constants for timer 1. */
#define portCLEAR_COUNTER_ON_MATCH				( ( unsigned portCHAR ) 0x08 )
#define portPRESCALER							( ( unsigned portCHAR ) 0x03 )
#define portCLOCK_PRESCALER						( ( unsigned portLONG ) 64 )
#define portCOMPARE_MATCH_A_INTERRUPT_ENABLE	( ( unsigned portCHAR ) 0x02 )

/*-----------------------------------------------------------*/

/*
 * Setup timer 1 compare match A to generate a tick interrupt.
 */
void prvSetupTimerInterrupt( void );
void prvSetupTimerInterrupt( void )
{
unsigned portLONG ulCompareMatch;
unsigned portCHAR ucHighByte, ucLowByte;

	/* Using 16bit timer 1 to generate the tick.  Correct fuses must be
	selected for the configCPU_CLOCK_HZ clock. */

	ulCompareMatch = configCPU_CLOCK_HZ / configTICK_RATE_HZ;

	/* We only have 16 bits so have to scale to get our required tick rate. */
	ulCompareMatch /= portCLOCK_PRESCALER;
	ulCompareMatch -= 1; // count correction


	/* Setup compare match value for compare match A.  Interrupts are disabled 
	before this is called so we need not worry here. */
	ucLowByte = ( unsigned portCHAR ) ( ulCompareMatch & ( unsigned portLONG ) 0xff );
	ulCompareMatch >>= 8;
	ucHighByte = ( unsigned portCHAR ) ( ulCompareMatch & ( unsigned portLONG ) 0xff );
	OCR1AH = ucHighByte;
	OCR1AL = ucLowByte;

	/* Setup clock source and compare match behaviour. */
	ucLowByte = portCLEAR_COUNTER_ON_MATCH | portPRESCALER; // prescaler neu 64 portPRESCALE_256;
	TCCR1B = ucLowByte;

	/* Enable the interrupt - this is okay as interrupt are currently globally
	disabled. */
	ucLowByte = TIMSK1;
	ucLowByte |= portCOMPARE_MATCH_A_INTERRUPT_ENABLE;
	TIMSK1 = ucLowByte;
}
