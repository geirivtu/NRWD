 /***********************************************************************//**
 * @file		uCmaskFile.h
 * @brief		Contains all needed macros masking port, registers etc. for masking architecture differences. @n
 *
 * @details		This file consists of macros of registers and addresses of used microcontroller family. @n
 *				Depending on microcontroller family software aplication designer is asked to adjust @n
 *				preprocessor directives #define. Before that designer HAS TO check whether proper header file @n
 *				with register addresses and all needed other stuff was included (look at section Includes). @n
 *				This file should be included whether by programming application or by a designer by hand. @n
 *				Such a solution increases portability of implemented libraries for PDCP, because of need @n
 *				to change data only inside this file and whole interface should work properly.
 *				
 *				This file was filled with macros for AT90USB1287 (AVR platform)! @n
 *
 *				In case of processor change aplication designer has to be aware of the need of refreshing data @n
 *				in this file. It can be associated with some more serious changes in this code below. @n
 *				@n
 *				<b>APPLICATION DESIGNER IS STRONGLY RECOMMENDED NOT TO CHANGE ANYTHING ELSE @n
 *				INSIDE OF OTHER PDCP FILES </b>
 * 
 * @author		Andrzej Zamojski @n NTNU in Trondheim (NORWAY) @n TU of Lodz (POLAND)				
 * @date		1 VI 2012
 *
 **************************************************************************/


 #ifndef UC_MASK_FILE_H_
 #define UC_MASK_FILE_H_
 
 

 /* INCLUDE =========================================== */
 /** @attention	You should include files with microcontroller register addresses or libraries, which you are going to use 
				This file can be delivered by programming application (e.g. AVR Studio)
 */
	
	//* place for microcontroller header file
	
	
	//* libraries from AVR Lib
	/** @name IO PORT AVR lib	*/
	#include <avr/io.h>
	
	/** @name INTERRUPT AVR lib	*/
	#include <avr/interrupt.h>

	/** @name Configuration file	*/
	#include "config.h"

 /* END OF INCLUDE =========================================== */


 /** Decide whether use or not use AVR library*/
  
 #define	USE_AT90CAN128		1
 //#define 	USE_AT90USB1287		1
 
#ifdef USE_AT90USB1287
	#define	MICROCONTROLLER		USE_AT90USB1287 
#endif //USE_AT90USB1287

#ifdef USE_AT90CAN128
  #define	MICROCONTROLLER		USE_AT90CAN128 
