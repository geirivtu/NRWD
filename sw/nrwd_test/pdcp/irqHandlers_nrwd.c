/***********************************************************************//**
 * @file		irqHandlers.c
 * @brief		Contains all interrupt handlers definitions and functions declarations @n
 *				indispensible for proper operation of the handlers.
 *
 * @details		
 *		
 *
 * @author		Andrzej Zamojski ( NTNU )
 * @date		10 VI 2012
 **************************************************************************/
 
 /* Includes */
 #include <avr/interrupt.h>
 #include <stdlib.h>
 #include "uCmaskFile.h"
 #include "irqHandlers_nrwd.h"
 
 #include "can.h"	//at90can
 
 /* Variables for time measuring - in testing */
 extern volatile uint16_t time;
 extern volatile uint8_t flag;


 /* Flags for interrupt driving */
 static volatile uint8_t	msgError;
 static volatile uint8_t	wakeUp;
 static volatile uint8_t	transmitError;
 static volatile uint8_t 	txBuf2Ready;
 static volatile uint8_t 	txBuf1Ready;
 static volatile uint8_t 	txBuf0Ready;
 static volatile uint8_t 	rxBuf1Full;
 static volatile uint8_t 	rxBuf0Full;
  
 extern volatile uint8_t readBuffer;		//* only for HAL testing! (not relevant for whole interface)
 
 

 
 
 /* ISR ( CONFIG_INT_SENDING) ===================================== */
 /**
 * @name 		CONFIG_INT_SENDING Interrupt handler
 * @brief  		External Interrupt handler
 * @param[in]	void
 * @return 		void
 */
ISR ( CONFIG_INT_SENDING ) {
	
	///* Disable interrupts */
	//cli();
	//
	///* Data */
	//struct can_msg* ptrToMsg;
	//
	///* Fetch message to sent from High Protocol Layer */
	//ptrToMsg = hll_msg_get();
	//
	//sendCanMsg( ptrToMsg, SEND_REG_0);
//
	///* Free pointer to structure */
	//hll_msg_free ( ptrToMsg );
	//
	///* Enable interrupts */
	//sei();
 }

 
 

 /* ISR ( WDT_VECT) ===================================== */
 /**
 * @name 		WDT_VECT Watchdog
 * @brief  		Watchdog Timer handler
 * @param[in]	void
 * @return 		void
 */
 #if ( CONFIG_WDT_MODE == WDT_OFF )
 ISR ( WDT_VECT ) {
	
	_delay_ms( 150 );	

 }
 #endif
 
 

 
 
 


 
