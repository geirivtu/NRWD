#ifndef __CURRENT_H
#define __CURRENT_H

#define CURRENT_vect	INT3_vect

/* The hardware current watcher disconnects the 
 * current to the motor at this value(in mA) taken from the specs  */
#define CURRENT_MAX	145


void current_init(void);

void current_startup(void);

unsigned int current_read(void);

#endif
