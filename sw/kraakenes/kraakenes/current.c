#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "current.h"


void current_init(void)
{
	DDRD |= (1<<PD4);

	/* Enabling interrupt on PD3 */
	EICRA |= (1<<ISC30) | (1<<ISC31);
	EIMSK |= (1<<INT3);

	/* Setting ADC reference voltage */
	ADMUX = (1<<REFS0);

	/* Enabling ADC */
	ADCSRA = (1<<ADEN);

	current_startup();
}

void current_startup(void)
{
	/* Toggling set-pin on SR-latch */
	PORTD |= (1<<PD4);
	_delay_us(1);
	PORTD &= ~(1<<PD4);
}

unsigned int current_read(void)
{
	/* Choosing channel ADC3 */
	ADMUX = (3 << 0);

	/* Starting conversion */
	ADCSRA |= (1<<ADSC);

	/* Waiting for conversion to complete */
	while (!(ADCSRA & (1<<ADIF)));

	return ADC;
}
