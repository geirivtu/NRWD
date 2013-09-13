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

volatile int tmp=0;

int main(void)
{

	motor_init();
	
	position_init();
	
	current_init();
	
	control_set_mode(MODE_POSITION);
	
	//motor_set_speed(70);
	
	//motor_start();
	
	/* Enabling external interrupt */
	sei();

    while(1)
    {
        //TODO:: Please write your application code 
		tmp = position_read();
    }
}


ISR(CURRENT_vect)
{
	/* Overcurrent */
	motor_stop();

	_delay_ms(1000);

	current_startup();
	motor_start();
}