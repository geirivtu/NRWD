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
 #include "uCmaskFile.h"
 #include "MCP2515control.h"
 #include "config.h"
 
 
 /* Needed pre-processor directives =============================== */

 #define 	MCP_ACTIVATE		( HW_CS_MCP2515_PORT &= ~( 1<<HW_CS_MCP2515 ) )	
 #define 	MCP_DEACTIVATE		( HW_CS_MCP2515_PORT |= ( 1<<HW_CS_MCP2515 ) )
 #define	MASK_ARBITRATOR		0x00
 #define	MASK_DEVICE			0xFF
 #define	DUMMY_DATA			0x00
 

 /* Structure for error handling ================================== */
 struct errorStr{
	uint8_t recBufOvf0;
	uint8_t recBufOvf1;
	uint8_t busOffError;
	uint8_t	transmitPassive; 
	uint8_t	receivePassive;
	uint8_t	transmitWarning; 
	uint8_t	receiveWarning;
	uint8_t	errorWarning;
 };
 
 struct errorStr errorStructure;
 
 /* Static variables ================================== */
 static volatile uint8_t readBuffer;	
 static volatile uint8_t dataToSend;
 
 /* Enumerated types ================================== */
 /* Enum: SPI - SPI_INIT_STATUS */
 /** @enum		SPI_INIT_STATUS 
 *	 @brief		Status of SPI interface initialization */
 typedef enum {
	SPI_INIT_OK = 0,	
	SPI_INIT_FAILED
 } SPI_INIT_STATUS;
 
 /* Enum: SPI - SPI_TRANS_STATUS */
 /** @enum		SPI_TRANS_STATUS 
 *	 @brief		Status of SPI transmission */
 typedef enum {
	SPI_TRANS_OK = 0,	
	SPI_TRANS_FAILED
 } SPI_TRANS_STATUS;
 
 
 /* Enum: CAN_INIT_STATUS */
 /** @enum		CAN_INIT_STATUS 
 *	 @brief		Status of CAN interface initialization */
 typedef enum {
	CAN_INIT_OK = 0,	
	CAN_INIT_FAILED
 } CAN_INIT_STATUS;
 
 


 
 /* Function declarations ================================== */
  
 /* CAN handling  */
 SPI_INIT_STATUS initSpi ( void );
 uint8_t transmitSpi ( uint8_t data );
 CAN_INIT_STATUS initCan ( uint8_t id );
 void hal_set_filter( uint8_t id );
 void hal_set_mask( uint8_t id );
 
 /* EEPROM functions */
 void initEEPROM ( void );
 uint8_t readEEPROM ( uint8_t address );
 void writeEEPROM ( uint8_t address, uint8_t data );
 
 /* Init interrupts/ports functions */
 void initInterrupts ( void );
 void initIOPort ( void );
 void initIOPort_appDesigner ( void );
 void initInterrupts_appDesigner ( void );
 void initSPIPorts ( void );
 void initINTPorts ( void );
 void initUSART ( uint16_t baud );
  
 /* Error handling functions */ 
 void checkTransmissionErrors ( struct errorStr* readErrStr );
 void clearTransmissionErrors ( void );
 
 /* Others */ 
 uint8_t mcp2515TransmitData ( uint8_t mode, uint8_t reg, uint8_t val, uint8_t setClearFlag );
 void triggerSoftwareInterrupt ( uint8_t port);
 void initLowLevelProtocolHardware ( void );
 void initUSART ( uint16_t baud );
 void printCharUsart ( char sign );
 void printUsart ( char* str );
 void hal_msg_take ( void );
 void wdtEnable ( uint8_t time );
 void wdtDisable ( void );
 void forceReset ( void );
 
 #endif
