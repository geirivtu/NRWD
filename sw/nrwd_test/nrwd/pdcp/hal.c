/***********************************************************************//**
 * @file		hal.c
 * @brief		Contains functions definitions which are relevant for interface between 
 *				lower and upper layers of PDCP ( mainly HAL )
 *
 * @details		
 *
 *
 * @author		Geir Turtum ( NTNU )			
 **************************************************************************/

 #include <avr/io.h>
 #include <avr/wdt.h>
 #include <stdint.h>
 
 
 #include "hal.h"
 #include "can.h"
 

 
 /* initLowLevelProtocolHardware ================================= */
 /**
 * @fn 			void initLowLevelProtocolHardware ( void )
 * @brief  		Function to initialize all important ports and methods for LLP hardware
 * @param[in]	void
 * @return 		void
 */
 void initLowLevelProtocolHardware ( void ) {			

	/* CAN configuration */	
	if ( CONFIG_BUS_MODE )			
		initCan( CONFIG_ARB_DEF_ID );
	else if ( !CONFIG_BUS_MODE )
		initCan( CONFIG_DEVICE_DEF_ID );			
	
  }


void canReceiveCallback( CAN_packet *p, unsigned char mob){ 
	uint8_t i;
	/* Msg alloc */
	struct can_msg* ptr = hll_msg_alloc(); 
	
	ptr->id = p->id;
	ptr->len = p->length;
	
	for(i=0; i<ptr->len; i++){
		ptr->data[i] = p->data[i];
	}	
 
	/* Msg commit */
	hll_msg_commit(ptr); 
}
 
  /* sendCanMsg ===================================== */
 /**
 * @fn 			void sendCanMsg ( struct can_msg* msgToSend, uint8_t regToSend )
 * @brief  		Internal function which task is to send message through CAN 
 * @param[in]	msgToSend*	Pointer to structure filled with message content
 * @return 		void
 */ 
  void sendCanMsg ( struct can_msg* msgToSend){
	
	
	
 	CAN_packet *canMsgPtr;
	CAN_packet canMsg;
	
	canMsgPtr = &canMsg;
	
	char mob;
	uint8_t i;
	 
	canMsgPtr->id = msgToSend->id;
	canMsgPtr->length = msgToSend->len;
	
	for(i=0; i<msgToSend->len; i++){
		canMsgPtr->data[i] = msgToSend->data[i];	
	}
	
	mob = 14; //What mob to use?
	can_tx(mob, canMsgPtr);
	
 }
 
   /* hal_msg_take =================================================== */
 /**
 * @fn 			void hal_msg_take()
 * @brief  		Function to trigger message sending
 * @return 		void
 */
void hal_msg_take(){

	/* Disable interrupts */
	cli();
	
	/* Data */
	struct can_msg* ptrToMsg;
	
	/* Fetch message to sent from High Protocol Layer */
	ptrToMsg = hll_msg_get();
	
	sendCanMsg( ptrToMsg);

	/* Free pointer to structure */
	hll_msg_free ( ptrToMsg );
	
	/* Enable interrupts */
	sei();	
}

 
 /* initCan ====================================================  */
 /**
 * @fn 			CAN_INIT_STATUS initCan( uint8_t id )
 * @brief  		Can initialization.
 * @details		Can be called <b>after PIN initialization</b>
 * @param[in]	id			Id CONFIG_BUS_MODE
 * @param[in]	moduleMode	CONFIG_BUS_MODE type
 * @return 		CAN_INIT_STATUS 	Status of CAN initialization 	
 */
