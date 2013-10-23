/***********************************************************************//**
 * @file		MCP2515control.h
 * @brief		Contains all macro definitions & function prototypes @n 
 *				for MCP2515 can bus controller
 * @author		Andrzej Zamojski ( NTNU )				
 * @date		10 VI 2012

**************************************************************************/


#ifndef MCP2515_CONTROL_H_
#define MCP2515_CONTROL_H_



/* PRE-PROCESSOR DIRECTIVES =========================================== */

#define SET_BIT					1
#define CLR_BIT					0
 
/* ================================= */

 /* MACRO DEFINES ================================= */
 /* Macro defines for TXBnCTRL ================================= */
 /** @defgroup CAN_TRANSMIT_MACRO_DEFINITIONS CAN Transmit Macro Definitions
 * @{
 * @brief 		Macro defines for TXBnCTRL - CAN Transmit Buffer n Control Register.
 * @details 	Address: 30h, 40h, 50h
 * @author 		AZ
 * @attention 	Read-only registers!
 */

 /** @brief Message Aborted Flag bit - message aborted or completed transmission successfully 
 *	 @attention	Read-only! */
 
 #define TXBCTRL_ABTF						((uint8_t)(6))

 /** @brief Message Lost Arbitration bit - message los arbitration while being sent
 *	 @attention	Read-only! */
 #define TXBCTRL_MLOA						((uint8_t)(5))

 /** @brief Transmission Error Detected Bit - a bus error occurred while transmission 
 *	 @attention	Read-only! */
 #define TXBCTRL_TXERR						((uint8_t)(4))

 /** @brief Message Transmit Request bit - currently pending transmission */
 #define TXBCTRL_TXREQ						((uint8_t)(3))
 
  /** @brief CAN Transmit Buffer Priority */
 #define TXBCTRL_TXP						((uint8_t)(0))
 
 
 
 /* Enum: MCP2515 - TXBnCTRL TXP */
 /** @enum		TXB_TXP
 *	 @brief		Transmit Buffer Priority enum */
 typedef enum {
	TXBCTRL_TXP_LOWEST_MSG_PRIORITY = 0,			/**< Lowest Message Priority */
	TXBCTRL_TXP_LOW_INTERMEDIATE_MSG_PRIORITY,		/**< Low Intermediate Message Priority */
	TXP_HIGH_INTERMEDIATE_MSG_PRIORITY,				/**< High Intermediate Message Priority */
	TXP_HIGHEST_MSG_PRIORITY						/**< Highest Message Priority */
 } TXB_CONTROL_TXP;
 
 /**
 * @}
 */
 /* ================================= */ 
 
 
 
 
 /* Macro defines for RXB0CTRL ================================= */
 /** @defgroup CAN_RECEIVING_MACRO_DEFINITIONS CAN Receive Macro Definitions
 * @{
 * @brief 	Macro defines for RXB0CTRL - CAN Receive Buffer 0 Control Register.
 * @details Address: 60h
 * @author 	AZ
 */

 /** @brief Receive Buffer Operating Mode bits - turn mask/filter off */
 #define RXB0CTRL_RXM1							((uint8_t)(6))
 

 /** @brief Receive Buffer Operating Mode bits - turn mask/filter off */
 #define RXB0CTRL_RXM0							((uint8_t)(5))
 

  /** @brief Received Remote Transfer Request bit 1 - ON, 0 - no remote */
 #define RXB0CTRL_RXRTR							((uint8_t)(3))

 /** @brief Rollover Enable bit
 *	@details 1 - RXB0 message will rollover and be written to RXB1 if RXB0 is full */
 #define RXB0CTRL_BUKT							((uint8_t)(2))


 /** @brief Read-only Copy of BUKT bit (used internally by the MCP2515) */
 #define RXB0CTRL_BUKT1							((uint8_t)(1))


 /** @brief Filter Hit Bit  - indicates which acceptance filter enabled reception of message
 * 	@details 	1 - Acceptance Filter 1 (RXF1)
 *				0 - Acceptance Filter 0 (RXF0)
 * 	@attention If a rollover from RXB0 to RXB1 occurs, the FILHIT bit will reflect the filter that 
 * 	accepted the message that rolled over. */
 #define RXB0_FILHIT							((uint8_t)(0))
 #define RXB0_FILHIT_MASK						((uint8_t)((1<<0)))
 

 
 /* Enum: MCP2515 - RXB0CTRL RXM */
 /** @enum		RXB0_CONTROL_RXM 
 *	 @brief		Message Aborted Flag bit enum */
 typedef enum {
	RXB0CTRL_RXM_ALL_MSG_STAND_EXT_ID = 0,	/**< Receive all valid msgs using either standard or extended identifiers */
	RXB0CTRL_RXM_ONLY_VALID_STAND_ID,		/**< Only valid messages with standard identifier */
	RXB0CTRL_RXM_ONLY_VALID_EXT_ID,			/**< Only valid messages with extended identifier */
	RXB0CTRL_RXM_TURN_OFF_FIL_MASK_ALL_MSG	/**< Turn off masks/filters, receive any messages */
 } RXB0_CONTROL_RXM;
 
 
 
 
 /**
 * @}
 */
 /* ================================= */
 
 
 /* Macro defines for RXB1CTRL ================================= */
 /** @ingroup CAN_RECEIVING_MACRO_DEFINITIONS CAN
 * @{
 * @brief 	Macro defines for RXB1CTRL - CAN Receive Buffer 1 Control Register.
 * @details Address: 70h
 * @author 	AZ
 */

 /** @brief Receive Buffer Operating Mode bits - turn mask/filter off; receive any message */
 #define RXB1CTRL_RXM1				((uint8_t)(6))
 

 /** @brief Receive Buffer Operating Mode bits - turn mask/filter off; receive any message */
 #define RXB1CTRL_RXM0				((uint8_t)(5))


 /** @brief Received Remote Transfer Request bit 1 - ON, 0 - no remote */
 #define RXB1CTRL_RXRTR				((uint8_t)(3))


 /** @brief Filter Hit Bit  - indicates which acceptance filter enabled reception of message
 * 	 @details 
 *				101 - Acceptance Filter 5 (RXF5)
 *				100 - Acceptance Filter 4 (RXF4)
 *				011 - Acceptance Filter 3 (RXF3)
 *				010 - Acceptance Filter 2 (RXF2)
 *				001 - Acceptance Filter 1 (RXF1) 
 *				000 - Acceptance Filter 0 (RXF0)
 *	@attention 	FILTER 1 and FILTER 0 only if BUKT bit set in RXB0CTRL! */
 #define RXB1CTRL_FILHIT_MASK		((uint8_t)	((1<<2)|(1<<1)|(1<<0)))

 

 /* Enum: MCP2515 - RXB1CTRL RXM */
 /** @enum		RXB1_CONTROL_RXM 
 *	 @brief		Message Aborted Flag bit enum */
 typedef enum {
	RXB1CTRL_RXM_ALL_MSG_STAND_EXT_ID = 0,	/**< Receive all valid msgs using either standard or extended identifiers */
	RXB1CTRL_RXM_ONLY_VALID_STAND_ID,		/**< Only valid messages with standard identifier */
	RXB1CTRL_RXM_ONLY_VALID_EXT_ID,			/**< Only valid messages with extended identifier */
	RXB1CTRL_RXM_TURN_OFF_FIL_MASK_ALL_MSG	/**< Turn off masks/filters, receive any messages */
 } RXB1_CONTROL_RXM;
 
 /**
 * @}
 */
 /* ================================= */
 
 


 /* Macro defines for RXBnDLC ================================= */
 /** @defgroup MCP2515_RECEIVE_BUFFER_N_DATA_LENGHT_CODE
 * @{
 * @brief 	Macro defines for RXBnDLC - Receive Buffer n Data Length Code (documentation p.31)
 * @details Address: 65h, 75h
 * @author 	AZ
 */
 
 /** @brief 		Extended Frame Remote Transmission Request bit
 * 	 @details 		Read-only bit - value unknown
 *	 @attention 	Valid only when RXBnSIDL.IDE = '1'! */
 #define	RXB_DLC_RTR			((uint8_t)(6))


 /** @brief 		EID6 of Extended Identifier LOW 
 *	 @details 		Read-only bits - value unknown */
 #define	RXB_DLC_MASK		((uint8_t)((1<<3)|(1<<2)|(1<<1)|(1<<0)))

 /**
 * @}
 */
 /* ================================= */
 

 
 
 /* Macro defines for EFLG ================================= */ 
 /** @defgroup MCP2515_ERROR_HANDLING
 * @{
 * @brief 	Macro defines for EFLG (documentation p. 47)
 * @details Address: 2Dh
 * @author 	AZ
 */
 
 /** @brief 		RX1OVR
 *	 @details 		Receive Buffer 1 Overflow Flag bit
 *   @attention		Set when valid message is received for RXB1 and CAINTF.RX1IF = 1
 *					R/W, bit is cleared, must be reset by MCU */
 #define	EFLG_RX1OVR		((uint8_t)(7))
 

 /** @brief 		RX0OVR
 *	 @details 		Receive Buffer 0 Overflow Flag bit
 *   @attention		Set when valid message is received for RXB0 and CAINTF.RX0IF = 1
 *					R/W, bit is cleared, must be reset by MCU */
 #define	EFLG_RX0OVR		((uint8_t)(6))
  

 /** @brief 		TXBO
 *	 @details 		Bus-off Error Flag bit
 *   @attention		Bit set when TEC reaches 255
 *					Read-only!, reset after successful bus recovery sequence */
 #define	EFLG_TXBO		((uint8_t)(5))
 

 /** @brief 		TXEP
 *	 @details 		Transmit Error-Passive Flag bit
 *   @attention		Set when TEC is equal to or greater than 128
 *					Read-only! Reset when TEC is less than 128 */
 #define	EFLG_TXEP		((uint8_t)(4))
 

 /** @brief 		RXEP
 *	 @details 		Receive Error-Passive Flag bit
 *   @attention		Set when REC is equal to or greater than 128
 *					Read-only! Reset when REC is less than 128 */
 #define	EFLG_RXEP		((uint8_t)(3))
  

 /** @brief 		TXWAR
 *	 @details 		Transmit Error Warning Flag bit
 *   @attention		Set when TEC is equal to or greater than 96
 *					Read-only! Reset when REC is less than 96 */
 #define	EFLG_TXWAR		((uint8_t)(2))
 

 /** @brief 		RXWAR
 *	 @details 		Receive Error Warning Flag bit
 *   @attention		Set when REC is equal to or greater than 96
 *					Read-only! Reset when REC is less than 96 */
 #define	EFLG_RXWAR		((uint8_t)(1))
 

 /** @brief 		EWARN
 *	 @details 		Error Warning Flag bit
 *   @attention		Set when TEC or REC is equal to or greater than 96 (TXWAR or RXWAR = 1)
 *					Read-only! Reset when both REC and TEC are less than 96 */
 #define	EFLG_EWARN		((uint8_t)(0))
 

 /**
 * @}
 */ 
 /* ================================= */ 
 
 
 /* Macro defines for CANINTE ================================= */ 
 /** @defgroup MCP2515_INTERRUPT_HANDLING
 * @{
 * @brief 	Macro defines for CANINTE - Can Interrupt Enable (documentation p. 50)
 * @details Address: 2Bh
 * @author 	AZ
 */
 
 /** @brief 		MERRE
 *	 @details 		Message Error Interrupt Enable bit
 *   				1 - Interrupt on error during message reception or transmission
 *					0 - Disabled
 *	 @attention		R/W */
 #define	CANINTE_MERRE	((uint8_t)(7))
 

 /** @brief 		WAKIE
 *	 @details 		WakeUp Interrupt Enable bit
 *  				1 - Interrupt on CAN bus activity
 *					0 - Disabled
 *	 @attention		R/W */
 #define	CANINTE_WAKIE	((uint8_t)(6))
  

 /** @brief 		ERRIE
 *	 @details 		Error Interrupt Enable bit (multiple sources in EFLG register)
 *   				1 - Interrupt on EFLG error condition change
 *					0 - Disabled
 *	 @attention		R/W */
 #define	CANINTE_ERRIE	((uint8_t)(5))
 

 /** @brief 		TX2IE
 *	 @details 		Transmit Buffer 2 Empty Interrupt Enable bit
 *   				1 - Interrupt on TXB2 becoming empty
 *					0 - Disabled
 *	 @attention		R/W */
 #define	CANINTE_TX2IE	((uint8_t)(4))
 

 /** @brief 		TX1IE
 *	 @details 		Transmit Buffer 1 Empty Interrupt Enable bit
 *   				1 - Interrupt on TXB1 becoming empty
 *					0 - Disabled
 *	 @attention		R/W */
 #define	CANINTE_TX1IE	((uint8_t)(3))
  

 /** @brief 		TX0IE
 *	 @details 		Transmit Buffer 0 Empty Interrupt Enable bit
 *  				1 - Interrupt on TXB0 becoming empty
 *					0 - Disabled
 *	 @attention		R/W */
 #define	CANINTE_TX0IE	((uint8_t)(2))
 

 /** @brief 		RX1IE
 *	 @details 		Receive Buffer 1 Full Interrupt Enable bit
 *   				1 - Interrupt when message received in RXB1
 *					0 - Disabled
 *	 @attention		R/W */
 #define	CANINTE_RX1IE	((uint8_t)(1))
 

 /** @brief 		RX0IE
 *	 @details 		Receive Buffer 0 Full Interrupt Enable bit
 *   				1 - Interrupt when message received in RXB0
 *					0 - Disabled
 *	 @attention		R/W */
 #define	CANINTE_RX0IE	((uint8_t)(0))
 

 /**
 * @}
 */ 
 /* ================================= */  
 


 /* Macro defines for CANINTF ================================= */ 
 /** @ingroup MCP2515_INTERRUPT_HANDLING
 * @{
 * @brief 	Macro defines for CANINTF - Can Interrupt Flag (documentation p. 51)
 * @details Address: 2Ch
 * @author 	AZ
 */
 
 /** @brief 		MERRF
 *	 @details 		Message Error Interrupt Flag bit
 *   				1 - Interrupt pending (must be cleared by MCU to reset interrupt conditions)
 *					0 - No interrupt pending
 *	 @attention		R/W */
 #define	CANINTF_FLAG_MERRF	((uint8_t)(7))
 

 /** @brief 		WAKIE
 *	 @details 		WakeUp Interrupt Flag bit
 *   				1 - Interrupt pending (must be cleared by MCU to reset interrupt conditions)
 *					0 - No interrupt pending
 *	 @attention		R/W */
 #define	CANINTF_FLAG_WAKIF	((uint8_t)(6))
  

 /** @brief 		ERRIF
 *	 @details 		Error Interrupt Flag bit (multiple sources in EFLG register)
 *   				1 - Interrupt pending (must be cleared by MCU to reset interrupt conditions)
 *					0 - No interrupt pending
 *	 @attention		R/W */
 #define	CANINTF_FLAG_ERRIF	((uint8_t)(5))
 

 /** @brief 		TX2IF
 *	 @details 		Transmit Buffer 2 Empty Interrupt Flag bit
 *   				1 - Interrupt pending (must be cleared by MCU to reset interrupt conditions)
 *					0 - No interrupt pending
 *	 @attention		R/W */
 #define	CANINTF_FLAG_TX2IF	((uint8_t)(4))
 

 /** @brief 		TX1IF
 *	 @details 		Transmit Buffer 1 Empty Interrupt Flag bit
 *   				1 - Interrupt pending (must be cleared by MCU to reset interrupt conditions)
 *					0 - No interrupt pending
 *	 @attention		R/W */
 #define	CANINTF_FLAG_TX1IF		((uint8_t)(3))
  

 /** @brief 		TX0IF
 *	 @details 		Transmit Buffer 0 Empty Interrupt Flag bit
 *   				1 - Interrupt pending (must be cleared by MCU to reset interrupt conditions)
 *					0 - No interrupt pending
 *	 @attention		R/W */
 #define	CANINTF_FLAG_TX0IF		((uint8_t)(2))
 

 /** @brief 		RX1IF
 *	 @details 		Receive Buffer 1 Full Interrupt Flag bit
 *   				1 - Interrupt pending (must be cleared by MCU to reset interrupt conditions)
 *					0 - No interrupt pending
 *	 @attention		R/W */
 #define	CANINTF_FLAG_RX1IF		((uint8_t)(1))
 

 /** @brief 		RX0IF
 *	 @details 		Receive Buffer 0 Full Interrupt Flag bit
 *   				1 - Interrupt pending (must be cleared by MCU to reset interrupt conditions)
 *					0 - No interrupt pending
 *	 @attention		R/W */
 #define	CANINTF_FLAG_RX0IF		((uint8_t)(0))
 
 /**
 * @}
 */ 
 /* ================================= */
 
 
 
 
 
 /* Macro defines for CANCTRL ================================= */ 
 /** @defgroup MCP2515_CONTROL
 * @{
 * @brief 	Macro defines for CANCTRL - Can Control Register(documentation p. 58)
 * @details Address: XFh
 * @author 	AZ
 */
 
 /** @brief 		REQOP MASK
 *	 @details 		Request Operation Mode bits <2:0>
 *   				000 = Set Normal Operation mode 
 *					001 = Set Sleep mode 
 *					010 = Set Loopback mode 
 *					011 = Listen-only mode 
 *					100 = Configuration mode
 *	@attention		On-power REQOP = b'111', All other values for REQOP bits are invalid & should not be used */
 #define	CANCTRL_REQOP_MASK				((uint8_t)( (1<<7)|(1<<6)|(1<<5) ))


 /** @brief 		REQOP_SHIFT
 *	 @details 		Request Operation Mode bits set based on CONTROL_REQOP enum */
 #define	CANCTRL_REQOP_SHIFT				((uint8_t)(5))
 
 
 /** @brief 		ABAT
 *	 @details 		Abort All Pending Transmissions bit
 * 			  		1 - Request abort of all pending transmit buffers
 *					0 - Terminate request to abort transmissions */
 #define	CANCTRL_ABAT					((uint8_t)(4))


 /** @brief 		OSM
 *	 @details 		One Shot Mode bit
 *   				1 - Enabled. Message will only attempt to transmit one time
 *					0 - Disabled. Message will reattempt transmission if required  */
 #define	CANCTRL_OSM						((uint8_t)(3))
 

 /** @brief 		CLKEN
 *	 @details 		CLKOUT Pin Enable bit
 *   				1 - Enabled
 *					0 - Disabled */
 #define	CANCTRL_CLKEN					((uint8_t)(2))
  
 
 /** @brief 		CLKPRE
 *	 @details 		CLKOUT Pin Prescaler bits <1:0>
 *   				00 - FCLKOUT = System Clock/1
 *					01 - FCLKOUT = System Clock/2
 *					10 - FCLKOUT = System Clock/4
 *					11 - FCLKOUT = System Clock/8 */
 #define	CANCTRL_CLKPRE_MASK					((uint8_t)( (1<<1)|(1<<0) ))
 
 
 
 /* Enum: MCP2515 - Operation Mode */
 /** @enum		CONTROL_REQOP
 *	 @brief		Request Operation Mode bits <2:0>
 *	 @attention On-power REQOP = b'111', All other values for REQOP bits are invalid & should not be used
 */
 typedef enum {
	CANCTRL_REQOP_NORMAL = 0,		/**< Set Normal Operation mode */
	CANCTRL_REQOP_SLEEP,			/**< Set Sleep mode */
	CANCTRL_REQOP_LOOPBACK,			/**< Set Loopback mode */
	CANCTRL_REQOP_LISTEN_ONLY,		/**< Set Listen-only mode */
	CANCTRL_REQOP_CONFIGURATION		/**< Set Configuration mode */
 } CONTROL_REQOP;
 
 
 
 /* Macro defines for CANSTAT ================================= */ 
 /** @defgroup MCP2515_STATUS
 * @{
 * @brief 	Macro defines for CANSTAT - Can Status Register(documentation p. 59)
 * @details Address: XEh
 * @author 	AZ
 */
 
 /** @brief 		OPMOD
 *	 @details 		Operation Mode bits <2:0>
 *   				000 = Device is in the Normal operation mode 
 *					001 = Device is in Sleep mode 
 *					010 = Device is in Loopback mode 
 *					011 = Device is in Listen-only mode 
 *					100 = Device is in Configuration mode
 *	@attention		Read-only! */
 #define	CANSTAT_OPMOD_MASK				((uint8_t)( (1<<7)|(1<<6)|(1<<5) ))
 
 
 /** @brief 		ICOD
 *	 @details 		Interrupt Flag Code bits <2:0>
 *   				000 = No interrupt
 *					001 = Error interrupt
 *					010 = Wake-up interrupt
 *					011 = TXB0 Interrupt
 *					100 = TXB1 Interrupt
 *					101 = TXB2 Interrupt
 *					110 = RXB0 Interrupt
 *					111 = RXB1 Interrupt
 *	@attention		Read-only! */
 #define	CANSTAT_ICOD_MASK			((uint8_t)( (1<<3)|(1<<2)|(1<<1) ))
 
 
 /* Enum: MCP2515 - OPMOD */
 /** @enum		CANSTAT_OPMODE_ENUM 
 *	 @brief		Operation mode
 */
 typedef enum {
	CANSTAT_OPMOD_NORMAL = 0,		/**< Normal Operation mode */
	CANSTAT_OPMOD_SLEEP,			/**< Sleep mode */
	CANSTAT_OPMOD_LOOPBACK,			/**< Loopback mode */
	CANSTAT_OPMOD_LISTEN_ONLY,		/**< Listen-only mode */
	CANSTAT_OPMOD_CONFIGURATION		/**< Configuration mode */
 } STATUS_OPMOD;
 

 /**
 * @}
 */ 
 /* ================================= */
 
 
 
 

 /* Register Addresses ================================= */ 
 /** @defgroup MCP2515_REGISTER_ADDRESSES
 * @{
 * @brief 	Register addresses for MCP2515
 * @author 	AZ
 */
 
 /** @brief 		TXB0CTRL
 *	 @details 		Transmit Buffer 0 Control Register
 *   @attention		Some registers read-only! */
 #define	TXB0CTRL		((uint8_t)(0x30))
 

 /** @brief 		TXB1CTRL
 *	 @details 		Transmit Buffer 1 Control Register
 *   @attention		Some registers read-only! */
 #define	TXB1CTRL		((uint8_t)(0x40))
 

 /** @brief 		TXB2CTRL
 *	 @details 		Transmit Buffer 2 Control Register
 *   @attention		Some registers read-only! */
 #define	TXB2CTRL		((uint8_t)(0x50))
 

 /** @brief 		TXRTSCTRL
 *	 @details 		TXnRTS Pin Control and Status Register
 *   @attention		Some registers read-only! */
 #define	TXRTSCTRL		((uint8_t)(0x0D))
 

 /** @brief 		TXB0SIDH
 *	 @details 		Transmit Buffer 0 Standard Identifier High */
 #define	TXB0SIDH		((uint8_t)(0x31))
 

 /** @brief 		TXB1SIDH
 *	 @details 		Transmit Buffer 1 Standard Identifier High */
 #define	TXB1SIDH		((uint8_t)(0x41))
 

 /** @brief 		TXB2SIDH
 *	 @details 		Transmit Buffer 2 Standard Identifier High */
 #define	TXB2SIDH		((uint8_t)(0x51))
 
 
 /** @brief 		TXB0SIDL
 *	 @details 		Transmit Buffer 0 Standard Identifier Low */
 #define	TXB0SIDL		((uint8_t)(0x32))
 

 /** @brief 		TXB1SIDL
 *	 @details 		Transmit Buffer 1 Standard Identifier Low */
 #define	TXB1SIDL		((uint8_t)(0x42))
 

 /** @brief 		TXB2SIDL
 *	 @details 		Transmit Buffer 2 Standard Identifier Low */
 #define	TXB2SIDL		((uint8_t)(0x52))
 
 
 /** @brief 		TXB0EID8
 *	 @details 		Transmit Buffer 0 Extended Identifier High */
 #define	TXB0EID8		((uint8_t)(0x33))
 

 /** @brief 		TXB1EID8
 *	 @details 		Transmit Buffer 1 Extended Identifier High */
 #define	TXB1EID8		((uint8_t)(0x43))
 

 /** @brief 		TXB2EID8
 *	 @details 		Transmit Buffer 2 Extended Identifier High */
 #define	TXB2EID8		((uint8_t)(0x53))
 

 /** @brief 		TXB0EID0
 *	 @details 		Transmit Buffer 0 Extended Identifier Low */
 #define	TXB0EID0		((uint8_t)(0x34))
 

 /** @brief 		TXB1EID0
 *	 @details 		Transmit Buffer 1 Extended Identifier Low */
 #define	TXB1EID0		((uint8_t)(0x44))
 

 /** @brief 		TXB2EID0
 *	 @details 		Transmit Buffer 2 Extended Identifier Low */
 #define	TXB2EID0		((uint8_t)(0x54))
 

 /** @brief 		TXB0DLC
 *	 @details 		Transmit Buffer 0 Data Length Code */
 #define	TXB0DLC			((uint8_t)(0x35))
 

 /** @brief 		TXB1DLC
 *	 @details 		Transmit Buffer 1 Data Length Code */
 #define	TXB1DLC			((uint8_t)(0x45))
 
 /** @brief 		TXB2DLC
 *	 @details 		Transmit Buffer 2 Data Length Code */
 #define	TXB2DLC			((uint8_t)(0x55))
 
 
 
 /** @brief 		TXB0Dx
 *	 @details 		Transmit Buffer 0 Data Byte 0-7 */
 #define	TXB0D0			((uint8_t)(0x36))

 
  /** @brief 		TXB1Dx
 *	 @details 		Transmit Buffer 1 Data Byte 0-7 */
 #define	TXB1D0			((uint8_t)(0x46))

 
 /** @brief 		TXB2Dx
 *	 @details 		Transmit Buffer 2 Data Byte 0-7 */
 #define	TXB2D0			((uint8_t)(0x56))

 
 
 //* RECEIVE buffer addresses
 /** @brief 		RXB0CTRL
 *	 @details 		Receive Buffer 0 Control
 *	 @attention		Some bits read-only! */
 #define	RXB0CTRL			((uint8_t)(0x60))
 

 /** @brief 		RXB1CTRL
 *	 @details 		Receive Buffer 1 Control
 *	 @attention		Some bits read-only! */
 #define	RXB1CTRL			((uint8_t)(0x70))
 

 /** @brief 		BFPCTRL
 *	 @details 		RXnBF Pin Control and Status */
 #define	BFPCTRL			((uint8_t)(0x0C))
 

 /** @brief 		RXBnSIDH
 *	 @details 		Receive Buffer n Standard Identifier High */
 #define	RXB0SIDH			((uint8_t)(0x61))
 #define	RXB1SIDH			((uint8_t)(0x71))
 

 /** @brief 		RXBnSIDL
 *	 @details 		Receive Buffer n Standard Identifier Low */
 #define	RXB0SIDL			((uint8_t)(0x62))
 #define	RXB1SIDL			((uint8_t)(0x72))
 

 /** @brief 		RXBnEID8
 *	 @details 		Receive Buffer n Extended Identifier High */
 #define	RXB0EID8			((uint8_t)(0x63))
 #define	RXB1EID8			((uint8_t)(0x73))
 

 /** @brief 		RXBnEID8
 *	 @details 		Receive Buffer n Extended Identifier Low */
 #define	RXB0EID0			((uint8_t)(0x64))
 #define	RXB1EID0			((uint8_t)(0x74))
 

 /** @brief 		RXBnDLC
 *	 @details 		Receive Buffer n Data Length Code 
 *	 @attention		Bits read-only! bits are unknown */
 #define	RXB0DLC				((uint8_t)(0x65))
 #define	RXB1DLC				((uint8_t)(0x75))
 

 /** @brief 		RXB0Dx
 *	 @details 		Receive Buffer 0 Data Length Code 
 *	 @attention		Bits read-only! bits are unknown */
 #define	RXB0D0				((uint8_t)(0x66))

 
 /** @brief 		RXB1Dx
 *	 @details 		Receive Buffer 1 Data Length Code 
 *	 @attention		Bits read-only! bits are unknown */
 #define	RXB1D0				((uint8_t)(0x76))
 #define	RXB1D1				((uint8_t)(0x77))
 #define	RXB1D2				((uint8_t)(0x78))
 #define	RXB1D3				((uint8_t)(0x79))
 #define	RXB1D4				((uint8_t)(0x7A))
 #define	RXB1D5				((uint8_t)(0x7B))
 #define	RXB1D6				((uint8_t)(0x7C))
 #define	RXB1D7				((uint8_t)(0x7D))
 

 //* filters
 /** @brief 		RXFnSIDH
 *	 @details 		Filter n Standard Identifier High */
 #define	RXF0SIDH			((uint8_t)(0x00))
 #define	RXF1SIDH			((uint8_t)(0x04))
 #define	RXF2SIDH			((uint8_t)(0x08))
 #define	RXF3SIDH			((uint8_t)(0x10))
 #define	RXF4SIDH			((uint8_t)(0x14))
 #define	RXF5SIDH			((uint8_t)(0x18))
 

 /** @brief 		RXFnSIDL
 *	 @details 		Filter n Standard Identifier Low */
 #define	RXF0SIDL			((uint8_t)(0x01))
 #define	RXF1SIDL			((uint8_t)(0x05))
 #define	RXF2SIDL			((uint8_t)(0x09))
 #define	RXF3SIDL			((uint8_t)(0x11))
 #define	RXF4SIDL			((uint8_t)(0x15))
 #define	RXF5SIDL			((uint8_t)(0x19))
 

 /** @brief 		RXFnEID8
 *	 @details 		Filter n Extended Identifier High */
 #define	RXF0EID8			((uint8_t)(0x02))
 #define	RXF1EID8			((uint8_t)(0x06))
 #define	RXF2EID8			((uint8_t)(0x0A))
 #define	RXF3EID8			((uint8_t)(0x12))
 #define	RXF4EID8			((uint8_t)(0x16))
 #define	RXF5EID8			((uint8_t)(0x1A))
 
 /** @brief 		RXFnEID0
 *	 @details 		Filter n Extended Identifier Low */
 #define	RXF0EID0			((uint8_t)(0x03))
 #define	RXF1EID0			((uint8_t)(0x07))
 #define	RXF2EID0			((uint8_t)(0x0B))
 #define	RXF3EID0			((uint8_t)(0x13))
 #define	RXF4EID0			((uint8_t)(0x17))
 #define	RXF5EID0			((uint8_t)(0x1B))
 


 //* masks
 /** @brief 		RXMnSIDH
 *	 @details 		Mask n Standard Identifier High */
 #define	RXM0SIDH			((uint8_t)(0x20))
 #define	RXM1SIDH			((uint8_t)(0x24))


 /** @brief 		RXMnSIDL
 *	 @details 		Mask n Standard Identifier Low */
 #define	RXM0SIDL			((uint8_t)(0x21))
 #define	RXM1SIDL			((uint8_t)(0x25)) 
 

 /** @brief 		RXMnEID8
 *	 @details 		Mask n Extended Identifier High */
 #define	RXM0EID8			((uint8_t)(0x22))
 #define	RXM1EID8			((uint8_t)(0x26))
 

 /** @brief 		RXMnEID0
 *	 @details 		Mask n Extended Identifier Low */
 #define	RXM0EID0			((uint8_t)(0x23))
 #define	RXM1EID0			((uint8_t)(0x27))
 
 
 
 
 //* BIT TIMING
 /** @brief 		CNF
 *	 @details 		Configuration registers */
 #define	CNF1				((uint8_t)(0x2A))
 #define	CNF2				((uint8_t)(0x29))
 #define	CNF3				((uint8_t)(0x28))
 
 
 

 //* ERROR and INTERRUPT handling
 /** @brief 		TEC
 *	 @details 		Transmit Error Counter 
 *   @attention		Read-Only! */
 #define	TEC		((uint8_t)(0x1C))
 

 /** @brief 		REC
 *	 @details 		Receiver Error Counter
 * 	 @attention		Read-Only!*/
 #define	REC		((uint8_t)(0x1D))
 

 /** @brief 		EFLG
 *	 @details 		Error Flag
 * 	 @attention		R/W */
 #define	EFLG	((uint8_t)(0x2D))
 

 /** @brief 		CANINTE
 *	 @details 		Can Interrupt Enable
 * 	 @attention		R/W */
 #define	CANINTE	((uint8_t)(0x2B))
 

 /** @brief 		CANINTF
 *	 @details 		Can Interrupt Flag
 * 	 @attention		R/W */
 #define	CANINTF	((uint8_t)(0x2C))
 

 /** @brief 		CANCTRL
 *	 @details 		Can Control Register
 * 	 @attention		R/W; I AM NOTE SURE ABOUT ADDRESS (take a look at MCP2515 documentation */
 #define	CANCTRL	((uint8_t)(0x0F))
 

 /** @brief 		CANSTAT
 *	 @details 		Can Status Register
 * 	 @attention		Read-only!; I AM NOTE SURE ABOUT ADDRESS (take a look at MCP2515 documentation */
 #define	CANSTAT	((uint8_t)(0xE))
 
 
 
 /**
 * @}
 */
 
 /* ================================= */
 
 
 
 /* Control Addresses ================================= */ 
 /** @defgroup MCP2515_CONTROL_ADDRESSES
 * @{
 * @brief 	Control Addresses for MCP2515
 * @author 	AZ
 */
 #define	MCP_RESET				0xC0	
 #define	MCP_READ_CMD			0x03
 #define 	MCP_WRITE_CMD			0x02

 #define 	MCP_RECEIVE_RXB0SIDH	0x90
 #define 	MCP_RECEIVE_RXB0D0		0x91
 #define 	MCP_RECEIVE_RXB1SIDH	0x92
 #define 	MCP_RECEIVE_RXB1D0		0x93


 #define 	MCP_LOAD_TXB0SIDH		0x40
 #define 	MCP_LOAD_TXB0D0			0x41
 #define 	MCP_LOAD_TXB1SIDH		0x42
 #define 	MCP_LOAD_TXB1D0			0x43
 #define 	MCP_LOAD_TXB2SIDH		0x44
 #define 	MCP_LOAD_TXB2D0			0x45

 #define 	MCP_READ_STATUS			0xA0
 #define 	MCP_RX_STATUS			0xB0
 #define 	MPC_BIT_MODIFY			0x05
 
 /**
 * @}
 */
 
 /** 
 * Description for receiving and sending function - registers number
 */
 #define	REG_OFFSET				0x10
 #define	REC_REG_0				0
 #define	REC_REG_1				1
 #define	SEND_REG_0				0
 #define	SEND_REG_1				1
 #define	SEND_REG_2				2


#endif
