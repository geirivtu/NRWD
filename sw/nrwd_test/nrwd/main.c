/*
 * nrwd_test.c
 *
 * Created: 04.09.2013 14:50:49
 *  Author: Geir
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

/* nrwd includes */
#include "motor.h"
#include "position.h"
#include "current.h"
#include "controller.h"
#include "analog.h"
#include "can.h"


//pdcp includes
#include "config.h"
#include "hal.h"
#include "hll.h"
#include "hll_device.h"
#include "hll_arbitrator.h"
#include <stdio.h> // sprintf


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


		sprintf(tmp,"PID = %x, VID = %x, SID = %x\r",(node->personality.vendor_id),(node->personality.product_id),(node->personality.serial_number));

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
		
#endif

	hll_msg_free(msg);

}


int main(void)
{
	motor_init();
	position_init();
	current_init();
		
	//analog_init();
	
	/* Initialize PDCP */
	hll_init(callback_incoming_can,handled);	//* HLL init
	initLowLevelProtocolHardware();				//* HAL init

	control_set_mode(CONTROL_MODE_ON_OFF);
	
	sei();										//* Turn on interrupts		

	//* DEVICE part
	#if ( CONFIG_BUS_MODE == BUS_DEVICE )
		if(!request_bind(255)){					//* device requests bind
		}
		while(1)
		{
			control_controller();
			_delay_ms(TIMESTEP);
		}
	#endif


}


/* Overcurrent */
ISR(CURRENT_vect)
{
	motor_stop();

	controller_mode_t mode = control_get_mode();
	switch(mode){
		case CONTROL_MODE_ON_OFF:
			/* Set speed to 0 */ 
			control_set_setpoint(0);
			break;
		case CONTROL_MODE_POSITION:
			/* Set target position to current position */
			control_set_setpoint(position_read());
			break;
		
		case CONTROL_MODE_SPEED:
			/* Set speed to 0 */
			control_set_setpoint(0);
			break;
		
		default:
			/* Should not get here */
		
		break;
	}

	_delay_ms(1000);
	
	current_startup();
	motor_start();
}

