/***********************************************************************//**
 * @file		irqHandlers.h
 * @brief		Contains all interrupt handlers declarations.
 *
 * @details		
 *		
 *
 * @author		Andrzej Zamojski ( NTNU )
 * @date		1 VI 2012
 **************************************************************************/

 #ifndef IRQ_HANDLERS_H_
 #define IRQ_HANDLERS_H_
 
 /* Includes =============================================== */
 #include <stdlib.h>
 #include <util/delay.h>
 
 #include "uCmaskFile.h"
 #include "functions.h"
 #include "MCP2515control.h"
 #include "hll.h"


 /* PRE-PROCESSOR DIRECTIVES =============================== */

 /* Only for debugging purposes - for msg sending */
 #define	TIME_PERIOD		16

 


 /* Interrupt routine declarations ========================= */

 #if ( CONFIG_TESTING_HAL )
 	ISR ( TIMER0_OVF_VECT );	// only for testing purposes
 #endif
 ISR ( CONFIG_MCP_INT );
 ISR ( CONFIG_INT_SENDING );
 ISR ( CONFIG_INT_RECEIVING );
 ISR ( WDT_VECT );
 ISR ( BADISR_vect );
 


 /* Function declarations ================================== */

 void clearMCP2515InterruptFlag ( uint8_t reg, uint8_t flag );
 // void receiveCanMsg ( struct can_msg* msgRec, uint8_t regRec );		// only for HAL testing
 void receiveCanMsg ( uint8_t regRec );
 void sendCanMsg ( struct can_msg* msgToSend, uint8_t regToSend );
 void hal_msg_poll ( void );
 
 #endif
