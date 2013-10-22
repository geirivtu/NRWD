#ifndef __MOTOR_H
#define __MOTOR_H

#define DIR_COUNTERCLOCKWISE	-1
#define DIR_CLOCKWISE			1

#define PHASE_A					OCR1C
#define PHASE_B					OCR1B
#define PHASE_C					OCR1A
#define HALL_A					INT5
#define HALL_B					INT6
#define HALL_C					INT4
#define HALL_A_vect				INT5_vect
#define HALL_B_vect				INT6_vect
#define HALL_C_vect				INT4_vect

void motor_init(void);

void motor_start(void);

void motor_stop(void);

void motor_set_speed(signed int speed);

void motor_commutate(unsigned char index);

void motor_read_hall(void);

int16_t motor_read_speed(void);

#endif
