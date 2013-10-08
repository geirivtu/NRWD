/*
 * This file is in public domain.
 * The source code herein is used for testing,
 * and should provide an example of a sane configuration.
 */

/**
 * @file		config.h
 * @brief		Tweakabe constants and associated values.
 *				This file common both for HAL and HLL.
 *
 * @author		Andreas Nordal   ( NTNU )
 *				Andrzej Zamojski ( NTNU )
 * @date		spring 2012
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/*
 * This file contains all constants named CONFIG_*.
 *
 * Prefix naming convention:
 * A prefix of CONFIG_ suggests that it is something
 * the application designer probably wants to tweak.
 * A prefix of BUS_ indicates that it is something going on on the CAN bus.
 */

 
 /*!
 * \def	CONFIG_BUS_MODE
 * Determines type of node within the system
 * See PDCP documentation: Message Mode Field
 */
#define BUS_ARBITRATOR  		1
#define BUS_DEVICE      		0
#ifndef CONFIG_BUS_MODE //let Makefile override
#	define CONFIG_BUS_MODE 		BUS_DEVICE
#endif

/**
 * Number of CAN messages reserved in the memory pool
 * of the High Level Layer, shared by all sockets.
 */
#define CONFIG_NUM_CANMSG 8

/**
 * If defined, enables datastructures of academic interest instead of array.
 * Currently affects only trie.
 */
#define CONFIG_USE_MALLOC

/**
 * When trie datastructure is enabled,
 * the height of the tree used for indexing node ids
 * in arbitrator is 8 divided by this number.
 */
#define CONFIG_TRIE_BITS_PER_NODE 4

/**
 * If nonzero, postpone socket callbacks when in
 * an interrupt that interrupts the same running callback.
 */
#define CONFIG_SERIALIZE_CALLBACKS 1

/**
 * Used in the Bind request.
 */
#define CONFIG_VENDOR_ID     1
#define CONFIG_PRODUCT_ID    2
#define CONFIG_SERIAL_NUMBER 3

#ifndef F_CPU
#	define F_CPU 16000000
#endif








/* ======================================================== */
/*							HAL								*/
/* ======================================================== */

/**
 * Default nodes ID
 */
 
/*!
 *	\def	CONFIG_DEVICE_DEF_ID
 *	Device default ID 
 */
#define	CONFIG_DEVICE_DEF_ID		0xFF

/*!
 *	\def	CONFIG_ARB_DEF_ID
 *	Arbitrator default ID 
 */
#define	CONFIG_ARB_DEF_ID			0x01





/**
 * SPI
 * SPI port specification for MCP2515
 */
 
 /*!
 *	\def	HW_CS_MCP2515_PORT
 *	Chip select  - PORT 
 *
 *	\def	HW_CS_MCP2515
 *	Chip select  - pin determination 
 *
 *	\def	HW_CS_MCP2515_DDR
 *	Chip select  - DDR (port direction) 
 */
#define		HW_CS_MCP2515_PORT			DATA_PORT_B
#define 	HW_CS_MCP2515				B0
#define 	HW_CS_MCP2515_DDR			DATA_DIR_REG_B
 
 
  /*!
 *	\def	HW_MISO_MCP2515
 *	SPI MISO - pin determination
 *
 *	\def	HW_MOSI_MCP2515
 *	SPI MOSI - pin determination
 *
 *	\def	HW_MISO_MCP2515_DDR
 *	SPI MISO - DDR ( port direction )
 *
 *	\def	HW_MISO_MCP2515_PIN
 *	SPI MISO - PIN value
 *
 *	\def	HW_MOSI_MCP2515_DDR
 *	SPI MOSI - DDR ( port direction )
 *
 *	\def	HW_MOSI_MCP2515_PORT
 *	SPI MOSI - PORT ( output value )
 *
 *	\def	HW_SCK_MCP2515_DDR
 *	SPI SCK - DDR (port direction)
 *
 *	\def	HW_SCK_MCP2515
 *	SPI CLK - pin determination
 */
#define		HW_MISO_MCP2515				B3
#define		HW_MOSI_MCP2515				B2
#define		HW_MISO_MCP2515_DDR			DATA_DIR_REG_B
#define		HW_MISO_MCP2515_PIN			PORT_INPUT_PIN_B
#define		HW_MOSI_MCP2515_DDR			DATA_DIR_REG_B
#define		HW_MOSI_MCP2515_PORT		DATA_PORT_B
#define		HW_SCK_MCP2515_DDR			DATA_DIR_REG_B
#define		HW_SCK_MCP2515				B1
 
 

 
 
