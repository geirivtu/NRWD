#ifndef __CONTROLLER_H
#define __CONTROLLER_H


#define TIMESTEP 150

typedef enum mode{
	CONTROL_MODE_ON_OFF,
	CONTROL_MODE_POSITION,
	CONTROL_MODE_SPEED,
	} controller_mode_t;

typedef void (*function)(void);

function control_controller;

uint8_t control_set_mode(controller_mode_t mode);

controller_mode_t control_get_mode(void);

void control_on_off(void);

void control_position(void);

void control_speed(void);

void control_set_setpoint(int16_t setpoint);

void control_set_parameter(double proportional);

void control_speed_v2(void); //remove


#endif
