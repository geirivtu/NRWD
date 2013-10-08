#include <stdio.h>
#include <unistd.h> //sleep
#include <pthread.h>
#include <semaphore.h>

#include "../src/socket.h"

sem_t fill;
struct socket sock_free, sock_stdin, sock_stdout;

void *app(void *arg){
	for(;; sleep(1)){
		sem_wait(&fill);
		struct can_msg *msg = sock_pull(&sock_stdin);
		if(!msg) break; //termination signal
		sock_push(&sock_stdout, msg);
	}
	return NULL;
}

void app_callback(struct socket *sock){
	sem_post(&fill);
}

void hal_print(struct socket *sock){
	struct can_msg *msg = sock_pull(sock);
	fwrite(msg->data, 1, msg->len, stdout);
	fflush(stdout);
	sock_push(&sock_free, msg);
}

int main(){
	sock_init(&sock_free);
	sock_init(&sock_stdin);
	sock_init(&sock_stdout);
	sock_register_recv_hook(&sock_stdin, app_callback);
	sock_register_recv_hook(&sock_stdout, hal_print);
	
	struct canel buf[2];
	buf[0].next = buf+1;
	buf[1].next = NULL;
	sock_free.rd = buf+0;
	sock_free.wr = buf+1;

	sem_init(&fill, 0, 0);
	pthread_t bjarne;
	pthread_create(&bjarne, NULL, app, NULL);

	struct can_msg *msg = NULL;
	for(;;){
		if(!msg){
			msg = sock_pull(&sock_free);
			if(!msg){
				fprintf(stderr, "Full buffer.\n");
				sleep(1);
				continue;
			}
			msg->len = 0;
		}
		if(msg->len >= 8){
			sock_push(&sock_stdin, msg);
			msg = NULL;
			continue;
		}
		int c = fgetc(stdin);
		if(c == EOF) break;

		msg->data[msg->len++] = c;
	}
	
	if(msg){
		if(msg->len)
			sock_push(&sock_stdin, msg);
		else
			sock_push(&sock_free, msg);
	}

	sem_post(&fill); //termination signal
	pthread_join(bjarne, NULL);
	return 0;
}
