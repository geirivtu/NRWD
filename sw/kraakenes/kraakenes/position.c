#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

#include "position.h"


unsigned int period;
unsigned int pulsewidth;
unsigned int start_time;
unsigned int stop_time;

void position_init(void)
{
	/* Setting up Input Capture */
	TCCR3A = 0x00;
	OCR3A = 0;
	TCCR3B |= (1<<ICES3) | (1<<CS31);
	TIMSK3 |= (1<<ICIE3);
}

unsigned int position_read(void)
{
	return pulsewidth;
}

ISR(TIMER3_CAPT_vect)
{
	/* Reading timestamp */
	unsigned int icr = ICR3;

	/* Start of PWM period and positive edge */
	if ((TCCR3B & (1 << ICES3)))
	{
		TCCR3B &= ~(1<<ICES3);
		period = icr - start_time;
		start_time = icr;
	}
	/* End of positive edge */
	else
	{
		TCCR3B |= (1<<ICES3);
		stop_time = icr;
		pulsewidth = stop_time - start_time;
	}
}
