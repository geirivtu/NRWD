/**
 * @file    socket.c
 * @brief
 * @details
 * @author  Andreas Nordal @n NTNU in Trondheim (NORWAY)
 * @date    spring 2012
 */


#include <stddef.h> //offsetof

#include "socket.h"

#ifdef __AVR__
# include <avr/interrupt.h> //cli/sei
#else
# include <pthread.h>
static pthread_mutex_t big_lock = PTHREAD_MUTEX_INITIALIZER;
void cli(){ pthread_mutex_lock(&big_lock); }
void sei(){ pthread_mutex_unlock(&big_lock); }
#endif

//unexported stuff

static struct canel *
canel_of_msg(struct can_msg *mess){
	return (struct canel*) ((char*)mess - offsetof(struct canel, msg));
}

static struct can_msg *
sock_pull_unlocked(struct socket *this){
	struct canel *avail = (struct canel*)(this->rd); //discard volatile
	if(avail){
		this->rd = avail->next;
		return &avail->msg;
	}else{
		return NULL;
	}
}

static void
sock_push_unlocked(struct socket* this, struct canel *item){
	//assume item->next == NULL
	if(this->rd){
		this->wr->next = item;
	}else{
		this->rd = item;
	}
	this->wr = item;
}

//exported stuff

struct can_msg *
sock_pull(struct socket *this){
	cli();
	struct can_msg *ret = sock_pull_unlocked(this);
	sei();
	return ret;
}

void
sock_push(struct socket *this, struct can_msg *msg){
	struct canel *item = canel_of_msg(msg);
	item->next = NULL;

	cli();
	sock_push_unlocked(this, item);
	
#if CONFIG_SERIALIZE_CALLBACKS
	if(this->recv_hook && !this->recv_hook_running){
		this->recv_hook_running = ~0;
		for(;;){
			sei();
			this->recv_hook(this);
			cli();
			register struct canel *test;
			test = (struct canel*) this->rd; //discard volatile
			if(test == NULL) break; //we have handled everything
			if(test == item) break; //handler left it - stop nagging
		}
		this->recv_hook_running = 0;
	}
#endif
	sei();
	
#if !CONFIG_SERIALIZE_CALLBACKS
	if(this->recv_hook) this->recv_hook(this);
#endif
}

void
sock_init(struct socket *this){
	this->rd = NULL;
	//wr is invalid when rd is NULL
	this->recv_hook = NULL;
	this->recv_hook_running = 0;
}

void
sock_register_recv_hook(struct socket *this, sock_recv_hook fn){
	this->recv_hook = fn;
}
