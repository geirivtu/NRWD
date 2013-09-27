#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

#include "position.h"


//unsigned int period;
volatile uint16_t pulsewidth;
volatile uint16_t start_time;
volatile uint16_t stop_time;

void position_init(void)
{
	/* Setting up Input Capture */
	TCCR3A = 0x00;
	
	OCR3A = 0;
	/* (1<<ICES3) - Trigger capture event on pos edge
	 * (1<<ICNC3) - Input capture noise canceler 
	 * (1<<CS31)  - clkIO/8 (From prescaler) so max width doesn't overflow 16bit uint
	 */
	TCCR3B |= (1<<ICES3) | (1<<ICNC3)| (1<<CS31);
	/* Timer Input Capture interrupt enable */
	TIMSK3 |= (1<<ICIE3);
	
	
	/* Use noise canceler */
}

/* Returns = [0, 360] degrees
 * Pos edge from position sensor has pulse width from 1 - 4096 uS
 * which gives pulsewidth = [F_CPU/8 * 1e-6, F_CPU/8 * 4096e-6] = [2 ,8192]  
 * 22.75 equals 1 degree
 */
uint16_t position_read(void)
{
	/* Floating point operation
	 * Max pulse width = 8192 us = 360 degrees 
	 * Wrist pos = ((360 degrees)/(8192 us)) * pulsewidth us 
	 *           = 0.043945 * pulsewidth 
	 */
	 
	uint16_t degree = ((double)0.044 * pulsewidth);
	
	/* Could happen for at least two reasons
	* 1: pulse width from encoder exceeds 8192
	* 2: Pulse counter misses a edge
	* In both cases the resulting error will be < 1 degree
	 */
	if(degree>360){
		degree = 0;
	}
	
	return degree;
}

ISR(TIMER3_CAPT_vect)
{
	/* Reading timestamp */
	uint16_t icr = ICR3;
	
	/* Start of PWM period and positive edge */
	if ((TCCR3B & (1 << ICES3)))
	{
		/* Trigger interrupt on neg edge */
		TCCR3B &= ~(1<<ICES3);
		//period = icr - start_time;
		start_time = icr;
	}
	/* End of positive edge */
	else
	{
		/* Trigger interrupt on pos edge */
		TCCR3B |= (1<<ICES3);
		stop_time = icr;
		pulsewidth = stop_time - start_time;
	}	
}
