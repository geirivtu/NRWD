/**
 * @file    hll_arbitrator.c
 * @brief
 * @details
 * @author  Andreas Nordal @n NTNU in Trondheim (NORWAY)
 * @date    spring 2012
 */


#include "config.h"
#if CONFIG_BUS_MODE == BUS_ARBITRATOR

#include <string.h> //mem{move, cpy, cmp}
#include <stdlib.h> //malloc

#include "hll.h"
#include "hll_arbitrator.h"
#include "pdcp.h"

#ifdef CONFIG_USE_MALLOC
struct trienode nodeinfo_byId;
#else
struct nodeinfo nodeinfo_byId[254];
#endif

void
hll_arbdev_init(){
#ifdef CONFIG_USE_MALLOC
	trie_init(&nodeinfo_byId);
#else
	u8 i=254;
	while(i--) nodeinfo_setUnused(&nodeinfo_byId[i]);
#endif
}

/**
 * Respond to an incoming Bind request by sending a response.
 */
static void
respond_bind(struct can_msg *msg){
	struct nodeinfo *taken = NULL;
	_Bool taken_by_us = 0;
	u8 want = msg->id;
	if(want >= 1 && want <= 254){
#ifdef CONFIG_USE_MALLOC
		void **insertPtr = trie_push(&nodeinfo_byId, want);
		if(!insertPtr) goto fail; //ENOMEM
		taken = *insertPtr;
#else
		taken = nodeinfo_lookup(want);
#endif
		if(!taken){
#ifdef CONFIG_USE_MALLOC
			taken = malloc(sizeof(struct nodeinfo));
			if(!taken) goto fail; //ENOMEM
#else
			taken = &nodeinfo_byId[want-1];
#endif
			memcpy(&taken->personality, msg->function_specific, sizeof(struct request_bind));
#ifdef CONFIG_USE_MALLOC
			*insertPtr = taken;
#endif
			taken_by_us = ~0;
		}
	}
	u8 try = want;
	if(!taken_by_us) for(;;){
		if(try==0 || try==255) try=1;
		taken = nodeinfo_lookup(try);
		if(!taken) break;
		if(0 == memcmp(
			&taken->personality,
			msg->function_specific,
			sizeof(struct request_bind)
		)) break; //device already had this id
		if(++try == want) goto fail; //none available
	}
	
	//transform msg into a bind response
	typedef struct request_bind req_t;
	typedef struct respons_bind res_t;
	req_t *req = (req_t*) &msg->function_specific;
	res_t *res = (res_t*) &msg->function_specific;
	msg->len = sizeof(msg->function_code) + sizeof(res_t);
	res->serial_number = req->serial_number;
	res->product_id    = req->product_id;
	res->vendor_id     = req->vendor_id;
	res->node_id = try;
	msg->function_code = RESPONS_BIND;
	msg->id = want | (1 << MESSAGE_PRIORITY);

	hll_msg_push(msg, SOCK_STDOUT);
	return;
fail:
	//TODO: how to fail properly? Send request_suspend?
	hll_msg_free(msg);
}

/**
 * Handles some messages, sorts rest into SOCK_APPLICATION.
 */
void
post_office(struct socket *so){
	struct can_msg *msg = sock_pull(so);

	switch(msg->function_code){
		case REQUEST_BIND:
			respond_bind(msg);
			break;
		case RESPONS_SUSPEND:
		case REQUEST_BEACON:
		case RESPONS_RESET:
			//TODO
		default:
			hll_msg_push(msg, SOCK_APPLICATION);
			return;
	}
	hll_global.notify(msg->function_code);
}

#endif
