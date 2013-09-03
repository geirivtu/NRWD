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
unsigned int K_p = 0;

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

void control_position(void)
{
//	signed int error = control_setpoint - position_read();

//	signed int output = (K_p*error);

//	motor_set_speed(output);
}

void control_speed(void)
{
	signed int error = control_setpoint - motor_read_speed();

	motor_setpoint = (K_p*error);

	if (prev_motor_setpoint + motor_setpoint >= 100)
	{
		motor_set_speed(100);
		prev_motor_setpoint = 100;
	}
	else if (prev_motor_setpoint + motor_setpoint <= -100)
	{
		motor_set_speed(-100);
		prev_motor_setpoint = -100;
	}
	else {
		motor_set_speed(prev_motor_setpoint + motor_setpoint);
		prev_motor_setpoint = (prev_motor_setpoint + motor_setpoint);
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
