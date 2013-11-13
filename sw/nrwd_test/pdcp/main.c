/*
 * This file is in public domain.
 * The source code herein is used for testing,
 * is expected to be replaced by the application implementor's own,
 * and may be freely used as examples for that purpose.
 */

/**
 * @file		main.c
 * @brief		Simple main function for PDCP for AVR testing
 *
 * @author		Andreas Nordal		( NTNU )
 *				Andrzej Zamojski  	( NTNU )
 * @date		spring 2012
 */


/* Includes */
#include "config.h"
#include "hal.h"
#include "hll.h"
#include "hll_device.h"
#include "hll_arbitrator.h"
#include <stdio.h> // sprintf



/* Variables for time measuring - in testing */
volatile uint16_t time;
volatile uint8_t flag;




 /* handled ==================================================== */
 /**
 * @fn 		void handled(u8 function_code)
 * @brief  	Callback function from HLL
 */
void handled(u8 function_code){


#if (CONFIG_BUS_MODE == BUS_ARBITRATOR)
	struct nodeinfo *node;
	nodeinfo_iterator it;

	node = nodeinfo_iterator_begin(&it, 254);
	
	for(; node; node = nodeinfo_iterate(&it)){
		char tmp[40];
		sprintf(tmp,"Node number %d: ",it.index);
		//printUsart(tmp);

		sprintf(tmp,"PID = %x, VID = %x, SID = %x\r",(node->personality.vendor_id),(node->personality.product_id),(node->personality.serial_number));
		//printUsart(tmp);
		//printUsart("\rBinding completed\r");
	}

#elif (CONFIG_BUS_MODE == BUS_DEVICE)
		switch(function_code){
			case 0:
				function_code +=4; //Debug
			break;
		}
#endif


}



 /* callback_incoming_can ==================================== */
 /**
 * @fn 		void callback_incoming_can(struct socket *so)
 * @brief  	Callback function from HLL
 */
void callback_incoming_can(struct socket *so){
	
	struct can_msg *msg = sock_pull(so);

#if CONFIG_BUS_MODE == BUS_DEVICE

		
	switch(msg->function_code){

	case REQUEST_BIND:
	
	break;
	case RESPONS_BIND:
	
	break;
	case REQUEST_GET_INFO:
	
	break;
	case RESPONS_GET_INFO :
	
	break;
	case REQUEST_GET_PARAMETER:
	
	break;
	case RESPONS_GET_PARAMETER:
	
	break;
	case REQUEST_SET_PARAMETER:
	
	break;
	case RESPONS_SET_PARAMETER:
	
	break;
	case REQUEST_SUSPEND:
	
	break;
	
	default:
		/* Function code not implemented */
	
	break;
	}
		
	//printUsart("DEVICE received msg\r");
#endif

	hll_msg_free(msg);

}




 /* main ==================================================== */
 /**
 * @fn 		int main()
 * @brief  	Main function
 */
int main(){
	
	hll_init(callback_incoming_can,handled);	//* HLL init
	initLowLevelProtocolHardware();				//* HAL init
	sei();										//* Turn on interrupts		


	//* DEVICE part
	#if ( CONFIG_BUS_MODE == BUS_DEVICE )
		if(!request_bind(255)){					//* device requests bind
			//printUsart("Failed to send bind request.\r");
		}
		while(1){
		}
	#endif
	
	return 0;
}
