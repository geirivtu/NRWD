#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/atomic.h>

#include "motor.h"

#define DIR_COUNTERCLOCKWISE	-1
#define DIR_CLOCKWISE			1

#define PHASE_A					OCR1C
#define PHASE_B					OCR1B
#define PHASE_C					OCR1A
#define HALL_A					INT5
#define HALL_B					INT6
#define HALL_C					INT4
#define HALL_A_vect				INT5_vect
#define HALL_B_vect				INT6_vect
#define HALL_C_vect				INT4_vect

uint8_t motor_speed = 0;
int8_t motor_direction;
uint8_t *commutation_table;

/* Commutation table for clockwise rotation */
uint8_t cw[] = {0x00, 0x05, 0x06, 0x04, 0x03, 0x01, 0x02};

/* Commutation table for counterclockwise rotation */
uint8_t ccw[] = {0x00, 0x02, 0x01, 0x03, 0x04, 0x06, 0x05};

uint8_t counter = 0; /* In TIMER0_OVF_vect */
volatile uint16_t rot_speed = 0;
volatile uint16_t rot_counter = 0;



void motor_init(void)
{
	/* Setting PB5-PB7 to outputs */
	DDRB |= (1<<PB5) | (1<<PB6) | (1<<PB7);
	/*
	PB5 : Motorfase C
   	PB6 : Motorfase B
	PB7 : Motorfase A
	*/
	
	/* Setting up Timer1 with fast PWM with TOP ICR1
	 * using prescaler clk/8 
	 * Clear OCnx on Compare Match and set at TOP
	 */
	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<COM1C1) | (1<<WGM11);
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11);

	/* PWM-period (1/16MHz * 8 * 100 = 50 us) 
	 * gives a PWM frequency of 20kHz	 */
	ICR1 = 100;

	/* Positiv width */ 
	PHASE_A = 0; //OCR1C Debug
	PHASE_B = 0; //OCR1B
	PHASE_C = 0; //OCR1A	

	/* Setting up timer0 for interrupt on overflow for measuring motor speed 
	 * clkIO/1024 (From prescaler) 
	 * Triggers at 61 Hz @ 16 Mhz clk */
	TCCR0A = (1<<CS02) | (1<<CS00);
	TIMSK0 = (1<<TOIE0);


	/* Set to output with high */
	/*
	For some reason the ext interrupt triggers randomly if it is set to input
	
	*/
	DDRE |= (1<<PE4) | (1<<PE5) | (1<<PE6);  
	PORTE |= (1<<PE4) | (1<<PE5) | (1<<PE6); 
	/*
	 * PE4 : HallC
	 * PE5 : HallA
	 * PE6 : HallB
	 */

	/* Enabling external level change interrupt on PE4-PE6 */
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

void motor_set_speed(int16_t speed)
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
		motor_speed = (100 * motor_direction);
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

	/* Used in speed calculation */
	rot_counter++; /* TODO should be atomic */
	
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
			break;

		default:
			break;
	}
}


void motor_read_hall(void)
{
	/* Reading hall-sensors */
	uint8_t index = ((PINE & 0x70)>>4);
	motor_commutate(index);
}

/* Nr of motor rotations per wrist revolution */
//#define MOTOR_ROT_FULL_TURN 333

/* Returns wrist speed in degrees per sec NOT TESTED 
 * wrist speed = ((rot_speed/(0.131 s))/MOTOR_ROT_FULL_TURN)*360/6
 *             = rot_speed * 458/MOTOR_ROT_FULL_TURN  */
int16_t motor_read_speed(void)
{
	int16_t speed =  0;	//debug
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		speed = (int16_t)(rot_speed*1.3738)*motor_direction;	
	}
	
	return speed;
}

/*  8*1/(61 Hz) = 131 ms between each rot_speed update  */
ISR(TIMER0_OVF_vect)
{
	/* Timer overflow */
	counter ++;
	if (counter == 8)
	{
		counter = 0;
		rot_speed = rot_counter;
		
		//speed = motor_read_speed(); //debug
		
		rot_counter = 0;

	}
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



