/**
 * @file    hll.c
 * @brief
 * @details
 * @author  Andreas Nordal @n NTNU in Trondheim (NORWAY)
 * @date    spring 2012
 */


#include <stddef.h> //NULL

#include "hll.h"
#include "pdcp.h"
#include "hll_device.h"
#include "hll_arbitrator.h"
void hal_msg_take(void);
void hal_msg_poll(void);

/*
 * The sock_* functions' systematic use of a this-pointer
 * enables more than one array of sockets to be used.
 * Is this meaningful for HLL to expose to HAL?
 * - No, HAL expects HLL to be a singleton like itself.
 * 
 * As originally intended, we provide wrapper functions
 * to index this singleton array using socket numbers
 * (akin to file descriptors) and invoke the sock_* functions.
 * 
 * However, the application may also contain its own sockets,
 * when wrapped in struct canel.
 * Separating buffers into isolated
 * datastructures may reduce need for synchronization.
 */

struct hll hll_global;

//internal hooks

/* what to do when space becomes available? */
static void
space_avail(struct socket *ignore){
	hal_msg_poll();
}

static void
send_to_hal(struct socket *ignore){
	hal_msg_take();
}

//application API

void
hll_init(sock_recv_hook app_callback, hll_handled_hook notify){
	struct hll *this = &hll_global;
	this->notify = notify;
	socknum_t i;
	const int SOCK_FREE = 0;
	
	struct canel *target = NULL;
	i = CONFIG_NUM_CANMSG;
	while(i--){
		this->canbuf[i].next = target;
		target = &this->canbuf[i];
	}
	
	i = SOCK_TOT_HLL;
	while(i--){
		sock_init(&this->sock[i]);
	}
	
	//to begin with, all buffers are free
	this->sock[SOCK_FREE].rd = this->canbuf;
	this->sock[SOCK_FREE].wr = this->canbuf + CONFIG_NUM_CANMSG-1;
	
	sock_register_recv_hook(&this->sock[SOCK_STDIN      ], post_office );
	sock_register_recv_hook(&this->sock[SOCK_APPLICATION], app_callback);
	sock_register_recv_hook(&this->sock[SOCK_STDOUT     ], send_to_hal );
	sock_register_recv_hook(&this->sock[SOCK_FREE       ], space_avail );

	hll_arbdev_init();
}

struct can_msg *
hll_msg_pull(socknum_t sd){
	return sock_pull(&hll_global.sock[sd]);
}

void
hll_msg_push(struct can_msg *msg, socknum_t sd){
	sock_push(&hll_global.sock[sd], msg);
}

/** @defgroup API for use by HAL
 * @{
 */

/**
 * Pull from the FREE queue.
 */
struct can_msg *
hll_msg_alloc(){
	return hll_msg_pull(SOCK_FREE);
}

/**
 * Push to the STDOUT queue.
 * Sets Message Mode to 1 if we are an arbitrator.
 */
struct can_msg *
hll_msg_get(){
	struct can_msg *msg = hll_msg_pull(SOCK_STDOUT);
	msg->id = (msg->id & 0xff) | (CONFIG_BUS_MODE << MESSAGE_MODE);
	return msg;
}

/**
 * Push to the STDIN queue.
 */
void
hll_msg_commit(struct can_msg *msg){
	hll_msg_push(msg, SOCK_STDIN);
}

/**
 * Pull from the STDOUT queue.
 */
void
hll_msg_free(struct can_msg *msg){
	hll_msg_push(msg, SOCK_FREE);
}

/// @}