#endif //USE_AT90CAN128




 #if ( MICROCONTROLLER == USE_AT90USB1287 )
 
 #elif ( MICROCONTROLLER == USE_AT90CAN128 )
 
 #endif //MICROCONTROLLER==
 
 
 /* I/O =========================================== */
 /** @defgroup 	I_O_MACROS
 *	 @code		<uCmaskFile.h>
 * @{
 */
 
 
 //* PIN A - port input pin
 #define	PORT_INPUT_PIN_A		PINA
 #define	A7						7
 #define	A6						6
 #define	A5						5
 #define	A4						4
 #define	A3						3
 #define	A2						2
 #define	A1						1
 #define	A0						0

 //* DDRA - port direction
 #define	DATA_DIR_REG_A			DDRA

 
 //* PORTA if OUTPUT PORTreg set value, if INPUT - decide about pull-up resistors
 #define	DATA_PORT_A				PORTA
 
 
 
 //* PINB - port input pin
 #define	PORT_INPUT_PIN_B		PINB
 #define	B7						7
 #define	B6						6
 #define	B5						5
 #define	B4						4
 #define	B3						3
 #define	B2						2
 #define	B1						1
 #define	B0						0

 //* DDRB - port direction
 #define	DATA_DIR_REG_B			DDRB
 
 //* PORTB
 #define	DATA_PORT_B				PORTB

 
 //* PINC - port input pin
 #define	PORT_INPUT_PIN_C		PINC
 #define	C7						7
 #define	C6						6
 #define	C5						5
 #define	C4						4
 #define	C3						3
 #define	C2						2
 #define	C1						1
 #define	C0						0

 //* DDRC - port direction
 #define	DATA_DIR_REG_C			DDRC
 
 //* PORTC if OUTPUT PORTreg set value, if INPUT - decide about pull-up resistors
 #define	DATA_PORT_C				PORTC

 
 
 //* PIND - port input pin
 #define	PORT_INPUT_PIN_D		PIND
 #define	D7						7
 #define	D6						6
 #define	D5						5
 #define	D4						4
 #define	D3						3
 #define	D2						2
 #define	D1						1
 #define	D0						0

 //* DDRD - port direction
 #define	DATA_DIR_REG_D			DDRD
 
 //* PORTD if OUTPUT PORTreg set value, if INPUT - decide about pull-up resistors
 #define	DATA_PORT_D				PORTD
 
 
 #if ( MICROCONTROLLER == USE_AT90USB1287 || MICROCONTROLLER == USE_AT90CAN128 )
 
 //* PINE - port input pin
 #define	PORT_INPUT_PIN_E		PINE
 #define	E7						7
 #define	E6						6
 #define	E5						5
 #define	E4						4
 #define	E3						3
 #define	E2						2
 #define	E1						1
 #define	E0						0

 //* DDRE - port direction
 #define	DATA_DIR_REG_E			DDRE
 
 //* PORTE if OUTPUT PORTreg set value, if INPUT - decide about pull-up resistors
 #define	DATA_PORT_E				PORTE
 
 
 //* PINF - port input pin
 #define	PORT_INPUT_PIN_F		PINF
 #define	F7						7
 #define	F6						6
 #define	F5						5
 #define	F4						4
 #define	F3						3
 #define	F2						2
 #define	F1						1
 #define	F0						0

 //* DDRF - port direction
 #define	DATA_DIR_REG_F			DDRF
 
 //* PORTF if OUTPUT PORTreg set value, if INPUT - decide about pull-up resistors
 
 #endif //( MICROCONTROLLER == USE_AT90USB1287 || MICROCONTROLLER == USE_AT90CAN128 )
 
  #if ( MICROCONTROLLER == USE_AT90CAN128 )
 
 //* PING - port input pin
 #define	PORT_INPUT_PIN_G		PING
 #define	G7						7
 #define	G6						6
 #define	G5						5
 #define	G4						4
 #define	G3						3
 #define	G2						2
 #define	G1						1
 #define	G0						0

 //* DDRF - port direction
 #define	DATA_DIR_REG_G			DDRG
 
 //* PORTF if OUTPUT PORTreg set value, if INPUT - decide about pull-up resistors
 
 #endif //( MICROCONTROLLER == USE_AT90CAN128 )
 
 /**
 * @}
 */
 /* ================================= */
 
 
 /* TIMERS =========================================== */
 /** @defgroup 	TIMER_MACROS
 *	 @code		<uCmaskFile.h>
 * @{
 */
 
  #if ( MICROCONTROLLER == USE_AT90USB1287 )
  
 
  
 /** @name GENERAL_TIMER_COUNTER_CONTROL_REGISTER */
 #define	TIMER_GTCCR		GTCCR
 #define	TIMER_TSM		TSM
 #define	TIMER_PSRASY	TIMER_PSRASY
 #define	TIMER_PSRSYNC	PSRSYNC
 
 
 /** @name TIMER0 */
 #define	TIMER0_TCNT		TCNT0
 #define	TIMER0_TCNTL	TCNT0L
 #define	TIMER0_TCNTH	TCNT0H
 
 #define	TIMER0_TCCR0A	TCCR0A
 #define	TIMER0_TCCR0B	TCCR0B
 #define	TIMER0_COM0A1	COM0A1
 #define	TIMER0_COM0A0	COM0A0
 #define	TIMER0_COM0B1	COM0B1
 #define	TIMER0_COM0B0	COM0B0
 #define	TIMER0_WGM02	WGM02
 #define	TIMER0_WGM01	WGM01
 #define	TIMER0_WGM00	WGM00
 #define	TIMER0_TIFR0	TIFR0
 #define	TIMER0_OCF0B	OCF0B
 #define	TIMER0_OCF0A	OCF0A
 #define	TIMER0_TOV0		TOV0
 #define	TIMER0_FOC0A	FOC0A
 #define	TIMER0_FOC0B	FOC0B
 
 #define	TIMER0_CS02		CS02
 #define	TIMER0_CS01		CS01
 #define	TIMER0_CS00		CS00
 
 #define 	TIMER0_TIMSK0	TIMSK0	
 #define	TIMER0_OCIE0B	OCIE0B
 #define	TIMER0_OCIE0A	OCIE0A
 #define	TIMER0_TOIE0	TOIE0
 #define	TIMER0_TOIE0	TOIE0
 
 #define	TIMER0_OCR0A	OCR0A
 #define	TIMER0_OCR0B	OCR0B
 
 /** @name TIMER1 */
 #define	TIMER1_TCNT		TCNT1
 #define	TIMER1_TCNTL	TCNT1L
 #define	TIMER1_TCNTH	TCNT1H
 #define	TIMER1_OCR1A	OCR1A
 #define	TIMER1_OCR1AL	OCR1AL
 #define	TIMER1_OCR1AH	OCR1AH
 #define	TIMER1_OCR1B	OCR1B
 #define	TIMER1_OCR1BL	OCR1BL
 #define	TIMER1_OCR1BH	OCR1BH 
 #define	TIMER1_OCR1C	OCR1C
 #define	TIMER1_OCR1CL	OCR1CL
 #define	TIMER1_OCR1CH	OCR1CH
 
 
 #define	TIMER1_TIFR1	TIFR1
 #define 	TIMER1_ICF1		ICF1
 #define	TIMER1_OCF1C	OCF1C
 #define	TIMER1_OCF1B	OCF1B
 #define	TIMER1_OCF1A	OCF1A
 #define	TIMER1_TOV1		TOV1
 
 #define	TIMER1_TCCR1A	TCCR1A
 #define	TIMER1_COM1A1	COM1A1
 #define	TIMER1_COM1A0	COM1A0
 #define	TIMER1_COM1B1	COM1B1
 #define	TIMER1_COM1B0	COM1B0
 #define	TIMER1_COM1C1	COM1C1
 #define	TIMER1_COM1C0	COM1C0
 #define	TIMER1_WGM11	WGM11
 #define	TIMER1_WGM10	WGM10
 
 #define	TIMER1_TCCR1B	TCCR1B
 #define	TIMER1_ICNC1	ICNC1
 #define	TIMER1_ICES1	ICES1
 #define	TIMER1_WGM13	WGM13
 #define	TIMER1_WGM12	WGM12
 #define	TIMER1_CS12		CS12
 #define	TIMER1_CS11		CS11
 #define	TIMER1_CS10		CS10
 
 #define	TIMER1_TCCR1C	TCCR1C
 #define	TIMER1_FOC1A	FOC1A
 #define	TIMER1_FOC1B	FOC1B
 #define	TIMER1_FOC1C	FOC1C
 
 
 /** @attention	Be careful with amount of timers */
 #if ( MICROCONTROLLER == USE_AT90USB1287 )
 
 
 /** @name TIMER2 */
 #define 	TIMER2_TCNT		TCNT2
 #define	TIMER2_TCNTL	TCNT2L
 #define	TIMER2_TCNTH	TCNT2H
 #define	TIMER2_OCR2A	OCR2A
 #define	TIMER2_OCR2B	OCR2B
 
 #define	TIMER2_TIFR2	TIFR2
 #define	TIMER2_OCF2B	OCF2B
 #define	TIMER2_OCF2A	OCF2A
 #define	TIMER2_TOV2		TOV2
 
 #define	TIMER2_COM2A1	COM2A1
 #define	TIMER2_COM2A0	COM2A0
 #define	TIMER2_COM2B1	COM2B1
 #define	TIMER2_COM2B0	COM2B0
 #define	TIMER2_WGM21	WGM21
 #define	TIMER2_WGM20	WGM20
 
 #define	TIMER2_FOC2A	FOC2A
 #define	TIMER2_FOC2B	FOC2B
 #define	TIMER2_WGM22	WGM22
 #define	TIMER2_CS22		CS22
 #define	TIMER2_CS21		CS21
 #define	TIMER2_CS20		CS20
 
 
 /** @name TIMER3 */
 #define 	TIMER3_TCNT		TCNT3
 #define	TIMER3_TCNTL	TCNT3L
 #define	TIMER3_TCNTH	TCNT3H
 
 #define	TIMER3_TIFR3	TIFR3
 #define 	TIMER3_ICF3		ICF3
 #define	TIMER3_OCF3C	OCF3C
 #define	TIMER3_OCF3B	OCF3B
 #define	TIMER3_OCF3A	OCF3A
 #define	TIMER3_TOV3		TOV3
 #define	TIMER3_OCR3A	OCF3A
 #define	TIMER3_OCR3AL	OCF3AL
 #define	TIMER3_OCR3AH	OCF3AH
 #define	TIMER3_OCR3B	OCF3B
 #define	TIMER3_OCR3BL	OCF3BL
 #define	TIMER3_OCR3BH	OCF3BH
 #define	TIMER3_OCR3C	OCF3C
 #define	TIMER3_OCR3CL	OCF3CL
 #define	TIMER3_OCR3CH	OCF3CH
 #define	TIMER3_ICR3		ICR3
 #define	TIMER3_ICR3L	ICR3L
 #define	TIMER3_ICR3H	ICR3H
 #define	TIMER3_TCCR3A	TCCR3A
 #define	TIMER3_TCCR3B	TCCR3B
 #define	TIMER3_TCCR3C	TCCR3C

 #define	TIMER3_COM3A1	COM3A1
 #define	TIMER3_COM3A0	COM3A0
 #define	TIMER3_COM3B1	COM3B1
 #define	TIMER3_COM3B0	COM3B0
 #define	TIMER3_COM3C1	COM3C1
 #define	TIMER3_COM3C0	COM3C0
 #define	TIMER3_WGM31	WGM31
 #define	TIMER3_WGM30	WGM30
 
 #define	TIMER3_ICNC3	ICNC3
 #define	TIMER3_ICES3	ICES3
 #define	TIMER3_WGM33	WGM33
 #define	TIMER3_WGM32	WGM32
 #define	TIMER3_CS32		CS32
 #define	TIMER3_CS31		CS31
 #define	TIMER3_CS30		CS30 
 
 #define	TIMER3_FOC3A	FOC3
 #define	TIMER3_FOC3B	FOC3B
 #define	TIMER3_FOC3C	FOC3C
 
 #endif
 
 #elif ( MICROCONTROLLER == USE_AT90CAN128 )
  
  
 #endif //MICROCONTROLLER==

 /**
 * @}
 */
 /* ================================= */
 
 
 /* INTERRUPTS =========================================== */
 /** @defgroup 	INTERRUPTS
 * @{
 */
 
 //* Pin Change Interrupt Flag Register
 /** @name 	EXT_INT_EIFR 	External Interrupt Flag Register */
 #define	EXT_INT_PCIFR	PCIFR
  
 //* External Interrupt Flags
 /** @name 	EXT_INT_EIFR 	External Interrupt Flag Register */
 #define	EXT_INT_EIFR	EIFR
 
 #define	EXT_INTF_7		INTF7
 #define	EXT_INTF_6		INTF6
 #define	EXT_INTF_5		INTF5
 #define	EXT_INTF_4		INTF4
 #define	EXT_INTF_3		INTF3
 #define	EXT_INTF_2		INTF2
 #define	EXT_INTF_1		INTF1
 #define	EXT_INTF_0		INTF0
 
 //* External Interrupt Request	
 /** @name 	EXT_INT_MASK 	External Interrupt Mask Register */
 #define	EXT_INT_EIMSK	EIMSK
 
 #define	EXT_INT_7		INT7
 #define	EXT_INT_6		INT6
 #define	EXT_INT_5		INT5
 #define	EXT_INT_4		INT4
 #define	EXT_INT_3		INT3
 #define	EXT_INT_2		INT2
 #define	EXT_INT_1		INT1
 #define	EXT_INT_0		INT0
 
 /** @name 	INT_PCIFR 		Pin Change Interrupt Flag Register */
 #define	INT_PCIFR		PCIFR
 #define 	INT_PCIF0		PCIF0
 
 /** @name 	INT_PCIFR 		Pin Change Interrupt Control Register */
 #define	INT_PCICR		PCICR
 #define	INT_PCIE0		PCIE0
 
 /** @name 	INT_PCMSK0 		Pin Change Mask Register 0 */
 #define	INT_PCMSK0		PCMSK0
 #define	INT_PCINT_7		PCINT7
 #define	INT_PCINT_6		PCINT6
 #define	INT_PCINT_5		PCINT5
 #define	INT_PCINT_4		PCINT4
 #define	INT_PCINT_3		PCINT3
 #define	INT_PCINT_2		PCINT2
 #define	INT_PCINT_1		PCINT1
 #define	INT_PCINT_0		PCINT0
 
 /** @name 	EXT_EICRA 		External Interrupt Control Register A */
 #define	EXT_EICRA		EICRA
 #define	EICRA_ISC31		ISC31
 #define	EICRA_ISC30		ISC30
 #define	EICRA_ISC21		ISC21
 #define	EICRA_ISC20		ISC20
 #define	EICRA_ISC11		ISC11
 #define	EICRA_ISC10		ISC10
 #define	EICRA_ISC01		ISC01
 #define	EICRA_ISC00		ISC00
 
 /** @name 	EXT_EICRB 		External Interrupt Control Register B */
 #define	EXT_EICRB		EICRB
 #define	EICRB_ISC71		ISC71
 #define	EICRB_ISC70		ISC70
 #define	EICRB_ISC61		ISC61
 #define	EICRB_ISC60		ISC60
 #define	EICRB_ISC51		ISC51
 #define	EICRB_ISC50		ISC50
 #define	EICRB_ISC41		ISC41
 #define	EICRB_ISC40		ISC40
 
 
 /**
 * @}
 */
 /* ================================= */
 
 
 
 /* SPI =========================================== */
 /** @defgroup 	SPI
 * @{
 */
 
 
 //* SPI Control Register */
 /** @name 	SPI_SPCR 	SPI Control Register */
 #define	SPI_SPCR	SPCR
 #define	SPCR_SPIE	SPIE
 #define	SPCR_SPE	SPE
 #define	SPCR_DORD	DORD
 #define	SPCR_MSTR	MSTR 
 #define	SPCR_CPOL	CPOL
 #define	SPCR_CPHA	CPHA
 #define	SPCR_SPR1	SPR1
 #define	SPCR_SPR0	SPR0
 
 //* SPI Status Register */
 /** @name 	SPI_SPSR 	SPI Status Register */
 #define	SPI_SPSR	SPSR
 #define	SPSR_SPIF	SPIF
 #define	SPSR_WCOL	WCOL
 #define	SPSR_SPI2X	SPI2X
 
 //* SPI Data Register */
 /** @name 	SPI_SPDR 	SPI Data Register */
 #define	SPI_SPDR	SPDR
 #define	SPI_SPI2X	SPI2X
 
 /**
 * @}
 */
 /* ================================= */
 
 
 /* UART =========================================== */
 /** @defgroup 	UART
 * @{
 */
 
  #if ( MICROCONTROLLER == USE_AT90USB1287 )
  
 #define	USART_UCSR1A	UCSR1A
 #define	UCSR1A_UDRE1	UDRE1
 
 #define	USART_UCSR1B	UCSR1B
 #define	UCSR1B_RXEN1	RXEN1
 #define	UCSR1B_TXEN1	TXEN1
 
 #define	USART_UCSR1C	UCSR1C
 #define	UCSR1C_UCSZ10	UCSZ10
 #define	UCSR1C_USBS1	USBS1
 
 #define	USART_UBRR1H	UBRR1H
 #define	USART_UBRR1L	UBRR1L
 #define	USART_UDR1		UDR1

  #elif ( MICROCONTROLLER == USE_AT90CAN128 )
  
   #define	USART_UCSR1A	UCSR0A
   #define	UCSR1A_UDRE1	UDRE0
   
   #define	USART_UCSR1B	UCSR0B
   #define	UCSR1B_RXEN1	RXEN0
   #define	UCSR1B_TXEN1	TXEN0
   
   #define	USART_UCSR1C	UCSR0C
   #define	UCSR1C_UCSZ10	UCSZ00
   #define	UCSR1C_USBS1	USBS0
   
   #define	USART_UBRR1H	UBRR0H
   #define	USART_UBRR1L	UBRR0L
   #define	USART_UDR1		UDR0
  
  #endif //MICROCONTROLLER==

 /**
 * @}
 */
 /* ================================= */
 
 
 
 /* WATCHDOG =========================================== */
 /** @defgroup 	WATCHDOG
 * @{
 */
 
 #if ( MICROCONTROLLER == USE_AT90USB1287 )
 
 #define	MCU_MCUSR		MCUSR
 #define	MCUSR_WDRF		WDRF
 
 //* WDT watchdog timer */
 /** @name 	WDT_WDTCSR 	WDT watchdog timer */
 #define	WDT_WDTCSR		WDTCSR
 #define	WDTCSR_WDIF		WDIF
 #define	WDTCSR_WDIE		WDIE
 #define	WDTCSR_WDP3		WDP3 
 #define	WDTCSR_WDCE		WDCE
 #define	WDTCSR_WDE		WDE
 #define	WDTCSR_WDP2		WDP2
 #define	WDTCSR_WDP1		WDP1
 #define	WDTCSR_WDP0		WDP0
 
 #define	WDT_64MS		( 1 << WDP1 )
 #define	WDT_125MS		( ( 1 << WDP1 ) | ( 1 << WDP0 ) )
 #define	WDT_250MS		( 1 << WDP2 ) 
 #define	WDT_500MS		( ( 1 << WDP2 ) | ( 1 << WDP0 ) )
 #define	WDT_1000MS		( ( 1 << WDP2 ) | ( 1 << WDP1 ) )
 
   #elif ( MICROCONTROLLER == USE_AT90CAN128 )

 #define	MCU_MCUSR		MCUSR
 #define	MCUSR_WDRF		WDRF
 
 //* WDT watchdog timer */
 /** @name 	WDT_WDTCSR 	WDT watchdog timer */
 #define	WDT_WDTCSR		WDTCR

 #define	WDTCSR_WDCE		WDCE
 #define	WDTCSR_WDE		WDE
 #define	WDTCSR_WDP2		WDP2
 #define	WDTCSR_WDP1		WDP1
 #define	WDTCSR_WDP0		WDP0
 
 #define	WDT_64MS		( 1 << WDP1 )
 #define	WDT_125MS		( ( 1 << WDP1 ) | ( 1 << WDP0 ) )
 #define	WDT_250MS		( 1 << WDP2 )
 #define	WDT_500MS		( ( 1 << WDP2 ) | ( 1 << WDP0 ) )
 #define	WDT_1000MS		( ( 1 << WDP2 ) | ( 1 << WDP1 ) )
  
  #endif //MICROCONTROLLER==

 /**
 * @}
 */
 /* ================================= */
 
 
 
 
 
 /* EEPROM MEMORY =========================================== */
 /** @defgroup 	EEPROM
 * 	 @attention	Piece of code below used only while LIBRARY_MODE == USE_AVR_LIB
 * @{
 */
 
 #if ( MICROCONTROLLER == USE_AT90USB1287 )
 
 //* EEPROM Control Register */
 /** @name 	EEPROM_EECR 	EEPROM Control Register */
 #define	EEPROM_EECR		EECR
  
 //* EEPROM Programming Mode Bits */
 /** @name 	EEPROM_EEPM1 	EEPROM Programming Mode Bits */
 #define	EEPROM_EEPM1	EEPM1
 
 //* EEPROM Programming Mode Bits */
 /** @name 	EEPROM_EEPM0 	EEPROM Programming Mode Bits */
 #define	EEPROM_EEPM0	EEPM0
 
 //* EEPROM Ready Interrupt Enable */
 /** @name 	EEPROM_EERIE 	EEPROM Ready Interrupt Enable */
 #define	EEPROM_EERIE	EERIE
 
 //* EEPROM Master Programming Enable */
 /** @name 	EEPROM_EEMPE 	EEPROM Master Programming Enable */
 #define	EEPROM_EEMPE	EEMPE
 
 //* EEPROM Programming Enable */
 /** @name 	EEPROM_EEPE 	EEPROM Programming Enable */
 #define	EEPROM_EEPE		EEPE
 
 //* EEPROM Read Enable */
 /** @name 	EEPROM_EERE 	EEPROM Read Enable */
 #define	EEPROM_EERE		EERE
 
 //* EEPROM Data Register */
 /** @name 	EEPROM_EEDR 	EEPROM Data Register */
 #define	EEPROM_EEDR		EEDR
 
 //* EEPROM Address Register */
 /** @name 	EEPROM_EEAR 	EEPROM Address Register */
 #define	EEPROM_EEAR		EEAR
 #define	EEPROM_EEARL	EEARL
 #define	EEPROM_EEARH	EEARH
 
 #elif ( MICROCONTROLLER == USE_AT90CAN128 )
   
  //* EEPROM Control Register */
  /** @name 	EEPROM_EECR 	EEPROM Control Register */
  #define	EEPROM_EECR		EECR
  
  //* EEPROM Programming Mode Bits */
  /** @name 	EEPROM_EEPM1 	EEPROM Programming Mode Bits */
  #define	EEPROM_EEPM1	EEPM1
  
  //* EEPROM Programming Mode Bits */
  /** @name 	EEPROM_EEPM0 	EEPROM Programming Mode Bits */
  #define	EEPROM_EEPM0	EEPM0
  
  //* EEPROM Ready Interrupt Enable */
  /** @name 	EEPROM_EERIE 	EEPROM Ready Interrupt Enable */
  #define	EEPROM_EERIE	EERIE
  
  //* EEPROM Master Programming Enable */
  /** @name 	EEPROM_EEMPE 	EEPROM Master Programming Enable */
  #define	EEPROM_EEMPE	EEMWE	//differemt from at90USB
  
  //* EEPROM Programming Enable */
  /** @name 	EEPROM_EEPE 	EEPROM Programming Enable */
  #define	EEPROM_EEPE		EEWE	//different from at90usb
  
  //* EEPROM Read Enable */
  /** @name 	EEPROM_EERE 	EEPROM Read Enable */
  #define	EEPROM_EERE		EERE
  
  //* EEPROM Data Register */
  /** @name 	EEPROM_EEDR 	EEPROM Data Register */
  #define	EEPROM_EEDR		EEDR
  
  //* EEPROM Address Register */
  /** @name 	EEPROM_EEAR 	EEPROM Address Register */
  #define	EEPROM_EEAR		EEAR
  #define	EEPROM_EEARL	EEARL
  #define	EEPROM_EEARH	EEARH
   
 #endif //MICROCONTROLLER==
 
 /**
 * @}
 */
 /* ================================= */
 
 
 
