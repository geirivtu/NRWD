/*
 * analog.c
 *
 * Created: 15.10.2013 16:59:45
 *  Author: Geir
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define ADC0_PF0 0
#define ADC1_PF1 1


void analog_init(void){
	

/* Set up ADC sampling on PF0(ADC0) and PF1(ADC1) */

	/* Setting ADC reference voltage to AVCC with external capacitor on AREF pin  */
	ADMUX = (1<<REFS0);
	
	/* Enabling ADC */
	ADCSRA = (1<<ADEN);
	
	/* First conversion ends up with wrong(?) result, do one at init to warmup ADC */
	ADMUX |= (3 << 0);
	/* Starting conversion */
	ADCSRA |= (1<<ADSC);

	/* Waiting for 10 bit ADC conversion to complete */
	while (!(ADCSRA & (1<<ADIF)));
	/* Clear conversion complete flag */
	ADCSRA &= ~(1<<ADIF);



/* Set up timer interrupt to sample lines */


	/* Setting up Timer1 with fast PWM with TOP ICR1
	 * using prescaler clk/8 
	 * Clear OCnx on Compare Match and set at TOP
	 */
	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<COM1C1) | (1<<WGM11);
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11);

	/* PWM-period (1/16MHz * 8 * 100 = 50 us) 
	 * gives a PWM frequency of 20kHz	 */
	ICR1 = 100;



	/* Setting up timer0 for interrupt on overflow for measuring motor speed 
	 * clkIO/1024 (From prescaler) 
	 * Triggers at 61 Hz @ 16 Mhz clk */
	TCCR0A = (1<<CS02) | (1<<CS00);
	TIMSK0 = (1<<TOIE0);	
	
}


uint16_t analog_read(uint8_t adc_nr){
	
	/* Set to correct ADC channel */
	if(adc_nr == ADC0_PF0){
		//ADMUX &= 0b11100000 | ADC0_PF0; wrong
	}else if(adc_nr == ADC1_PF1){
		//ADMUX &= 0b11100000 | ADC1_PF1; wrong
	}else{
		//error
	}

	/* Starting conversion */
	ADCSRA |= (1<<ADSC);

	/* Waiting for 10 bit ADC conversion to complete */
	while (!(ADCSRA & (1<<ADIF)));
	/* Clear conversion complete flag */
	ADCSRA &= ~(1<<ADIF);	
	
	return ADC;
}


ISR(TIMER2_OVF_vect)
{

}