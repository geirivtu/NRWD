/*!	\mainpage CAN bus Driver for AT90CAN128 under FreeRTOS with AVRGCC
	
	This driver uses a three layer architecture:
	
	<tt>
	---------------------- \n
	| Application        | \n
	---------------------- \n
	---------------------- \n
	| FreeRtos CAN driver| \n
	---------------------- \n
	---------------------- \n
	| generic CAN driver | \n
	---------------------- \n
	</tt>

	\author Dr. Klaus Schaefer \n
	Hochschule Darmstadt * University of Applied Sciences \n
	schaefer@eit.h-da.de \n
	http://eit.h-da.de

	You can redistribute it and/or modify it 
	under the terms of the GNU General Public License.\n
	It is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; \n
	without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n
	See http://www.gnu.org/copyleft/gpl.html for mor details.

	This software was developed using material from ATMEL \n
	see http://www.atmel.com \n
	and especially http://www.atmel.com/dyn/resources/prod_documents/at90can128-lib-mcu-0_0_3.zip

	\b Download the latest version of this software here: http://kschaefer.eit.h-da.de/ATMEL/CAN/CANdriver.zip \n
	To use this package you also need to download FreeRTOS: http://www.freertos.org/ \n
	and the GNU Compiler for AVR Controllers http://winavr.sourceforge.net

	\see main.c
	\see main_without_FreeRTOS()

	\file
	test routines for FreeRTOS CAN driver \n
	send and receive CAN packets\n
	\b Test \b environment: \n
	AT90CAN128 on STK502 using 8MHz crystal\n
	PORT E connected to the LEDs of the STK500 carrier board.\n
	PORT D connected to a CAN bus running at 100kBit/s with a proper bus driver.
	
*/
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "frtos_can.h"

//! blink LED at port E 
static void blink_function( void *x)
	{
	unsigned char i=0;
	portTickType xLastWakeTime = xTaskGetTickCount();
	for(;;)
		{
		PORTE ^= 0x01;
		++i; i%=4;
        vTaskDelayUntil( &xLastWakeTime, (unsigned[]){100, 100, 100, 700}[i]);
		}
 	}

//! periodically send CAN packet ID 0x152
static void send_function( void *x)
	{
	(void)x;
	portTickType xLastWakeTime = xTaskGetTickCount();
	char data[8];
	unsigned long *l=(unsigned long *)data;
	static const CAN_packet packet={0x152, 8, "12345678"};
	
     for( ;; )
		{
        vTaskDelayUntil( &xLastWakeTime, 10 );
		can_send( &packet, 14, 1000);
		++*l;
		}
	}

//! continuously send CAN packets ID 0x153 with max speed (approx 1000Hz)
static void send_function2( void *x)
	{
	(void)x;
	static CAN_packet packet={0x153, 8, "\0\0\0\0\0\0\0\0"};
	unsigned long *l=(unsigned long *)&(packet.data);
	
     for( ;; )
		{
		can_send( &packet, 13, 1000);
		++*l; // modify packet data
		}
	}

//! echo CAN packets ID 0x150 on ID 0x151
static void receive_function( void *x)
	{
	(void)x;
	static CAN_packet packet;
	xQueueHandle queue=xCANQueueCreate( 0x150, 0x3ff, 2);
	for(;;)
		{
		xQueueReceive( queue, &packet, portMAX_DELAY);
		PORTE ^= (packet.data[0] & 0xfe);
		packet.id=0x151;
		can_send( &packet, 12, 1000);
		}
 	}

//! system initialisation
int main( void )
{
	DDRE = 0xff;
	can_init();
	xTaskCreate( receive_function, 	0, configMINIMAL_STACK_SIZE, 0, tskIDLE_PRIORITY + 3 , NULL );
	xTaskCreate( send_function, 	0, configMINIMAL_STACK_SIZE, 0, tskIDLE_PRIORITY + 2 , NULL );
	xTaskCreate( blink_function, 	0, configMINIMAL_STACK_SIZE, 0, tskIDLE_PRIORITY + 1 , NULL );
	xTaskCreate( send_function2, 	0, configMINIMAL_STACK_SIZE, 0, tskIDLE_PRIORITY + 0 , NULL );

	vTaskStartScheduler();

	return 0;
}

