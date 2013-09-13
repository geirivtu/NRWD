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

	/* Setting ADC reference voltage to AVCC with external capacitor on AREF pin  */
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

/* Should return value in mA */
uint16_t current_read(void)
{
	/*
	uint16_t adc_ref_value = 5;
	uint16_t opamp_gain = 15.7
	uint16_t current_mA = 0;
	*/
	uint16_t K = 311; 
	
	/* Choosing channel ADC3, output from the OPAMP where 2.28V equals the max current of 145 mA  */
	/* The OPAMP has a gain of 15.7 */
	ADMUX = (3 << 0);

	/* Starting conversion */
	ADCSRA |= (1<<ADSC);

	/* Waiting for 10 bit ADC conversion to complete */
	while (!(ADCSRA & (1<<ADIF)));

	current_mA = ADC/(1<<10)

	return current_mA;
}
