#ifndef __CAN_H
#define __CAN_H

typedef struct can_message_t {
	unsigned int id;
	unsigned int length;
	unsigned char data[8];
} can_message_t;


#define ID_CONTROLLER	0x120
#define ID_SETPOINT		0x121
#define ID_PARAMETER	0x122
#define ID_ERROR		0x100

#define	BRP_VALUE		(F_CPU/125000/16)
#define	SJW_VALUE		1
#define	PROP_SEG		7
#define	PHASE_SEG_1		4
#define	PHASE_SEG_2		4

#define ACCPT_MASK_ID	0b11111111110
#define ACCPT_TAG_ID	0x6
#define ACCPT_MASK_RTR	0
#define ACCPT_TAG_RTR	0
#define ACCPT_MASK_IDE	0
#define ACCPT_TAG_RB0	0

#define	CAN_FRAME_DATA_LENGTH	8
#define	CAN_FRAME_MSG_LENGTH	3
#define	CAN_IDE					0
#define CAN_FRAME_SIZE			(CAN_FRAME_DATA_LENGTH + CAN_FRAME_MSG_LENGTH)

void can_init(void);

void can_transmit(can_message_t *message);

#endif
