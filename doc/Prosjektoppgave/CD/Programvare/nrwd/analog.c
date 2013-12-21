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
	/* Set up ADC for sampling on PF0(ADC0) and PF1(ADC1) */

	/* Setting ADC reference voltage to AVCC with external capacitor on AREF pin  */
	ADMUX = (1<<REFS0);
	
	/* Enabling ADC */
	ADCSRA = (1<<ADEN);
	
	/* Set up timer2 interrupt overflow to sample lines */
	/* f_interrupt = f_clkio / (N*(1+OCR2A)) */
	/* The N variable represents the prescale factor (1, 8, 32, 64, 128, 256, or 1024). */
	
	/* Defines top value of counter */
	OCR2A = 255;
	
	/* Prescaler: IOclock/64 and CTC mode( Clear Timer Compare Match) */
	TCCR2A = (1<<CS22) | (1<<WGM21);
	
	/* Timer/Counter2 Output Compare Match A Interrupt Enable */
	TIMSK2 = (1<<OCIE2A);	
}


uint16_t analog_read(uint8_t adc_nr){
	
	/* Set to correct ADC channel */
	if(adc_nr == ADC0_PF0){
		ADMUX = (ADMUX & 0b11100000) | ADC0_PF0; 
	}else if(adc_nr == ADC1_PF1){
		ADMUX = (ADMUX & 0b11100000) | ADC1_PF1; 
	}

	/* Starting conversion */
	ADCSRA |= (1<<ADSC);

	/* Waiting for 10 bit ADC conversion to complete */
	while (!(ADCSRA & (1<<ADIF)));
	/* Clear conversion complete flag */
	ADCSRA &= ~(1<<ADIF);	
	
	return ADC;
}

/* Read analog input */
void preprocessing(void){
	
	uint16_t sig_a, sig_b;
	
	
	sig_a = analog_read(ADC0_PF0);
	sig_b = analog_read(ADC1_PF1);
	
}


/* Use processed signals to control system */
void intent_interpretation(void){
	
	
	
}

ISR(TIMER2_COMP_vect)
{
	preprocessing(); 
}