/**
 * EXTERNAL interrupt
 * External interrupt port specification
 */
 /*!
 *	\def	HW_MCP_EXT_INT
 *	External interrupt  - number of interrupt
 *
 *	\def	HW_MCP_EXT_INT_DDR
 *	External interrupt - port direction
 *
 *	\def	HW_MCP_EXT_INT_PORT
 *	External interrupt  - port number
 *
 *	\def	CONFIG_MCP_INT
 *	External interrupt handler name
 */
 
#define		HW_MCP_EXT_INT				0
#define 	HW_MCP_EXT_INT_DDR			DDRD
#define 	HW_MCP_EXT_INT_PORT			PORTD
#define		CONFIG_MCP_INT				INT0_VECTOR
 
 
 
 
/**
 * EXTERNAL interrupt as SOFTWARE interrupt
 * Software int basing on external interrupt of uC - be careful with number of interrupt ... 
 * ... to not destroy communication with CAN controller
 */

 /*!
 *	\def	HW_SOFT_EXT_INT_DDR
 *	Software interrupt - port direction
 *
 *	\def	HW_SOFT_EXT_INT_PORT
 *	Software interrupt - port value
 *
 *	\def	HW_SOFT_EXT_INT_1
 *	Software interrupt 1 - port number
 *
 *	\def	HW_SOFT_EXT_INT_2
 *	Software interrupt 2 - port number 
 */
#define		HW_SOFT_EXT_INT_DDR		DDRE	
#define		HW_SOFT_EXT_INT_PORT	PORTE
#define		HW_SOFT_EXT_INT_1		PE4
#define		HW_SOFT_EXT_INT_2		PE5


/*!
 *	\def	CONFIG_INT_SENDING
 *	Determinates vector of interrupt routine responsible for message sending
 *
 *	\def	CONFIG_INT_RECEIVING
 *	Determinates number of interrupt routine responsible for message receiving
 *
 *	\def	CONFIG_INT_SEND_NUM
 *	Determinates number of interrupt routine responsible for message sending
 *
 *	\def	CONFIG_INT_REC_NUM
 *	Determinates number of interrupt routine responsible for message receiving
 *
 *	\def 	TRIGGER_RECEIVING
 *	It determines port responsible for triggering receiving mechanism 
 *
 *	\def 	TRIGGER_SENDING
 *	It determines port responsible for triggering sending mechanism 
 *
 */
#define		CONFIG_INT_SENDING			INT4_VECTOR
#define		CONFIG_INT_RECEIVING		INT5_VECTOR
#define		CONFIG_INT_SEND_NUM			HW_SOFT_EXT_INT_1
#define		CONFIG_INT_REC_NUM			HW_SOFT_EXT_INT_2
#define		TRIGGER_RECEIVING			HW_SOFT_EXT_INT_2
#define		TRIGGER_SENDING				HW_SOFT_EXT_INT_1
 
 
 
 
 
/**
 * WATCHDOG
 * Properties
 */
 
/*!
 *	\def	CONFIG_WDT_MODE
 *	Watchdog timer ON/OFF
 */
 #define 	WDT_OFF		0
 #define	WDT_ON		1
 #define	CONFIG_WDT_MODE	WDT_OFF
 
 
 
 
 
 
/**
 * CONFIGURATION modes
 * External interrupt port specification
 */

/*!
 *	\def	CONFIG_DEBUG_UART_INFO
 *	Configuration mode in which some informations are sent through UART
 */
#define	CONFIG_DEBUG_UART_INFO		1

/*!
 *	\def	CONFIG_DEBUG_TEST_HLL
 *	Configuration mode in which HLL is included into testing
 */
#define	CONFIG_DEBUG_TEST_HLL		1


/*!
 *	\def	CONFIG_TESTING_HAL
 *	Configuration mode in which only HAL is tested - modified main function needed
 */
#define CONFIG_TESTING_HAL			0


/*!
 *	\def	MSG_AMOUNT_TEST
 *	Number of messages for HAL testing
 */
#define MSG_AMOUNT_TEST 	10000


/*!
 *	\def	DATA_TO_SEND_1
 *	Data to send (only for testing)
 */
#define	DATA_TO_SEND_1	0x5


/*!
 *	\def	CONFIG_DEBUG_LED_TOGGLING
 *	Configuration mode in which some toggling diode while msg receiving @n
 *	and sending can be started.
 */
#define	CONFIG_DEBUG_LED_TOGGLING	0
#define	HW_PORT_LED					PORTF
#define	HW_DDR_LED					DDRF
#define	HW_PORT_LED0				PF0
#define	HW_PORT_LED1				PF1
#define	HW_PORT_LED2				PF2






/* UART - debugging */
#if ( CONFIG_DEBUG_UART_INFO ) 
	#define 	RS_BAUD 	9600UL
	#define 	RS_UBRR 	((F_CPU/16/RS_BAUD) - 1)
#endif 


#endif
