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
 #include "irqHandlers.h"
 
 #include "can.h"	//at90can
 
 /* Variables for time measuring - in testing */
 extern volatile uint16_t time;
 extern volatile uint8_t flag;

 /* Terminal messages */ 
 #if ( CONFIG_DEBUG_UART_INFO )
 	char* strMERRE = "MERRE error \r";
 	char* strERROR = "Error interrupt occured \r";
 #endif

 
 
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
 
 
 /* ISR ( CONFIG_MCP_INT) ===================================== */
 /**
 * @name 		CONFIG_MCP_INT Interrupt handler
 * @brief  		MCP2515 interrupt handler
 * @param[in]	void
 * @return 		void
 */
 ISR( CONFIG_MCP_INT ){
 
	/* Temporary data */
	volatile static uint8_t tmpData, tmpData2;
	 
	/* Disable interrupts */
	cli();
	 
	/* Read status register in MCP2515 */
	transmitSpi( MCP_READ_CMD );
	transmitSpi( CANINTF );
	tmpData = transmitSpi( DUMMY_DATA );
	MCP_DEACTIVATE;

	if ( tmpData ){

		/* Message Error Interrupt */
		if ( tmpData & ( 1 << CANINTF_FLAG_MERRF )){
		
			/* ONLY FOR DEBUGGING */
				#if ( CONFIG_DEBUG_LED_TOGGLING && !CONFIG_DEBUG_CAPACITY )
					HW_PORT_LED ^= ( 1 << HW_PORT_LED2 );
				#endif
				
				#if ( CONFIG_DEBUG_UART_INFO )
					printUsart( strMERRE );
				#endif
			/* ONLY FOR DEBUGGING */
			
			msgError = 1;
			clearMCP2515InterruptFlag( CANINTF, CANINTF_FLAG_MERRF );
		}
		
			
		/* Wakeup Interrupt */
		if ( tmpData & ( 1 << CANINTF_FLAG_WAKIF )){
			wakeUp = 1;
			clearMCP2515InterruptFlag( CANINTF, CANINTF_FLAG_WAKIF );
		}
			
		/*
		Error Interrupt */
		if ( tmpData & ( 1 << CANINTF_FLAG_ERRIF )){
		
			/* Read status register in MCP2515 */
			transmitSpi( MCP_READ_CMD );
			transmitSpi( EFLG );
			tmpData2 = transmitSpi( DUMMY_DATA );
	 		MCP_DEACTIVATE;
			
			
			
			if ( tmpData2 ){
				if ( tmpData2 & ( 1 << EFLG_RX1OVR ) ){
					errorStructure.recBufOvf1++;
					clearMCP2515InterruptFlag( EFLG, EFLG_RX1OVR );
				}
				
				if ( tmpData2 & ( 1 << EFLG_RX0OVR ) ){
					errorStructure.recBufOvf0++;
					clearMCP2515InterruptFlag( EFLG, EFLG_RX0OVR );
				}
				
				if ( tmpData2 & ( 1 << EFLG_TXBO ) )
					errorStructure.busOffError++;
				
				if ( tmpData2 & ( 1 << EFLG_TXEP ) )
					errorStructure.transmitPassive++;
				
				if ( tmpData2 & ( 1 << EFLG_RXEP ) )
					errorStructure.receivePassive++;
				
				if ( tmpData2 & ( 1 << EFLG_TXWAR ) )
					errorStructure.transmitWarning++;
					
				if ( tmpData2 & ( 1 << EFLG_RXWAR ) )
					errorStructure.receiveWarning++;
				
				if ( tmpData2 & ( 1 << EFLG_EWARN ) )
					errorStructure.errorWarning++;
			}

			transmitError = 1;
			clearMCP2515InterruptFlag( CANINTF, CANINTF_FLAG_ERRIF );
		}
		
		
		/* Transmit Buffer 2 Empty Interrupt */
		if ( tmpData & ( 1 << CANINTF_FLAG_TX2IF )){
			
			/* allow msg sending */ 
			txBuf2Ready = 1;
			clearMCP2515InterruptFlag( CANINTF, CANINTF_FLAG_TX2IF );
		}
			
			
		/* Transmit Buffer 1 Empty Interrupt */
		if ( tmpData & ( 1 << CANINTF_FLAG_TX1IF )){
			
			/* allow msg sending */ 
			txBuf1Ready = 1;
			clearMCP2515InterruptFlag( CANINTF, CANINTF_FLAG_TX1IF );
		}
			
			
		/* Transmit Buffer 0 Empty Interrupt */
		if ( tmpData & ( 1 << CANINTF_FLAG_TX0IF )){
			
			/* allow msg sending */ 
			txBuf0Ready = 1;
			clearMCP2515InterruptFlag( CANINTF,CANINTF_FLAG_TX0IF );
		}
			
			
		/* Receive Buffer 1 Full Interrupt */
		if ( tmpData & ( 1 << CANINTF_FLAG_RX1IF )){
			
			/* trigger msg receiving */ 
			rxBuf1Full = 1;
			triggerSoftwareInterrupt( TRIGGER_RECEIVING );
		}
			
			
		/* Receive Buffer 1 Full Interrupt */
		if ( tmpData & ( 1 << CANINTF_FLAG_RX0IF )){
			
			/* trigger msg receiving */ 
			rxBuf0Full = 1;
			triggerSoftwareInterrupt( TRIGGER_RECEIVING );
		}
	 }
	 
	 /* enable interrupts */
	 sei();
 }
 
 
 
