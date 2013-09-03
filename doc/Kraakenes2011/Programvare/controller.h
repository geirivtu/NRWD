#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#define MODE_ON_OFF		0
#define MODE_POSITION	1
#define MODE_SPEED		2

typedef void (*function)(void);
function control_controller;

char control_set_mode(unsigned char mode);

void control_on_off(void);

void control_position(void);

void control_speed(void);

void control_set_setpoint(signed int setpoint);

void control_set_parameter(unsigned int proportional);

#endif
