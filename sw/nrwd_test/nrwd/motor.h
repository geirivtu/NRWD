#ifndef __MOTOR_H
#define __MOTOR_H



void motor_init(void);

void motor_start(void);

void motor_stop(void);

void motor_set_speed(signed int speed);


int16_t motor_read_speed(void);

#endif