#if ( CONFIG_TESTING_HAL )
 /**
 * @name 		TIMER0_OVF_VECT Interrupt handler
 * @brief  		TIMER0 Overflow interrupt handler - used for time measurement in testing modes
 * @param[in]	void
 * @return 		void
 */
 ISR ( TIMER0_OVF_VECT ){
	
	static volatile uint16_t counter;
	volatile uint8_t sendOnce;

	/* Disable interrupts */
	cli();
	
	/* Counter value incrementation */
	counter++;
	
	/*  */ 
	switch ( counter ){
	
		case ( 6*TIME_PERIOD ):	// ca every 100 ms
			
			HW_PORT_LED ^= ( 1 << HW_PORT_LED2 );
			if (flag) time++;
			counter = 0;
			
			break;
				
		default:
			break;
	}

	/* Enable interrupts */
	sei();
	
 }
#endif






 
 /* ISR ( CONFIG_INT_RECEIVING) ===================================== */
 /**
 * @name 		CONFIG_INT_RECEIVING Interrupt handler
 * @brief  		External Interrupt handler
 * @param[in]	void
 * @return 		void
 */
 ISR ( CONFIG_INT_RECEIVING ) {
	
	/* Disable interrupts */
	cli();
	
	if ( rxBuf0Full )
		//receiveCanMsg( NULL, REC_REG_0 );		//* for HAL testing (prototype in irqHandlers.h must be changed!
		receiveCanMsg( REC_REG_0 );				//* trigger receiving from buffer 0
	if ( rxBuf1Full )
		//receiveCanMsg( NULL, REC_REG_1 );		//* for HAL testing (prototype in irqHandlers.h must be changed!
		receiveCanMsg( REC_REG_1 );				//* trigger receiving from buffer 1

	/* Enable interrupts */
	sei();
 }

 
 
 #if ( CONFIG_DEBUG_TEST_HLL )	
 /* ISR ( CONFIG_INT_SENDING) ===================================== */
 /**
 * @name 		CONFIG_INT_SENDING Interrupt handler
 * @brief  		External Interrupt handler
 * @param[in]	void
 * @return 		void
 */
 ISR ( CONFIG_INT_SENDING ) {
	
	/* Disable interrupts */
	cli();
	
	/* Data */
	volatile uint8_t sendOnce;
	struct can_msg* ptrToMsg;
	
	/* Fetch message to sent from High Protocol Layer */
	ptrToMsg = hll_msg_get();
	
	/* Put MCP2515 into normal mode */
	mcp2515TransmitData( MCP_WRITE_CMD, CANCTRL, ( CANCTRL_REQOP_NORMAL << CANCTRL_REQOP_SHIFT ) , 0 );
					
	/* Prioritization */
	uint8_t prior;						//* must be non-volatile, otherwise stop sending, why?
	if ( (txBuf2Ready) || ( txBuf1Ready ) || (txBuf0Ready ) || !sendOnce) {
		prior =  ( ptrToMsg->id & ( ( 1 << 10 ) | ( 1 << 9 ) ) ) >> 9;
					
		/* Highest msg priority -> put msg into highest transmission priority register */
		if ( prior == 0 ){
			if ( txBuf0Ready || !sendOnce ) 		sendCanMsg( ptrToMsg, SEND_REG_0);
			else if ( txBuf1Ready || !sendOnce ) 	sendCanMsg( ptrToMsg, SEND_REG_1);
			else if ( txBuf2Ready || !sendOnce ) 	sendCanMsg( ptrToMsg, SEND_REG_2);
		}			
		else if ( prior == 1 ){
			if ( txBuf1Ready || !sendOnce )			sendCanMsg( ptrToMsg, SEND_REG_1);
			else if ( txBuf2Ready || !sendOnce )	sendCanMsg( ptrToMsg, SEND_REG_2);
			else if ( txBuf0Ready || !sendOnce ) 	sendCanMsg( ptrToMsg, SEND_REG_0);
		}
				
		else{
			if ( txBuf1Ready || !sendOnce ) 		sendCanMsg( ptrToMsg, SEND_REG_1);
			else if ( txBuf2Ready || !sendOnce ) 	sendCanMsg( ptrToMsg, SEND_REG_2);
			else if ( txBuf0Ready || !sendOnce ) 	sendCanMsg( ptrToMsg, SEND_REG_0);
		}
					
		sendOnce = 1;
	}	

	/* Free pointer to structure */
	hll_msg_free ( ptrToMsg );
	
	/* Enable interrupts */
	sei();
 }
