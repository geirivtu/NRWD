/**
 * @file    pdcp.h
 * @brief
 * @details
 * @author  Andreas Nordal @n NTNU in Trondheim (NORWAY)
 * @date    spring 2012
 */

#ifndef PDCP_H_
#define PDCP_H_

#include "types.h"

#define MESSAGE_PRIORITY 9
#define MESSAGE_MODE     8

#define RESPCODE_FAILURE 0
#define RESPCODE_SUCCESS 1

/*
 * Naming convention
 * 1) Names are taken from the "Function Codes" section of the PDCP protocol spec.
 * 2) All names start with either "request_" or "respons_", or the uppercase equivalents.
 *    This is not valid English, but prefixes of equal length are beautyful.
 *    Prefixes are a poor man's namespace, and as opposed to suffixes, is a big-endian
 *    naming convention, which is both logical and beautyful.
 * 3) To keep names short, omit "device" and the request/response suffix.
 */

enum{
	REQUEST_BIND                             = 0x01,
	RESPONS_BIND                             = 0x81,
	REQUEST_GET_INFO                         = 0x02,
	RESPONS_GET_INFO                         = 0x82,
	REQUEST_GET_PARAMETER                    = 0x03,
	RESPONS_GET_PARAMETER                    = 0x83,
	REQUEST_SET_PARAMETER                    = 0x04,
	RESPONS_SET_PARAMETER                    = 0x84,
	REQUEST_SUSPEND                          = 0x08,
	RESPONS_SUSPEND                          = 0x88,
	REQUEST_RELEASE                          = 0x09,
	RESPONS_RELEASE                          = 0x89,
	REQUEST_BEACON                           = 0x0A,
//	RESPONS_BEACON                           = 0x8A, undefined
	REQUEST_RESET                            = 0x0B,
	RESPONS_RESET                            = 0x8B,
	REQUEST_CONFIGURE_GET_BULK_DATA_TRANSFER = 0x0C,
	RESPONS_CONFIGURE_GET_BULK_DATA_TRANSFER = 0x8C,
	REQUEST_CONFIGURE_SET_BULK_DATA_TRANSFER = 0x0D,
	RESPONS_CONFIGURE_SET_BULK_DATA_TRANSFER = 0x8D,
	REQUEST_BULK_DATA_TRANSFER               = 0x0E,
	RESPONS_BULK_DATA_TRANSFER               = 0x8E,
	REQUEST_UPDATE_DATA_CHANNEL              = 0x0F,
	RESPONS_UPDATE_DATA_CHANNEL              = 0x8F
};

/*
 * Multibyte fields are little endian, according to
 * "Function Code Implementation Examples" of the PDCP spec.
 */

struct request_bind{
	u16 vendor_id;
	u16 product_id;
	u16 serial_number;
};

struct respons_bind{
	u8 node_id;
	u16 vendor_id;
	u16 product_id;
	u16 serial_number;
};

struct request_get_parameter{
	u8 parameter_id;
	u8 channel_index;
};

struct respons_get_parameter{
	u8 response_code;
	u8 parameter_id;
	u8 channel_index;
	u8 parameter_value[4];
};

struct request_set_parameter{
	u8 parameter_id;
	u8 channel_index;
	u8 parameter_value[4];
};

struct respons_set_parameter{
	u8 response_code;
	u8 parameter_id;
	u8 channel_index;
	u8 parameter_value[4];
};

struct request_suspend{
	u16 time_msec;
};

struct respons_suspend{
	u8 response_code;
	u16 time_msec;
};

struct request_release{};

struct respons_release{
	u8 response_code;
};

struct request_beacon{};

struct request_reset{};

struct respons_reset{
	u8 response_code;
};

struct request_configure_get_bulk_data_transfer{
	u8 parameter_id;
	u8 channel_index;
};

struct respons_configure_get_bulk_data_transfer{
	u8 response_code;
	u8 parameter_id;
	u8 channel_index;
	u16 bulk_data_size;
};

struct request_configure_set_bulk_data_transfer{
	u8 parameter_id;
	u8 channel_index;
	u16 bulk_data_size;
};

struct respons_configure_set_bulk_data_transfer{
	u8 response_code;
	u8 parameter_id;
	u8 channel_index;
	u16 bulk_data_size;
};

struct request_bulk_data_transfer{
	u8 packet_id;
	u8 bulk_data[6];
};

struct respons_bulk_data_transfer{
	u8 response_code;
};

struct respons_update_data_channel{
	u8 channel_index;
};

struct request_update_data_channel{
	u8 response_code;
	u8 channel_index;
};

#endif
