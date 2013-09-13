#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

#include "controller.h"
#include "current.h"
#include "motor.h"
#include "position.h"
#include "uart.h"


signed int control_setpoint = 0;
signed int motor_setpoint = 0;
signed int prev_motor_setpoint = 0;

unsigned int K_p = 1;
int16_t K_i = 1;

char control_set_mode(unsigned char mode)
{
	if (mode == MODE_ON_OFF)
	{
		control_controller = &control_on_off;
	}
	else if (mode == MODE_POSITION)
	{
		control_controller = &control_position;
	}
	else if (mode == MODE_SPEED)
	{
		control_controller = &control_speed;
	}
	else
	{
		return 0;
	}
	return 1;
}

/* Should set motor to max speed while not exceeding max current */
void control_on_off(void)
{
	signed int setpoint = control_setpoint;

	if (setpoint > 0)
	{
		motor_set_speed(100);
	}
	else if (setpoint < 0)
	{
		motor_set_speed(-100);
	}
	else
	{
		motor_set_speed(0);
	}
}

/* Make it a KI regulator */
/* control_setpoint = [0, 360] */
void control_position(void)
{
	static int16_t accum_error = 0;
	static int16_t prev_control_setpoint = 0;
	
	/* error - how many degrees away from setpoint */
    int16_t error = control_setpoint - position_read();

	/* If set point changed, reset accumulated error */
	if(prev_control_setpoint != control_setpoint){
		accum_error = 0;
	}

    int16_t output = (K_p*error + K_i*accum_error); // Debug Check for overflow?
	
	/* Output is between [-100, 100] */
	if(output > 100){
		output = 100;
	}else if(output < -100){
		output = -100;
	}
	
	accum_error += error;
	/* acum_error not to exceed a certain value */
	if(accum_error > 30){
		accum_error = 30;
	}else if(accum_error < -30){
		accum_error = -30;
	}	
	
	prev_control_setpoint = control_setpoint;
	
	motor_set_speed(output);
}

void control_speed(void)
{
	signed int error = control_setpoint - motor_read_speed();
    int16_t new_speed;
	
	motor_setpoint = (K_p*error);
	new_speed = prev_motor_setpoint + motor_setpoint;
	

	if (new_speed >= 100)
	{
		motor_set_speed(100);
		prev_motor_setpoint = 100;
	}
	else if (new_speed <= -100)
	{
		motor_set_speed(-100);
		prev_motor_setpoint = -100;
	}
	else {
		motor_set_speed(new_speed);
		prev_motor_setpoint = (new_speed);
	}
}

void control_set_setpoint(signed int setpoint)
{
	control_setpoint = setpoint;
}

void control_set_parameter(unsigned int proportional)
{
	K_p = proportional;
}
