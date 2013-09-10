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

volatile int tmp=0;

int main(void)
{
	
	
	motor_init();
	
	//motor_set_speed(100);
	
	//motor_start();
	
	/* Enabling external interrupt */
	sei();

    while(1)
    {
        //TODO:: Please write your application code 
		tmp++;
    }
}