#endif
 
 

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
 
 
 
 
  /* ISR ( BADISR_vect) ===================================== */
 /**
 * @name 		BADISR_vect BADisr
 * @brief  		BADISR_vect handler - fired just before processor 
 *				reset in case of memory problems...
 * @param[in]	void
 * @return 		void
 */
 ISR ( BADISR_vect ){
 	static char *tmp = "Default handler fired!\r";
	printUsart(tmp);
 }

 
 
 /* FUNCTIONS ========================================================= */
 /* =================================================================== */
 
 /* receiveCanMsg ===================================== */
 /**
 * @fn 			void receiveCanMsg ( uint8_t regRec )
 * @brief  		Internal function in order to receive message from CAN controller (MCP2515)
 *
 * @param[in]	regRec	Number of register with received message ( defined in MCP2515control.h )
 * @return		void
 */ 
 //void receiveCanMsg ( struct can_msg* msgRec, uint8_t regRec ){
 void receiveCanMsg ( uint8_t regRec ){

	 /* AT90CAN128 using canlib */
	 
	 
	 /* AT90CAN128 END*/

#if ( !CONFIG_DEBUG_TEST_HLL )							//* only for HAL testing
	volatile uint8_t loopCounter = 0;					//* auxiliary variable
	volatile uint8_t regShift = regRec * REG_OFFSET;	//* offset depending of buffer register number
	
		
	/* Reading msg identifier */		
	msgRec->id = mcp2515TransmitData ( MCP_READ_CMD, RXB0SIDH + regShift, DUMMY_DATA , 0 );
	readBuffer = mcp2515TransmitData ( MCP_READ_CMD, RXB0SIDL + regShift, DUMMY_DATA , 0 );
	msgRec->id |= ((msgRec->id) << 3) | ( ( readBuffer & 0xE0 ) >> 5 );	//* SID2, SID1, SID0
				
	/* Reading msg length */
	msgRec->len = mcp2515TransmitData ( MCP_READ_CMD, RXB0DLC + regShift, DUMMY_DATA, 0 );

	/* Reading data msg */
	for ( loopCounter = 0; loopCounter < msgRec->len; loopCounter++ )
		msgRec->data [ loopCounter ] = mcp2515TransmitData ( MCP_READ_CMD, ( RXB0D0 + regShift + loopCounter ) , DUMMY_DATA, 0 );
				
	
	/* Mgs received - flag clearings */	
	if ( !regRec ){
		rxBuf0Full = 0;
		clearMCP2515InterruptFlag ( CANINTF, CANINTF_FLAG_RX0IF );
	}
	else{
		rxBuf1Full = 0;	
		clearMCP2515InterruptFlag ( CANINTF, CANINTF_FLAG_RX1IF );
	}
	
	/* CAN controller - deactivation */	
	MCP_DEACTIVATE;
	
	
#else


														//* for whole designed interface testing
	volatile uint8_t tmp;
	volatile uint8_t loopCounter = 0;					//* auxiliary variable
	volatile uint8_t regShift = regRec * REG_OFFSET;	//* offset depending of buffer register number
	
	/* Msg alloc */
	struct can_msg* ptr = hll_msg_alloc ( );
	
	/* Reading msg identifier */		
	ptr -> id = mcp2515TransmitData ( MCP_READ_CMD, RXB0SIDH + regShift, DUMMY_DATA , 0 );
	tmp = mcp2515TransmitData ( MCP_READ_CMD, RXB0SIDL + regShift, DUMMY_DATA , 0 );
	ptr -> id = ((ptr -> id) << 3) | ( ( tmp & 0xE0 ) >> 5 );	//* SID2, SID1, SID0
				
	/* Reading msg length */
	ptr -> len = mcp2515TransmitData ( MCP_READ_CMD, RXB0DLC + regShift, DUMMY_DATA, 0 );

	/* Reading data msg */
	for ( loopCounter = 0; loopCounter < ptr -> len; loopCounter++ )
		ptr -> data [ loopCounter ] = mcp2515TransmitData ( MCP_READ_CMD, ( RXB0D0 + regShift + loopCounter ) , DUMMY_DATA, 0 );
	
	#if ( ( CONFIG_BUS_MODE == BUS_ARBITRATOR ) && CONFIG_DEBUG_UART_INFO )
		char str[50];
		sprintf(str,"\rPID = %x, VID = %x, SID = %x\r",*((uint16_t*)(ptr->data+1)), *((uint16_t*)(ptr->data+3)), *((uint16_t*)(ptr->data+5)));
		printUsart(str);
	#endif

	#if ( CONFIG_DEBUG_LED_TOGGLING ) 
		HW_PORT_LED ^= ( 1 << HW_PORT_LED1 );
	#endif
	
	/* Mgs received - flag clearings */	
	if ( !regRec ){
		rxBuf0Full = 0;	
		clearMCP2515InterruptFlag ( CANINTF, CANINTF_FLAG_RX0IF );
	}
	else{
		rxBuf1Full = 0;
		clearMCP2515InterruptFlag ( CANINTF, CANINTF_FLAG_RX1IF );
	}	

	/* Msg commit */
	hll_msg_commit ( ptr );
	
	/* CAN controller - deactivation */	
	MCP_DEACTIVATE;

#endif
 }
 
 
 
 /* sendCanMsg ===================================== */
 /**
 * @fn 			void sendCanMsg ( struct can_msg* msgToSend, uint8_t regToSend )
 * @brief  		Internal function which task is to send message through CAN controller (MCP2515)
 * @param[in]	msgToSend*	Pointer to structure filled with message content
 * @param[in]	regToSend	Number of register to send message ( defined in MCP2515control.h )
 * @return 		void
 */ 
  void sendCanMsg ( struct can_msg* msgToSend, uint8_t regToSend ){
	  
	 /* AT90CAN128 using canlib */
 
 	CAN_packet *canMsg;
	char mob;
	uint8_t i;
	 
	canMsg->id = msgToSend->id;
	canMsg->length = msgToSend->len;
	
	for(i=0; i<msgToSend->len; i++){
		canMsg->data[i] = msgToSend->data[i];	
	}
	
	mob = 14; //What mob to use?
	can_tx(mob, canMsg);
	
	/* Clear internal flags of transmit buffer ready */
	if ( regToSend == 2 ){
		txBuf2Ready = 0;
	}else if ( regToSend == 1 ){
		txBuf1Ready = 0;
	}else{
		txBuf0Ready = 0;
	}
	 

 
	/* AT90CAN128 END*/
	
	
 //
	//uint8_t loopCounter;
	//uint8_t regShift = regToSend * REG_OFFSET;
	//volatile char str[40];
	//
	//#if ( CONFIG_DEBUG_UART_INFO )
		//sprintf(str,"Arbitration field of sent msg: %x\r",msgToSend->id );
			//printUsart(str);
//
		//sprintf(str,"NodeID of sent msg: %x\r",msgToSend->data[1]);
			//printUsart(str);
	//#endif
	//
	///* Send identifier SIDH and SIDL */	
	//mcp2515TransmitData( MCP_WRITE_CMD, TXB0SIDH + regShift, ( msgToSend->id >> 3 ) , 0 );
	//mcp2515TransmitData( MCP_WRITE_CMD, TXB0SIDL + regShift, ( ( msgToSend->id & 0x7 ) << 5 ) , 0 );
					//
	///* Send length */			
	//mcp2515TransmitData( MCP_WRITE_CMD, TXB0DLC + regShift, ( msgToSend->len & 0xF ) , 0 );
	//
	///* Send bytes of msgToSend */
	//for ( loopCounter = 0; loopCounter < ( msgToSend->len ); loopCounter++ )
		//mcp2515TransmitData( MCP_WRITE_CMD, ( TXB0D0 + regShift + loopCounter ), ( msgToSend->data[loopCounter] ) , 0 );
				//
					//
	///* Send information - buffer ready for transmission, physical layer wait for free bus */								
	//mcp2515TransmitData( MPC_BIT_MODIFY, TXB0CTRL + regShift, ( 1 << TXBCTRL_TXREQ ) , SET_BIT);
//
	///* Clear internal flags of transmit buffer ready */
	//if ( regToSend == 2 )
		//txBuf2Ready = 0;
	//else if ( regToSend == 1 )
		//txBuf1Ready = 0;
	//else 
		//txBuf0Ready = 0;
											//
	//#if ( CONFIG_DEBUG_LED_TOGGLING ) 
		//HW_PORT_LED ^= ( 1 << HW_PORT_LED0 );
	//#endif
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
	triggerSoftwareInterrupt( TRIGGER_RECEIVING );
 }



  /* clearMCP2515InterruptFlag =====================================  */
 /**
 * @fn 			void clearMCP2515InterruptFlag( uint8_t reg, uint8_t flag )
 * @brief  		Function to reset clear flags inside of CAN controller.
 * @param[in]	reg		Register containing a flag
 * @param[in]	flag	Flag to reset
 * @return 		void
 */
 void clearMCP2515InterruptFlag( uint8_t reg, uint8_t flag ){
	transmitSpi( MPC_BIT_MODIFY );		//* Put MCP2515 in bit modify mode
	transmitSpi( reg );					//* Register name - CANINTF
	transmitSpi( 1 << flag );			//* Treated as a mask
	transmitSpi( 0 << flag );			//* Treated as a data	
	MCP_DEACTIVATE;						//* CAN controller - deactivation
 }
 
