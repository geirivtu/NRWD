#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "motor.h"


unsigned char motor_speed = 0;
signed char motor_direction;
unsigned char *commutation_table;

/* Commutation table for clockwise rotation */
unsigned char cw[] = {0x00, 0x05, 0x06, 0x04, 0x03, 0x01, 0x02};

/* Commutation table for counterclockwise rotation */
unsigned char ccw[] = {0x00, 0x02, 0x01, 0x03, 0x04, 0x06, 0x05};

unsigned char counter = 0;
unsigned int rot_speed = 0;
unsigned int rot_counter = 0;

void motor_init(void)
{
	/* Setting PB5-PB7 to outputs */
	DDRB |= (1<<PB5) | (1<<PB6) | (1<<PB7);

	/* Internal pull-up */
	DDRE |= (1<<PE4) | (1<<PE5) | (1<<PE6);
	PORTE |= (1<<PE4) | (1<<PE5) | (1<<PE6);

	/* Setting PWM-mode and prescaler */
	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<COM1C1) | (1<<WGM11);
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11);

	/* PWM-period (1/16MHz * 8 * 100 = 50 us) */
	ICR1 = 100;

	/* Positiv width */
	PHASE_A = 0;
	PHASE_B = 0;
	PHASE_C = 0;

	/* Setting up timer for interrupt on overflow for measuring motor speed */
	TCCR0A = (1<<CS02) | (1<<CS00);
	TIMSK0 = (1<<TOIE0);

	/* Enabling external interrupt on PE4-PE6 */
	EICRB = (1<<ISC60) | (1<<ISC50) | (1<<ISC40);
	EIMSK = (1<<HALL_A) | (1<<HALL_B) | (1<<HALL_C);
}

void motor_start(void)
{
	/* Setting PB5-PB7 to outputs */
	DDRB |= (1<<PB5) | (1<<PB6) | (1<<PB7);

	/* Reading rotor position for first commutation */
	motor_read_hall();
}

void motor_stop(void)
{
	/* Setting PB5-PB7 to inputs */
	DDRB = 0x00;
}

void motor_set_speed(signed int speed)
{
	if(speed < 0)
	{
		motor_direction = DIR_COUNTERCLOCKWISE;
		commutation_table = ccw;
	}
	else if(speed > 0)
	{
		motor_direction = DIR_CLOCKWISE;
		commutation_table = cw;
	}

	/* Saturation */
	if((speed * motor_direction) > 100)
	{
		motor_speed = 100;
	}
	else
	{
		motor_speed = (speed * motor_direction);
	}

	/* Starting up motor if speed is zero */
	if(!motor_read_speed())
	{
		motor_start();
	}
}

void motor_commutate(unsigned char index)
{
	switch (commutation_table[index])
	{
		case 0x01:
			PHASE_A = 0;
			PHASE_B = 0;
			PHASE_C = motor_speed;
			break;

		case 0x02:
			PHASE_A = 0;
			PHASE_B = motor_speed;
			PHASE_C = 0;
			break;

		case 0x03:
			PHASE_A = 0;
			PHASE_B = motor_speed;
			PHASE_C = motor_speed;
			break;

		case 0x04:
			PHASE_A = motor_speed;
			PHASE_B = 0;
			PHASE_C = 0;
			break;

		case 0x05:
			PHASE_A = motor_speed;
			PHASE_B = 0;
			PHASE_C = motor_speed;
			break;

		case 0x06:
			PHASE_A = motor_speed;
			PHASE_B = motor_speed;
			PHASE_C = 0;

			rot_counter++;
			break;

		default:
			break;
	}
}

void motor_read_hall(void)
{
	/* Reading hall-sensors */
	unsigned char index = ((PINE & 0x70)>>4);
	motor_commutate(index);
}

unsigned int motor_read_speed(void)
{
	return rot_speed;
}

ISR(HALL_A_vect)
{
	motor_read_hall();
}

ISR(HALL_B_vect)
{
	motor_read_hall();
}

ISR(HALL_C_vect)
{
	motor_read_hall();
}


ISR(TIMER0_OVF_vect)
{
	/* Timer overflow */
	counter ++;
	if (counter == 10)
	{
		counter = 0;
		rot_speed = rot_counter;
		rot_counter = 0;
	}
}
