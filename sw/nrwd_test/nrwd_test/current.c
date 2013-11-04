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
	
	/* First conversion ends up with wrong(?) result, do one at init to warmup ADC */
	ADMUX |= 3;
	/* Starting conversion */
	ADCSRA |= (1<<ADSC);

	/* Waiting for 10 bit ADC conversion to complete */
	while (!(ADCSRA & (1<<ADIF)));
	/* Clear conversion complete flag */
	ADCSRA &= ~(1<<ADIF);

	current_startup();
}

void current_startup(void)
{
	/* Toggling set-pin on SR-latch */
	PORTD |= (1<<PD4);
	_delay_us(1);
	PORTD &= ~(1<<PD4);
}


/* Returns current in mA */ //TODO not working??

uint16_t current_read(void)
{
	uint16_t current_mA = 0;
	/* Multiply K with ADC value to get current in uA 
	* K = ADCref * (1'000'000/1024)/(Aopamp) = 311 
	* ADCref = 5 V
	* Aopamp = 15.7 (opamp gain)
	*/
	uint16_t K = 31; //311 
	
	/* Choosing channel ADC3, output from the OPAMP where 2.28V equals the max current of 145 mA  */
	/* The OPAMP has a gain of 15.7 */
	ADMUX |= 3;

	/* Starting conversion */
	ADCSRA |= (1<<ADSC);

	/* Waiting for 10 bit ADC conversion to complete */
	while (!(ADCSRA & (1<<ADIF)));
	/* Clear conversion complete flag */
	ADCSRA &= ~(1<<ADIF);
	//adc = ADC;
	
	//kAdc = K*adc;
	current_mA = (K*ADC)/100;

	return current_mA;
}
