/**
 * @file    socket.h
 * @brief
 * @details
 * @author  Andreas Nordal @n NTNU in Trondheim (NORWAY)
 * @date    spring 2012
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include "config.h"
#include "types.h"

struct can_msg{
	u16 id : 11;
	u8 len :  4;
	u8 rtr :  1;
	union{
		u8 data[8];
		struct{
			u8 function_code;
			u8 function_specific[7];
		};
	};
};

struct socket;
typedef void (*sock_recv_hook)(struct socket*);

/**
 * CAN element: linked list container of CAN messages.
 */
struct canel{
	struct canel *next;
	struct can_msg msg;
};

/**
 * FIFO of CAN elements
 * @param rd Read pointer
 * @param wr Write pointer
 */
struct socket{
	volatile struct canel *rd, *wr;
	sock_recv_hook recv_hook;
	volatile _Bool recv_hook_running;
};

void sock_init(struct socket*);
void sock_register_recv_hook(struct socket*, sock_recv_hook);
void sock_push(struct socket*, struct can_msg*);
struct can_msg *sock_pull(struct socket*);

#endif