/* INTERRUPT VECTORS =========================================== */
 /** @defgroup 	INTERRUPTS_VECTORS
 *				Interrupt vectors for AT90USB1287
 * @{
 */
 
  
 #define	EXT_INT_EIFR	EIFR
 
 #define	INT0_VECTOR		INT0_vect
 #define	INT1_VECTOR		INT1_vect
 
 #define	INT2_VECTOR		INT2_vect
 #define	INT3_VECTOR		INT3_vect
 #define	INT4_VECTOR		INT4_vect
 #define	INT5_VECTOR		INT5_vect
 #define	INT6_VECTOR		INT6_vect
 #define	INT7_VECTOR		INT7_vect
 
 #define	PCINT0_VECTOR	PCINT0_vect
 #define	USB_GEN_VECTOR	USB_GEN_vect
 #define	USB_COM_VECTOR	USB_COM_vect
 #define	WDT_VECT		WDT_vect
 
 #define	TIMER2_COMPA_VECT		TIMER2_COMPA_vect
 #define	TIMER2_COMPB_VECT		TIMER2_COMPB_vect
 #define	TIMER2_OVF_VECT			TIMER2_OVF_vect
 
 #define	TIMER1_CAPT_VECT		TIMER1_CAPT_vect
 #define	TIMER1_COMPA_VECT		TIMER1_COMPA_vect
 #define	TIMER1_COMPB_VECT		TIMER1_COMPB_vect
 #define	TIMER1_OVF_VECT			TIMER1_OVF_vect
 
 #define	TIMER0_COMPA_VECT		TIMER0_COMPA_vect
 #define	TIMER0_COMPB_VECT		TIMER0_COMPB_vect
 
 #define	TIMER0_OVF_VECT			TIMER0_OVF_vect
 
 #define	SPI_STC_VECT			SPI_STC_vect
 #define	USART1_RX_VECT			USART1_RX_vect
 #define	USART1_UDRE_VECT		USART1_UDRE_vect
 #define	USART1_TX_VECT			USART1_TX_vect
 
 #define	ANALOG_COMP_VECT		ANALOG_COMP_vect
 
 #define	ADC_VECT				ADC_vect
 #define	EE_READY_VECT			EE_READY_vect
 
 #define	TIMER3_CAPT_VECT		TIMER3_CAPT_vect
 #define	TIMER3_COMPA_VECT		TIMER3_COMPA_vect
 #define	TIMER3_COMPB_VECT		TIMER3_COMPB_vect 
 #define	TIMER3_COMPC_VECT		TIMER3_COMPC_vect
 #define	TIMER3_OVF_VECT			TIMER3_OVF_vect
 #define	TWI_VECT				TWI_vect
 
 /**
 * @}
 */
 
 /* ================================= */
 

 //* shift these enums into another file with MACROS for AT90usb1287 or whole AVR family
 
 /* Enum: AT90USB1287 - EXT_SENSE_CONTROL */
 /** @enum		EXT_SENSE_CONTROL 
 *	 @brief		External Interrupt Sense Control */
 typedef enum {
	EXT_TRIGGER_LOW_LEVEL = 0,		/**< The low level of INTn generates asynchronously an interrupt request */
	EXT_TRIGGER_ANY_EDGE,			/**< Any edge of INTn generates an interrupt request */
	EXT_TRIGGER_FALLING_EDGE,		/**< The falling edge of INTn generates an interrupt request */
	EXT_TRIGGER_RISING_EDGE			/**< The rising edge of INTn generates an interrupt request */
 } EXT_SENSE_CONTROL;
 
 
 #endif
