#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

#include "controller.h"
#include "current.h"
#include "motor.h"
#include "position.h"
//#include "uart.h"


int16_t control_setpoint = 0;


uint16_t K_p = 1;
uint16_t K_i = 1;

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

/* Should set motor to max speed while not exceeding max current NOT TESTED */
void control_on_off(void)
{
	signed int setpoint = control_setpoint;
	
	// uint16_t current_read()

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





/* Make it a KI regulator 
 * control_setpoint = [0, 360] NOT TESTED */
void control_position(void)
{
	static int16_t accum_error = 0; //make static
	static int16_t prev_control_setpoint = 0; //make static
	int16_t motor_setpoint = 0;
	uint16_t position;
	int16_t error;
	
	int8_t max_accum_erro = 40;
	
	/* error - how many degrees away from setpoint */
	position = position_read();
    error = control_setpoint - position;
	if(error > 180) error = error - 360;
	if(error < -180) error = 360 + error;

	/* If set point changed, reset accumulated error */
	if(prev_control_setpoint != control_setpoint){
		accum_error = 0;
	}

	/* Proportional part */
    motor_setpoint = K_p*error;
	
	/* Integral part */
	motor_setpoint += K_i*accum_error; // TODO Check for overflow? Multiply with timestep?
	
	/* motor_setpoint is between [-100, 100] */
	if(motor_setpoint > 100){
		motor_setpoint = 100;
	}else if(motor_setpoint < -100){
		motor_setpoint = -100;
	}
	
	accum_error += error;
	/* acum_error not to exceed a certain value */
	if(accum_error > max_accum_erro){
		accum_error = max_accum_erro;
	}else if(accum_error < -max_accum_erro){
		accum_error = -max_accum_erro;
	}	
	
	prev_control_setpoint = control_setpoint;
	
	motor_set_speed(motor_setpoint);
}


/* Measured angular velocity with stopwatch at different duycycles

Speed(DC)   Angular velocity(degrees per sec)
80				156
65				94
50				44
*/

int16_t motor_setpoint = 0;
int16_t prev_motor_setpoint = 0;
static int16_t accum_error = 0; //make static
static int16_t prev_control_setpoint = 0; //make static
int16_t error;

/* NOT TESTED */
void control_speed(void)
{
	
	int8_t max_accum_error = 50;
	
	error = control_setpoint - motor_read_speed();
    
	
		
	/* If set point changed, reset accumulated error */
	if(prev_control_setpoint != control_setpoint){
		accum_error = 0;
	}
	
	/* Proportional part */
	motor_setpoint = 50 + (K_p*error);
	
	/* Integral part */
	motor_setpoint += K_i*accum_error; // TODO Check for overflow?
	
	accum_error += error;
	/* acum_error not to exceed a certain value */
	if(accum_error > max_accum_error){
		accum_error = max_accum_error;
	}else if(accum_error < -max_accum_error){
		accum_error = -max_accum_error;
	}	
	
	
	/* motor_set_speed already checks for saturation */
	/*
	if (motor_setpoint >= 100)
	{
		motor_setpoint = 100;
	}
	else if (motor_setpoint <= -100)
	{
		motor_setpoint = -100;
	}
	*/
	prev_motor_setpoint = motor_setpoint;
	
	motor_set_speed(motor_setpoint);
}

void control_set_setpoint(int16_t setpoint)
{
	control_setpoint = setpoint;
}

void control_set_parameter(unsigned int proportional)
{
	K_p = proportional;
}
