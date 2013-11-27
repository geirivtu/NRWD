/*
 * nrwd_test.c
 *
 * Created: 04.09.2013 14:50:49
 *  Author: Geir
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

#include "motor.h"
#include "position.h"
#include "current.h"
#include "controller.h"
#include "analog.h"
#include "can.h"




//! interrupt callback function for CAN receiver interrupt.
void setSetpoint( CAN_packet *p, unsigned char mob) // interrupt callback
{
	(void)mob;
	
	/*
	int16_t setpoint;
	setpoint = p->data[0] << 8;
	setpoint += p->data[1];
	*/
	
	int16_t speed = p->data[0];
	if(speed > 128) speed = -1;
	
	
	//control_set_setpoint(setpoint);
	control_set_setpoint(speed);
	//p->id= speed & 0xFFF;
	//can_tx( 14, p);
}



int main(void)
{
	motor_init();
	
	position_init();
	
	current_init();
		
	//analog_init();
		
	can_init();

	prepare_rx( 1, 0x151, 0x7ff, setSetpoint);

	control_set_mode(CONTROL_MODE_SPEED);
	
	/* Setting PD6 to output */
	
	DDRD |= (1<<PD6); //Debug
	
	PORTD &= ~(1<<PD6);	 //debug
	PORTD |= (1<<PD6); //Debug
	
	
	/* Enabling external interrupt */
	sei();

	volatile uint16_t pos_temp;
	
	volatile int16_t tmp = 0;
	
	CAN_packet *canTmp;
	canTmp->id = 0;
	canTmp->length = 1;
	canTmp->data[0] = 0;

    while(1)
    {
		
        //control_controller();
		control_speed_v2();
		//control_on_off();
		
		tmp = motor_read_speed();
		canTmp->data[0] = tmp;
	
		can_tx( 14, canTmp);

		
		_delay_ms(TIMESTEP);
    }
}


/* Overcurrent */
ISR(CURRENT_vect)
{
	motor_stop();

	controller_mode_t mode = control_get_mode();
	switch(mode){
		case CONTROL_MODE_ON_OFF:
			/* Set speed to 0 */ 
			control_set_setpoint(0);
			break;
		case CONTROL_MODE_POSITION:
			/* Set target position to current position */
			control_set_setpoint(position_read());
			break;
		
		case CONTROL_MODE_SPEED:
			/* Set speed to 0 */
			control_set_setpoint(0);
			break;
		
		default:
			/* Should not get here */
		
		break;
	}

	_delay_ms(1000);
	
	current_startup();
	motor_start();
}
