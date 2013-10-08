#include <stdio.h>
#include <stddef.h> //offsetof

#include "../src/socket.h"

static struct canel *
canel_of_msg(struct can_msg *mess){
	return (struct canel*) ((char*)mess - offsetof(struct canel, msg));
}

int main(){
	struct canel memory;
	struct canel *outer = &memory;
	struct can_msg *inner = &outer->msg;
	if(outer != canel_of_msg(inner)){
		printf("%p != %p\n", outer, canel_of_msg(inner));
		return 1;
	}
	return 0;
}
