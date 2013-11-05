/***********************************************************************//**
 * @file		functions.c
 * @brief		Contains functions definitions which are relevant for interface between 
 *				lower and upper layers of PDCP ( mainly HAL )
 *
 * @details		
 *
 *
 * @author		Andrzej Zamojski ( NTNU )			
 * @date		1 VI 2012
 **************************************************************************/

 #include <avr/io.h>
 #include <avr/wdt.h>
 #include <stdint.h>
 #include "functions.h"

#include "can.h"
 

 
 /* initLowLevelProtocolHardware ================================= */
 /**
 * @fn 			void initLowLevelProtocolHardware ( void )
 * @brief  		Function to initialize all important ports and methods for LLP hardware
 * @param[in]	void
 * @return 		void
 */
 void initLowLevelProtocolHardware ( void ) {
	
	/* Leds - only for testing */
	/*
	#if ( CONFIG_DEBUG_LED_TOGGLING )	
		HW_DDR_LED = 0xFF;
		HW_PORT_LED = 0xFF;
	#endif
	*/
	
	/* Init I/O, SPI ports and application designer ports if needed */
	initIOPort();					
	
	//initSpi();	
	
	#if ( CONFIG_DEBUG_UART_INFO ) 
		initUSART( RS_UBRR );
	#endif

	/* CAN configuration */	
	if ( CONFIG_BUS_MODE )			
		initCan( CONFIG_ARB_DEF_ID );
	else if ( !CONFIG_BUS_MODE )
		initCan( CONFIG_DEVICE_DEF_ID );
	
	/* Init interrupts properties */
	initInterrupts( );				
	
	/* Set watchdog timer properties */
	wdtDisable();	
	  
  }

 /*  initSpi =====================================  */
 /**
 * @fn 			SPI_INIT_STATUS initSpi()
 * @brief  		SPI Interface Initialization
 * @return 		SPI_INIT_STATUS 	Status of Initialization (enum SPI_INIT_STATUS)
 */
 SPI_INIT_STATUS initSpi(){
	
	/** Port initialization done in InitPorts function */
	
	/* Enable SPI, Master mode */
	SPI_SPCR |=	( 1 << SPCR_SPE ) | ( 1 << SPCR_MSTR ) ;
	SPI_SPCR &= ~( ( 1 << SPCR_SPIE ) | (1 << SPCR_SPR1 ) | (1 << SPCR_SPR0 ));	// Now set on FCK/4 
		
	return SPI_INIT_OK;
	/* for future purposes -> return SPI_INIT_FAIL; */
 }


 /* transmitSpi =====================================  */
 /**
 * @fn 			uint8_t transmitSpi ( uint8_t data )
 * @brief  		SPI Transmit Data
 * @details		May be called <b>after PIN initialization</b>
 * @param[in]	data		Data to transmission
 * @return 		uint8_t 	Result of SPI transmission (data)	
 */
 uint8_t transmitSpi ( uint8_t data ){
	
	/* Activate device CS = 0 */
	//HW_CS_MCP2515_PORT &= ~( 1 << HW_CS_MCP2515 );
 
	/* Start transmission */ 
	////SPI_SPDR = ( char ) data;
	
	/* Waiting for end of transmission */
	//while( !( SPI_SPSR & ( 1 << SPSR_SPIF ) ) );
	
	/* Return result of transmission */
	return ( ( uint8_t ) SPI_SPDR );
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
	 
	 can_init(); //by geir
	 
	///* Set masks & filters */
	//hal_set_filter(id);
	//hal_set_mask(id);
	//
	///* Reset error structure */
	//clearTransmissionErrors( );
	 
	 return CAN_INIT_OK;
	//
	//cli();
		//
	///* Call reset command */
	//transmitSpi( MCP_RESET );
	//MCP_DEACTIVATE;
		//
		//
	///* Put MCP into configuration mode */
	//MCP_DEACTIVATE;	
	//mcp2515TransmitData( MCP_WRITE_CMD, CANCTRL, ( CANCTRL_REQOP_CONFIGURATION << CANCTRL_REQOP_SHIFT ), 0 );
		//
	///* CNF1 */
	////dataToSend = 0xC1;				//* for 250 kbps
	////dataToSend = 0x00;				//* for 500 kbps
	//dataToSend = 0xC0;					//* for 1 Mbps
	//mcp2515TransmitData( MCP_WRITE_CMD, CNF1, dataToSend, 0 );
		//
	///* CNF2 */
	////dataToSend = 0xB5;				//* for 250 kbps
	////dataToSend = 0xA4;				//* for 500 kbps
	//dataToSend = 0x89;					//* for 1 Mbps
	//mcp2515TransmitData( MCP_WRITE_CMD, CNF2, dataToSend, 0 );
		//
	///* CNF3 */
	////dataToSend = 0x01;				//* for 250 kbps
	////dataToSend = ( 0x04 );			//* for 500 kbps
	//dataToSend = ( 0x02 );				//* for 1 Mbps
	//mcp2515TransmitData( MCP_WRITE_CMD, CNF3, dataToSend, 0 );
		//
	///* Put MCP into normal mode */
	//MCP_DEACTIVATE;	
	//mcp2515TransmitData( MCP_WRITE_CMD, CANCTRL, ( CANCTRL_REQOP_NORMAL << CANCTRL_REQOP_SHIFT ), 0 );
	//
	//
	//
	///* Switch on particular interrupts */		
	//dataToSend = 	/*( 1 << CANINTE_MERRE ) */( 1 << CANINTE_ERRIE ) | 
					//( 1 << CANINTE_TX2IE ) | ( 1 << CANINTE_TX1IE ) | ( 1 << CANINTE_TX0IE ) | 
					//( 1 << CANINTE_RX1IE ) | ( 1 << CANINTE_RX0IE );
	//mcp2515TransmitData( MCP_WRITE_CMD, CANINTE, dataToSend, 0 );
	//
	///* Clear all interrupt flags */
	//mcp2515TransmitData( MCP_WRITE_CMD, CANINTF, 0x00, 0 );
		//
	///* Set receiving buffer properties */				
	///* --- receive only valid msgs with standard identifiers, rollover */
	//dataToSend = 	( RXB0CTRL_RXM_ONLY_VALID_STAND_ID << RXB0CTRL_RXM0 ) | 
					//( 1 << RXB0CTRL_BUKT );
	//mcp2515TransmitData( MPC_BIT_MODIFY, RXB0CTRL, dataToSend, SET_BIT );
	//mcp2515TransmitData( MPC_BIT_MODIFY, RXB1CTRL, ( RXB1CTRL_RXM_ONLY_VALID_STAND_ID << RXB1CTRL_RXM0 ) , SET_BIT );
		//
			//
	///* TXBxCTRL	*/
	///* Set transmitting buffer properties - standard identifier, priorities */
	///* TXB0CTRL - highest, TXB1CTRL - intermediate, TXB2CTRL - intermediate */
	//mcp2515TransmitData( MPC_BIT_MODIFY, TXB0CTRL, ( TXP_HIGHEST_MSG_PRIORITY << TXBCTRL_TXP ) , SET_BIT );
	//mcp2515TransmitData( MPC_BIT_MODIFY, TXB1CTRL, ( TXP_HIGH_INTERMEDIATE_MSG_PRIORITY << TXBCTRL_TXP ) , SET_BIT );
	//mcp2515TransmitData( MPC_BIT_MODIFY, TXB2CTRL, ( TXP_HIGH_INTERMEDIATE_MSG_PRIORITY << TXBCTRL_TXP ) , SET_BIT );
				//
	///* Set masks & filters */
	//hal_set_filter(id);
	//hal_set_mask(id);
		//
	///* Reset error structure */
	//clearTransmissionErrors( );
	//
	//MCP_DEACTIVATE;
	//return CAN_INIT_OK;

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
	MCP_DEACTIVATE;	
	mcp2515TransmitData(MCP_WRITE_CMD, CANCTRL, ( CANCTRL_REQOP_CONFIGURATION << CANCTRL_REQOP_SHIFT ), 0 );

	if ( CONFIG_BUS_MODE == BUS_DEVICE ){

		/* set filter 0 for DEVICE CONFIG_BUS_MODE */
		mcp2515TransmitData(MCP_WRITE_CMD, RXF0SIDH, ( id >> 3 ) , 0 );
		mcp2515TransmitData(MCP_WRITE_CMD, RXF0SIDL, ( ( id & 0x7 ) << 5 ) , 0 );

		/* set filter 1 for DEVICE CONFIG_BUS_MODE */
		mcp2515TransmitData(MCP_WRITE_CMD, RXF1SIDH, ( id >> 3 ) , 0 );
		mcp2515TransmitData(MCP_WRITE_CMD, RXF1SIDL, ( ( id & 0x7 ) << 5 ) , 0 );

		/* set filter 2 for DEVICE CONFIG_BUS_MODE - for broadcast messages */
		mcp2515TransmitData(MCP_WRITE_CMD, RXF2SIDH, ( 0x00 >> 3 ) , 0 );
		mcp2515TransmitData(MCP_WRITE_CMD, RXF2SIDL, ( ( 0x00 & 0x7 ) << 5 ) , 0 );
	}
	else if ( CONFIG_BUS_MODE == BUS_ARBITRATOR ){
	
		/* set filter 0 for ARBITRATOR CONFIG_BUS_MODE - receive all messages */	
		mcp2515TransmitData(MCP_WRITE_CMD, RXF0SIDH, 0x00 , 0);		
		mcp2515TransmitData(MCP_WRITE_CMD, RXF0SIDL, 0x00 , 0);
	}

	/* Put MCP2515 into normal mode */
	mcp2515TransmitData( MCP_WRITE_CMD, CANCTRL, ( CANCTRL_REQOP_NORMAL << CANCTRL_REQOP_SHIFT ) , 0 );
	
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
	MCP_DEACTIVATE;	
	mcp2515TransmitData(MCP_WRITE_CMD, CANCTRL, ( CANCTRL_REQOP_CONFIGURATION << CANCTRL_REQOP_SHIFT ), 0 );

	if ( CONFIG_BUS_MODE == BUS_DEVICE ){

		/* Set mask 0 for DEVICE CONFIG_BUS_MODE */
		mcp2515TransmitData(MCP_WRITE_CMD, RXM0SIDH, ( MASK_DEVICE >> 3 ) , 0 );
		mcp2515TransmitData(MCP_WRITE_CMD, RXM0SIDL, ( ( MASK_DEVICE & 0x7 ) << 5 ) , 0 );

		/* Set mask 1 for DEVICE CONFIG_BUS_MODE */
		mcp2515TransmitData(MCP_WRITE_CMD, RXM1SIDH, ( MASK_DEVICE >> 3 ) , 0 );
		mcp2515TransmitData(MCP_WRITE_CMD, RXM1SIDL, ( ( MASK_DEVICE & 0x7 ) << 5 ) , 0 );

	}	
	else if ( CONFIG_BUS_MODE == BUS_ARBITRATOR ){

		/* Set mask 0 for ARBITRATOR CONFIG_BUS_MODE */
		mcp2515TransmitData(MCP_WRITE_CMD, RXM0SIDH, ( MASK_ARBITRATOR >> 3 ), 0 );
		mcp2515TransmitData(MCP_WRITE_CMD, RXM0SIDL, ( ( MASK_ARBITRATOR & 0x7 ) << 5 ), 0 );
	}
	/* Put MCP2515 into normal mode */
	mcp2515TransmitData( MCP_WRITE_CMD, CANCTRL, ( CANCTRL_REQOP_NORMAL << CANCTRL_REQOP_SHIFT ) , 0 );
	
}



 
 
 
 
 /* initInterrupts ================================================= */
 /**
 * @fn 		 	void initInterrupts( void )
 * @brief  		Initialize all needed interrupts (TIMERS, EXTx..)
 * @details		Contains call to function initInterrupts_appDesigner() which should contain @n
 *				initialization of interrupts indispensible for application (empty by default)
 * @attention	User must be careful with EXT_EICRA and EXT_EICRB registers, because automation of this process
 *				would be too complicated, therefore user should take a look at microcontroller documentation
 *				and set registers value properly.
 * @param[in]	void
 * @return 		void
 */
 void initInterrupts( void ){
	
	/* Interrupt initialization indispensible for application, default - empty function */
	initInterrupts_appDesigner();


#if ( CONFIG_TESTING_HAL )
	/* timer interrupt initialization  */
	TIMER0_TCCR0A &= ~(	( 1 << TIMER0_COM0A1 ) | ( 1 << TIMER0_COM0A1 ) |	  						//* normal port operation COM0A1 COM0A0 = 00
						( 1 << TIMER0_WGM02 ) | ( 1 << TIMER0_WGM01 ) | ( 1 << TIMER0_WGM00 ) );	//* mode of operation = NORMAL
						
	TIMER0_TCCR0B |= ( 1 << TIMER0_CS01 ) | ( 1 << TIMER0_CS00 );		//* prescaling (clk/8);
	TIMER0_TCNT = 0;							//* reset TIMER0 value
	TIMER0_TIMSK0 |= ( 1 << TIMER0_TOIE0 );		//* activate TIMER0 Overflow Interrupt
#endif



	/* External interrupt initialization */
	/* Falling edge of INT(HW_MCP_EXT_INT) [set in uCmaskFile.h]
		triggers interrupt	*/
	//EXT_EICRA |= ( EXT_TRIGGER_FALLING_EDGE << HW_MCP_EXT_INT ) | ( EXT_TRIGGER_FALLING_EDGE << 2 );
	
	/* Activating an external interrupt of number described in HW_MCP_EXT_INT */
	//EXT_INT_EIMSK |= ( 1 << HW_MCP_EXT_INT );
	
	
	/* Software interrupt initialization (pin change interrupt control reg) */
	//EXT_EICRB |= ( 0x1 << 2 )|( 0x1 << 0 );												// must be checked before
	//EXT_INT_EIMSK |= ( 1 << CONFIG_INT_SEND_NUM ) | ( 1 << CONFIG_INT_REC_NUM );		// INT5, INT4 now
	
 }
 
 
 /* initIOPort ========================================================== */
 /**
 * @fn 			void initIOPort( void )
 * @brief  		Place for I/O pins initialization 
 * @details		Contains call to function initIOPort_appDesigner() which should contain @n
 *				initialization of IO Ports indispensible for application (empty by default)
 * @param[in]	void
 * @return 		void
 */
 void initIOPort( void ){
	 	 
	 /* Initialization IO port indispensible for application, default - empty function */
	 initIOPort_appDesigner();
	 
	 /* Init SPI port */
	 //initSPIPorts();
	 
	 /* Init software interrupt ports */
	 initINTPorts();
 }
 


 
 /* initIOPort_appDesigner ============================================= */
 /**
 * @fn 			void initIOPort_appDesigner( void )
 * @brief  		Place for I/O pins initialization left for application designer
 * @details		Can consist of I2C, pins, interfaces etc. initialization
 * @attention	Be careful about ports relevant for communication interface
 * @param[in]	void
 * @return 		void
 */
 void initIOPort_appDesigner( void ){
	//* place for port initialization code executed within initIOPort() function
	//*	be careful about port relavant for proper operation of Interface (look at uCmaskFile.h)
	
	/* code here */
	
 }

 

 /* initInterrupts_appDesigner ======================================== */
 /**
 * @fn 			void initInterrupts_appDesigner( void )
 * @brief  		Place for interrupt initialization left for application designer
 * @attention	Be careful about interrupt bits used by interface - always use operator (|) or (&) to not destroy an interface
 * @param[in]	void
 * @return 		void
 */
 void initInterrupts_appDesigner( void ){

	/* code here */
	
 }
 
 

 /* initSPIPorts ====================================================== */
 /**
 * @fn 			void initSPIPorts( void )
 * @brief  		Spi ports initialization
 * @param[in]	void
 * @return 		void
 */
 void initSPIPorts( void ){
	/**	look at uCmaskFile.h where ports are defined */
	
	//* CS port as output
	HW_CS_MCP2515_DDR |= ( 1 << HW_CS_MCP2515 );			
	
	//* SCK port as an output
	HW_SCK_MCP2515_DDR |= ( 1 << HW_SCK_MCP2515 );		
	
	//* CS value = 1
	HW_CS_MCP2515_PORT |= ( 1 << HW_CS_MCP2515 );			
	
	//* MOSI port as an output
	HW_MOSI_MCP2515_DDR |= ( 1 << HW_MOSI_MCP2515 );		
	
	//* MISO port as an input
	HW_MISO_MCP2515_DDR &= ~( 1 << HW_MISO_MCP2515 );		
	 
 }

 

 /* mcp2515TransmitData ============================================== */
 /**
 * @fn 			uint8_t mcp2515TransmitData( uint8_t mode, uint8_t reg, uint8_t val, uint8_t setClearFlag )
 * @brief  		Function to transmit data between MCU and MCP2515
 * @details		Can be called <b>after PIN initialization</b>
 * @param[in]	mode			Mode of operation MCP_WRITE_CMD, MCP_READ_CMD or MPC_BIT_MODIFY
 * @param[in]	reg				Address of register to change/read
 * @param[in]	val				Value to to change: <b>must be a shift value if MPC_BIT_MODIFY is specified, otherwise full value register</b>
 * @param[in]	setClearFlag	If MPC_BIT_MODIFY specified, SET_BIT or CLR_BIT (defined in MCP2515_CAN_control.h file) defines clearing of setting mode
 * @return 		retValue		Read value from MCP2515
 */
 uint8_t mcp2515TransmitData( uint8_t mode, uint8_t reg, uint8_t val, uint8_t setClearFlag ){
		
	volatile uint8_t retValue;
	if ( mode == MPC_BIT_MODIFY ){
		transmitSpi( mode );
		transmitSpi( reg );
		transmitSpi( val );			/* Mask while MPC_BIT_MODIFY specified */
			
		if ( setClearFlag == SET_BIT ) 
			transmitSpi( val );		/* Set bit while MPC_BIT_MODIFY specified */
		else { 
			transmitSpi( ~val );	/* Clear bit while MPC_BIT_MODIFY specified */
			retValue = 0;
		}
	}
	else {
		transmitSpi( mode );
		transmitSpi( reg );
		retValue = transmitSpi( val );
	}
	MCP_DEACTIVATE;
	
	return retValue;
 }
 
 
  /* initINTPorts ===================================================== */
 /**
 * @fn 		 	void initINTPorts( void )
 * @brief  		Software interrupt ports initialization
 * @attention	HW_SOFT_INT_DDR and HW_SOFT_INT_PORT defined in uCmaskFile.h
 * @param[in]	void
 * @return 		void
 */
 void initINTPorts( void ){
	
	/* Software interrupts */
	HW_SOFT_EXT_INT_DDR |= ( 1 << HW_SOFT_EXT_INT_1 ) | ( 1 << HW_SOFT_EXT_INT_2 ) ;

	/* External interrupts */
	/*
	HW_MCP_EXT_INT_DDR &= ~( 1 << HW_MCP_EXT_INT );
	HW_MCP_EXT_INT_PORT |= ( 1 << HW_MCP_EXT_INT );
	*/
 }
  
 
 
 
 /* initUSART ======================================================== */
 /**
 * @fn 		 	void initUSART ( uint16_t )
 * @brief  		Function to initialize all important ports and methods for LLP hardware
 * @param[in]	baud	Baudrate
 * @return 		void
 */
 void initUSART ( uint16_t baud ) {
	
	/* Set baud rate */
	USART_UBRR1H = ( unsigned char )( baud >> 8 );
	USART_UBRR1L = ( unsigned char ) baud;
	
	/* Enable receiver and transmitter */
	USART_UCSR1B = ( 1 << UCSR1B_RXEN1 ) | ( 1 << UCSR1B_TXEN1 );
	
	/* Set frame format: 8 data (USBS), 2 stop bit */
	USART_UCSR1C = ( 1 << UCSR1C_USBS1 ) | ( 3 << UCSR1C_UCSZ10 );
 }
 



 /* triggerSoftwareInterrupt ========================================= */
 /**
 * @fn 		 	void triggerSoftwareInterrupt ( uint8_t )
 * @brief  		Function to trigger software interrupt
 * @attention	Be careful with port number ( in AT90USB1287 higher than 3, because of SPI interface... ) @n
 *				HW_SOFT_INT_PORT declared in uCmaskFile.h
 * @param[in]	void	
 * @return 		void
 */
 void triggerSoftwareInterrupt ( uint8_t port ) {
	HW_SOFT_EXT_INT_PORT ^= ( 1 << port );
 }
 
 

 /* printCharUsart =================================================== */
 /**
 * @fn		 	void printCharUsart ( char )
 * @brief  		Function to send single char through UART
 * @param[in]	sign	Sign to send through USART
 * @return 		void
 */
 void printCharUsart ( char sign ) {
	while ( !( USART_UCSR1A & ( 1 << UCSR1A_UDRE1 )) );
	USART_UDR1 = ( unsigned char ) sign;
 }

 
 /* printUsart ====================================================== */
 /**
 * @fn 			void printUsart ( char* ) 
 * @brief  		Function to send string of chars through UART
 * @param[in]	str		String to send through UART
 * @return 		void
 */
 void printUsart( char* str ) {
 	cli();
	while ( *str )
		printCharUsart( *str++ );
	sei();
 }

  /* hal_msg_take =================================================== */
 /**
 * @fn 			void hal_msg_take()
 * @brief  		Function to trigger message sending
 * @return 		void
 */
