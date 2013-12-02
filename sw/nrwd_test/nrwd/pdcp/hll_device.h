/**
 * @file    hll_device.h
 * @brief
 * @details
 * @author  Andreas Nordal @n NTNU in Trondheim (NORWAY)
 * @date    spring 2012
 */

/* This file was automatically generated.  Do not edit! */
#if CONFIG_BUS_MODE == BUS_DEVICE
_Bool request_bind(u8 hint_nodeId);
void respond_bind(struct can_msg *msg);
void post_office(struct socket *so);
void hll_arbdev_init();
#endif
