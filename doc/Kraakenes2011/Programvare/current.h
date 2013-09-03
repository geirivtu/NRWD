#ifndef __CURRENT_H
#define __CURRENT_H

#define CURRENT_vect	INT3_vect

void current_init(void);

void current_startup(void);

unsigned int current_read(void);

#endif