void hal_msg_take(){
	triggerSoftwareInterrupt( TRIGGER_SENDING );
}




 /* wdtDisable ====================================================  */
 /**
 * @fn 			void wdtDisable ()
 * @brief  		Function to disable watchdog timer
 * @return 		void
 */
 void wdtDisable (){

 	/* Clear WDRF */
	MCU_MCUSR &= ~( 1 << MCUSR_WDRF );
	
	/* Write logical one to WDCE and WDE while keeping...
		... old prescaler setting to prevent unintentional time-out */
	WDT_WDTCSR |=  ( 1 << WDTCSR_WDCE ) | ( 1 << WDTCSR_WDE );
		
	/* Disable Watchdog */
	WDT_WDTCSR = 0x00;
 }

 
 
 /* wdtEnable ======================================================  */
 /**
 * @name 		wdtEnable
 * @brief  		Function to enable watchdog timer
 * @param[in]	time	Time of WDT reset activation
 * @return 		void
 */
 void wdtEnable ( uint8_t time ){
 	
	/* Start timed sequence */
	WDT_WDTCSR |=  ( 1 << WDTCSR_WDCE ) | ( 1 << WDTCSR_WDE );
		
	/* Set new prescaler setting */
	WDT_WDTCSR = ( ( 1 << WDTCSR_WDE ) | time );

	/* WDT Interrupt enable */
	WDT_WDTCSR |=  ( 1 << WDTCSR_WDCE ) | ( 1 << WDTCSR_WDE );
 }

 /* initEEPROM ===================================================== */
 /**
 * @fn 			void initEEPROM ( void )
 * @brief  		Init EEPROM
 * @return 		void
 */
 void initEEPROM ( void ){
	/* init EEPROM */ 
	/* or in different interrupt */
  
 }
 
 
 
 /* readEEPROM ==================================================== */
 /**
 * @fn 			uint8_t readEEPROM (uint8_t address)
 * @brief  		Read EEPROM
 * @param[in]	address		EEPROM read address
 * @return 		data		EEPROM data
 */
 uint8_t readEEPROM ( uint8_t address ){
	
	/* Wait until completion of previous write */
	while ( EEPROM_EECR & (1<<EEPROM_EEPE) );
	
	/* Set up address register */ 
	EEPROM_EEAR = address;
	
	/* Start eeprom read by writing EERE */
	EEPROM_EECR |= (1<<EEPROM_EERE);
	
	/* Return data from Data Register*/
	return EEPROM_EEDR;
 }

 
 
 /* writeEEPROM ================================================== */
 /**
 * @fn 		 	void writeEEPROM ( uint8_t address, uint8_t data )
 * @brief  		Write EEPROM
 * @param[in]	address		EEPROM write address
 * @param[in]	data		EEPROM write data
 * @return 		void
 */
 void writeEEPROM (uint8_t address, uint8_t data){
		
	/* Wait for completion of previous write ??? */
	while ( EEPROM_EECR & ( 1 << EEPROM_EEPE ) );
	
	/* Set up address and data register */
	EEPROM_EEAR = address;
	EEPROM_EEDR = data;
	
	/* Write logical one to EEMPE */
	EEPROM_EECR |= ( 1 << EEPROM_EEMPE );
	
	/* Start eeprom write by setting EEPE */
	EEPROM_EECR |= ( 1 << EEPROM_EEPE );
	
}
 



 /* checkTransmissionErrors =====================================  */
 /**
 * @fn 			void checkTransmissionErrors ( struct errorStr* )
 * @brief  		Callback function to check whether errors in transmission have occured
 * @param[in]	struct errorStr*	Pointer to structure (type of errorStr) to read errors
 * @return 		void
 */
 void checkTransmissionErrors ( struct errorStr* readErrStr ){
	readErrStr = &errorStructure;
 }
 
 
 /* clearTransmissionErrors =====================================  */
 /**
 * @fn 		 	void clearTransmissionErrors ( void )
 * @brief  		Function to clear error structure
 * @param[in]	void
 * @return 		void
 */
 void clearTransmissionErrors ( void ){
	errorStructure.recBufOvf0 = errorStructure.recBufOvf1 = errorStructure.busOffError = 0;
	errorStructure.transmitPassive = errorStructure.receivePassive = errorStructure.transmitWarning = 0;
	errorStructure.receiveWarning = errorStructure.errorWarning = 0;
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
   wdtEnable(WDTO_15MS); 	// enable watchdog
   while(1); 				// wait for watchdog to reset processor
 }
