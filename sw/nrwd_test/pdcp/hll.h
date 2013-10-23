/**
 * @file    hll.h
 * @brief
 * @details
 * @author  Andreas Nordal @n NTNU in Trondheim (NORWAY)
 * @date    spring 2012
 */

#ifndef HLL_H_
#define HLL_H_
#include "pdcp.h"
#include "socket.h"

enum {
	SOCK_FREE,
	SOCK_STDOUT,
	SOCK_STDIN,
	SOCK_APPLICATION,
	//These are all sockets in hll (others may exist elsewhere)
	SOCK_TOT_HLL
};

typedef void (*hll_handled_hook)(u8);

struct hll{
	struct socket sock[SOCK_TOT_HLL];
	struct canel canbuf[CONFIG_NUM_CANMSG];
	hll_handled_hook notify;
};

extern struct hll hll_global;

typedef u8 socknum_t;

void hll_msg_free(struct can_msg *msg);
void hll_msg_commit(struct can_msg *msg);
struct can_msg *hll_msg_get(void);
struct can_msg *hll_msg_alloc(void);
void hll_msg_push(struct can_msg *msg,socknum_t);
struct can_msg *hll_msg_pull(socknum_t);
void hll_init(sock_recv_hook, hll_handled_hook);

#endif
