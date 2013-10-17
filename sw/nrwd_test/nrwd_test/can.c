#include <avr/io.h>
#include <avr/interrupt.h>

#include "can.h"


void can_init(void)
{
	/* Resetting CAN-controller */
	CANGCON = (1<<SWRES);

	/* CAN baud rate 125000 with 16MHz crystal */
	CANBT1 = ((BRP_VALUE - 1) << 1);
	CANBT2 = ((SJW_VALUE - 1) << 5) | ((PROP_SEG - 1) << 1);
 	CANBT3 = ((PHASE_SEG_2 - 1) << 4) | ((PHASE_SEG_1 - 1) << 1) | 1;
	
	CANTIM = 0;
	CANTTC = 0;


	CANHPMOB = 0; //??
	/* Prescaler for the CAN timer. */
	CANTCON = 0;

	/* Switch to Mob 0 (Transmit) */
	CANPAGE = (0<<4);
	CANSTMOB = 0;

	/* Switch to Mob 1 (Receive) */
	CANPAGE = (1<<4);
	/* CAN MOb status register */
	CANSTMOB = 0;

	/* Identifier Masking */
	CANIDM4 = (ACCPT_MASK_RTR << 2) | ACCPT_MASK_IDE;	// 0x00;
	CANIDM2 = (ACCPT_MASK_ID << 5) & 0xFF;				// 0x00;
	CANIDM1 = (ACCPT_MASK_ID >> 3) & 0xFF;				// 0x00;

	/* Identifier Tags */
	CANIDT4 = (ACCPT_TAG_RTR << 2) | ACCPT_TAG_RB0;		// 0x00;
	CANIDT2 = (ACCPT_TAG_ID << 5) & 0xFF;				// 0x00;
	CANIDT1 = (ACCPT_TAG_ID >> 3) & 0xFF;				// 0x00;

	/* Enable reception */
	CANCDMOB = (1<<CONMOB1) | CAN_IDE; //CAN_IDE = 0

	/* Enable Mob 0 and Mob 1 */
	CANEN2 = (1<<ENMOB1) | (1<<ENMOB0); //Read only register?

	/* Enable interrupt on Mob 0 and Mob 1 */
	CANIE2 = (1<<ENMOB1) | (1<<ENMOB0);

	/* Enable interrupt on RX and TX */
	CANGIE = (1<<ENIT) | (1<<ENRX);

	/* Enable CAN controller */
	CANGCON = (1<<ENASTB);
}

void can_transmit(can_message_t *message)
{
	/* Disabling interrupt */
	CANGIE &= ~(1<<ENIT);

	/* Selecting MOb 0 (transmitting) */
	CANPAGE = (0<<4);

	/* Writing message id */
	CANIDT1	= ((message->id) >> 3);
	CANIDT2 = ((message->id) << 5);

	/* Writing data to message */
	for (int i = 0; i < (message->length); i++) {
		CANMSG = ((message->data[i]) >> (i*8));
	}

	/* Enabling transmission, interrupt and selecting MOb 1 (receiving) */
	CANCDMOB = (1<<CONMOB0) | CAN_IDE | (message->length);
	CANGIE |= (1<<ENIT);
	CANPAGE = (1<<4);
}
