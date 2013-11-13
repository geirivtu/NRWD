/***********************************************************************//**
 * @file		functions.h
 * @brief		Contains functions prototype for HAL.
 *
 * @author		Andrzej Zamojski ( NTNU )			
 * @date		1 VI 2012

 **************************************************************************/

 #ifndef FUNCTIONS_H_
 #define FUNCTIONS_H_
 
 #include <stdlib.h>
 #include <avr/interrupt.h>

 #include "config.h"
 #include "hll.h"

 
 
 /* Needed pre-processor directives =============================== */

 #define	MASK_ARBITRATOR		0x00
 #define	MASK_DEVICE			0xFF
 #define	DUMMY_DATA			0x00
 
 /* Enum: CAN_INIT_STATUS */
 /** @enum		CAN_INIT_STATUS 
 *	 @brief		Status of CAN interface initialization */
 typedef enum {
	CAN_INIT_OK = 0,	
	CAN_INIT_FAILED
 } CAN_INIT_STATUS;
 

 
 /* Function declarations ================================== */
  
 /* CAN handling  */


 CAN_INIT_STATUS initCan ( uint8_t id );
 void hal_set_filter( uint8_t id );
 void hal_set_mask( uint8_t id );
 void hal_msg_poll ( void );
  void hal_msg_take ( void );
 

 /* Others */ 
 void triggerSoftwareInterrupt ( uint8_t port);
 void initLowLevelProtocolHardware ( void );
 
 void sendCanMsg ( struct can_msg* msgToSend);


 void forceReset ( void );
 
 #endif
