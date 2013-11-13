/**
 * @file    hll_device.c
 * @brief
 * @details
 * @author  Andreas Nordal @n NTNU in Trondheim (NORWAY)
 * @date    spring 2012
 */


#include "config.h"
#if CONFIG_BUS_MODE == BUS_DEVICE

#include "hll.h"
#include "hll_device.h"
#include "pdcp.h"
#include "hal.h"

void hll_arbdev_init(){}

/**
 * Handles some messages, sorts rest into SOCK_APPLICATION.
 */
void
post_office(struct socket *so){
	struct can_msg *msg = sock_pull(so);

	switch(msg->function_code){
		case RESPONS_BIND:
			respond_bind(msg);
			break;
		case REQUEST_RESET:
			respond_reset(msg);
			// should not return
		default:
			hll_msg_push(msg, SOCK_APPLICATION);
			return;
	}
	hll_global.notify(msg->function_code);
}

_Bool request_bind(u8 hint_nodeId){
	hal_set_filter(hint_nodeId);
	
	struct can_msg *msg = hll_msg_alloc();
	if(!msg) return 0; //fail
	
	typedef struct request_bind T;
	T *specific = (T*) &msg->function_specific;
	msg->len = sizeof(msg->function_code) + sizeof(T);
	
	msg->function_code      = REQUEST_BIND;
	msg->id                 = hint_nodeId | (3 << MESSAGE_PRIORITY);
	specific->vendor_id     = CONFIG_VENDOR_ID;
	specific->product_id    = CONFIG_PRODUCT_ID;
	specific->serial_number = CONFIG_SERIAL_NUMBER;
	
	hll_msg_push(msg, SOCK_STDOUT);
	return ~0; //success
}

void respond_bind(struct can_msg *msg){
	typedef struct respons_bind T;
	T *specific = (T*) &msg->function_specific;
	if(specific->serial_number != CONFIG_SERIAL_NUMBER) return;
	if(specific->product_id    != CONFIG_PRODUCT_ID   ) return;
	if(specific->vendor_id     != CONFIG_VENDOR_ID    ) return;
	
	u8 oldId = msg->id & 0xff;
	u8 newId = specific->node_id;
	if(newId != oldId){
		request_bind(newId);
	}
}

void respond_reset(struct can_msg *msg){
	typedef struct respons_reset T;
	T *specific = (T*) &msg->function_specific;
	msg->len = sizeof(msg->function_code) + sizeof(T);
	
	specific->response_code = RESPCODE_SUCCESS;
	
	hll_msg_push(msg, SOCK_STDOUT);
	forceReset();
}

#endif
