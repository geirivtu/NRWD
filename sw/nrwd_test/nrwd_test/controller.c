#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h>
#include <util/atomic.h>

#include "controller.h"
#include "current.h"
#include "motor.h"
#include "position.h"


volatile int16_t Control_setpoint = 0;

/* Decides how close to the CURRENT_MAX the controllers
 * should regulate to */
static int8_t Current_safe_zone = 10;

controller_mode_t Controller_mode = CONTROL_MODE_ON_OFF; 

/* P and I-term for the on/off regulator */
double K_p_on_off = 0.4;
double K_i_on_off = 0.1;

/* P and I-term for the position regulator */
double K_p_position = 0.9;
double K_i_position = 0.1;

/* P and I-term for the speed regulator */
/* outer loop */
double K_p_v_speed = 0.4;
double K_i_v_speed = 0.07;

/* inner loop */
double K_p_i_speed = 0.4;
double K_i_i_speed = 0.07;
	

uint8_t control_set_mode(controller_mode_t mode)
{
	if (mode == CONTROL_MODE_ON_OFF)
	{
		control_controller = &control_on_off;
		Controller_mode = CONTROL_MODE_ON_OFF;
	}
	else if (mode == CONTROL_MODE_POSITION)
	{
		control_controller = &control_position;
		Controller_mode = CONTROL_MODE_POSITION;
	}
	else if (mode == CONTROL_MODE_SPEED)
	{
		control_controller = &control_speed;
		Controller_mode = CONTROL_MODE_SPEED;
	}
	else
	{
		return 0;
	}
	return 1;
}

/* Returns the current control mode */
controller_mode_t control_get_mode()
{
	return Controller_mode;
}


/* Should set motor to max speed while not exceeding max current NOT TESTED */
void control_on_off(void)
{
	int16_t motor_setpoint = 0;
	static int16_t accum_error = 0; 

	int16_t error;
	uint16_t current;
	uint8_t current_setpoint;
		
	current_setpoint = CURRENT_MAX-Current_safe_zone;

	if(Control_setpoint!=0){
		current = current_read();
		error = current_setpoint - current;
	
		/* Proportional part */
		motor_setpoint = (int16_t)(K_p_on_off*error);

		/* Integral part */
		motor_setpoint += (int16_t)(K_i_on_off*accum_error); 
	
		accum_error += error;	
	}
	else{ 
		accum_error = 0;
	}
	
	/* Control_setpoint decides motor direction */
	if (Control_setpoint > 0)
	{
		motor_set_speed(motor_setpoint);
	}
	else if (Control_setpoint < 0)
	{
		motor_set_speed(-motor_setpoint);
	}else{
		motor_set_speed(0);
	}
}





/* Make it a KI regulator 
 * Control_setpoint = [0, 360] NOT TESTED */
void control_position(void)
{
	
	static int16_t accum_error = 0; 
	static int16_t prev_Control_setpoint = 0; 
	int16_t motor_setpoint = 0;
	uint16_t position;
	int16_t error;
	
	/* How many degrees of error the system accepts */
	uint8_t error_tolerance = 3;
	

	
	/* error - how many degrees away from setpoint */
	position = position_read();
    error = Control_setpoint - position;
	if(error > 180) error = error - 360;
	if(error < -180) error = 360 + error;

	/* If set point changed, reset accumulated error */
	if(prev_Control_setpoint != Control_setpoint){
		accum_error = 0;
	}

	if(abs(error) > error_tolerance){
		/* Proportional part */
		motor_setpoint = (int16_t)(K_p_position*error);

		/* Integral part */
		motor_setpoint += (int16_t)(K_i_position*accum_error); 
	
		accum_error += error;
	}else{
		motor_setpoint = 0;
		accum_error = 0;
	}
	
	prev_Control_setpoint = Control_setpoint;
	
	motor_set_speed(motor_setpoint);
}


/* Measured angular velocity with stopwatch at different dutycycles

Speed(DC)   Angular velocity(degrees per sec)
80				156
65				94
50				44
*/

/* NOT TESTED */
void control_speed(void)
{
	int16_t motor_setpoint = 0;
	static int16_t accum_error = 0; 

	int16_t error;
	uint16_t current;
	
	double K_p = 0.4;
	double K_i = 0.07;
	
	/* Special case: Minimize the time it takes before stopping */
	if(Control_setpoint==0) accum_error = 0;
	
	int16_t control_motor_speed = motor_read_speed();
	
	current = current_read();
	if(current >= (CURRENT_MAX-Current_safe_zone)){
		/* Set new setpoint so as not to exceed CURRENT_MAX */
		control_set_setpoint(control_motor_speed);
	}
	
	error = Control_setpoint - control_motor_speed;
	
	/* Proportional part */
	motor_setpoint = (int16_t)(K_p*error);

	/* Integral part */
	motor_setpoint += (int16_t)(K_i*accum_error); 
	
	accum_error += error;

	/* motor_set_speed already checks for saturation */	
	motor_set_speed(motor_setpoint);
}


	int16_t motor_setpoint = 0;
	static int16_t accum_error_v = 0;
	static int16_t accum_error_i = 0;
	
	int16_t current_setpoint = 0;

	int16_t error_v;
	int16_t error_i;
	
	uint16_t current;
	int16_t control_motor_speed;
	
void control_speed_v2(void)
{

	/* Special case: Minimize the time it takes before stopping */
	//if(Control_setpoint==0) accum_error = 0;
	
	control_motor_speed = motor_read_speed();
	error_v = Control_setpoint - control_motor_speed;
	
	/* Outer loop pi regulator */
	current_setpoint = (int16_t)(K_p_v_speed*error_v) + (int16_t)(K_i_v_speed*accum_error_v);
	accum_error_v += error_v;
	
	//Current saturation
	if(current_setpoint >= (CURRENT_MAX-Current_safe_zone)){
		current_setpoint = 	(CURRENT_MAX-Current_safe_zone);
	}
	
	current = current_read();
	error_i = current_setpoint - current;
	
	/* Inner loop pi regulator */
	motor_setpoint = (int16_t)(K_p_i_speed*error_i) + (int16_t)(K_i_i_speed*accum_error_i);
	accum_error_i += error_i;

	if(Control_setpoint == 0){
		 accum_error_i = 0;
		 accum_error_v = 0;
	}

	/* motor_set_speed already checks for saturation */
	motor_set_speed(motor_setpoint);
}

void control_set_setpoint(int16_t setpoint)
{
	/* Makes setting of variable atomic */
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		Control_setpoint = setpoint;
	}
}


/* Expected order of parameters in the parameter_array is:
 * parameter_array = { P  term, I term, Optional second P term, Optional second I term}  */
void control_set_parameter(double * parameter_array, uint8_t array_len )
{
	switch(Controller_mode){
		case CONTROL_MODE_ON_OFF:
			K_p_on_off = parameter_array[0];
			K_i_on_off = parameter_array[1];
		break;
		
		case CONTROL_MODE_POSITION:
			K_p_position = parameter_array[0];
			K_i_position = parameter_array[1];		
		break;
		
		case CONTROL_MODE_SPEED:
			/* Outer loop parameters */
			K_p_v_speed = parameter_array[0];
			K_i_v_speed = parameter_array[1];
			
			if(array_len>1){
				/* Inner loop parameters */
				K_p_i_speed = parameter_array[2];
				K_i_i_speed = parameter_array[3];
			}
		break;
	}
}