CAN_INIT_STATUS initCan( uint8_t id ){
	 
	 
	 cli();
	 
	 can_init();
	 
	 char mob = 10;	//what mob to use?
	 
	 /* Sets mask and id for this mob */
	 prepare_rx(mob, id, id, canReceiveCallback);
	 
	 return CAN_INIT_OK;
 }

 
 /* hal_set_filter ===============================================  */
 /**
 * @fn 		 	void hal_set_filter ( uint8_t id )
 * @brief  		Function to set filters of node indicated by ID
 * @details		Can be called <b>after PIN initialization</b>
 * @param[in]	id			 CONFIG_BUS_MODE
 * @return 		void
 */
 void hal_set_filter ( uint8_t id ){
 	
	/* Put MCP into configuration mode */



	if ( CONFIG_BUS_MODE == BUS_DEVICE ){

		///* set filter 0 for DEVICE CONFIG_BUS_MODE */
		//mcp2515TransmitData(MCP_WRITE_CMD, RXF0SIDH, ( id >> 3 ) , 0 );
		//mcp2515TransmitData(MCP_WRITE_CMD, RXF0SIDL, ( ( id & 0x7 ) << 5 ) , 0 );
//
		///* set filter 1 for DEVICE CONFIG_BUS_MODE */
		//mcp2515TransmitData(MCP_WRITE_CMD, RXF1SIDH, ( id >> 3 ) , 0 );
		//mcp2515TransmitData(MCP_WRITE_CMD, RXF1SIDL, ( ( id & 0x7 ) << 5 ) , 0 );
//
		///* set filter 2 for DEVICE CONFIG_BUS_MODE - for broadcast messages */
		//mcp2515TransmitData(MCP_WRITE_CMD, RXF2SIDH, ( 0x00 >> 3 ) , 0 );
		//mcp2515TransmitData(MCP_WRITE_CMD, RXF2SIDL, ( ( 0x00 & 0x7 ) << 5 ) , 0 );
	}
	else if ( CONFIG_BUS_MODE == BUS_ARBITRATOR ){
	
		/* set filter 0 for ARBITRATOR CONFIG_BUS_MODE - receive all messages */	

	}
}



 /* hal_set_mask =================================================== */
 /**
 * @fn 			void hal_set_mask( uint8_t id )
 * @brief  		Function to set mask of node indicated by ID
 * @details		Can be called <b>after PIN initialization</b>
 * @param[in]	id			 CONFIG_BUS_MODE
 * @return 		void
 */
 void hal_set_mask( uint8_t id ){
 	
	/* Put MCP into configuration mode */

	//mcp2515TransmitData(MCP_WRITE_CMD, CANCTRL, ( CANCTRL_REQOP_CONFIGURATION << CANCTRL_REQOP_SHIFT ), 0 );
//
	//if ( CONFIG_BUS_MODE == BUS_DEVICE ){
//
		///* Set mask 0 for DEVICE CONFIG_BUS_MODE */
		//mcp2515TransmitData(MCP_WRITE_CMD, RXM0SIDH, ( MASK_DEVICE >> 3 ) , 0 );
		//mcp2515TransmitData(MCP_WRITE_CMD, RXM0SIDL, ( ( MASK_DEVICE & 0x7 ) << 5 ) , 0 );
//
		///* Set mask 1 for DEVICE CONFIG_BUS_MODE */
		//mcp2515TransmitData(MCP_WRITE_CMD, RXM1SIDH, ( MASK_DEVICE >> 3 ) , 0 );
		//mcp2515TransmitData(MCP_WRITE_CMD, RXM1SIDL, ( ( MASK_DEVICE & 0x7 ) << 5 ) , 0 );
//
	//}	
	//else if ( CONFIG_BUS_MODE == BUS_ARBITRATOR ){
//
		///* Set mask 0 for ARBITRATOR CONFIG_BUS_MODE */
		//mcp2515TransmitData(MCP_WRITE_CMD, RXM0SIDH, ( MASK_ARBITRATOR >> 3 ), 0 );
		//mcp2515TransmitData(MCP_WRITE_CMD, RXM0SIDL, ( ( MASK_ARBITRATOR & 0x7 ) << 5 ), 0 );
	//}
	///* Put MCP2515 into normal mode */
	//mcp2515TransmitData( MCP_WRITE_CMD, CANCTRL, ( CANCTRL_REQOP_NORMAL << CANCTRL_REQOP_SHIFT ) , 0 );
	
}




  
 /* forceReset ==================================================  */
 /**
 * @fn 			void forceReset (void)
 * @brief  		Function to call reset handler
 * @attention	After calling this function procedure of BINDING probably should be executed
 * @param[in]	void
 * @return 		void
 */
 void forceReset ( void ) {
   cli(); 					// disable interrupts
   //wdtEnable(WDTO_15MS); 	// enable watchdog
   while(1); 				// wait for watchdog to reset processor
 }



 /* hal_msg_poll =====================================  */
 /**
 * @fn 			void hal_msg_poll ( void )
 * @brief  		Function to retry fetching an incoming message left in CAN controller
 *				by triggering software interrupt responsible for receiving.
 * @param[in]	void
 * @return 		void
 */
 void hal_msg_poll ( void ){
	//triggerSoftwareInterrupt( TRIGGER_RECEIVING );
 }
