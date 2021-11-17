#include <stdio.h>      /* for snprintf */
#include "csapp.h"
#include "calc.h"

/* buffer size for reading lines of input from user */
#define LINEBUF_SIZE 1024

struct Calc *calc;
int listenfd;
pthread_mutex_t lock; 

int chat_with_client(void *arg);
void _shutdown();

int main(int argc, char **argv) {
	if(argc != 2){
	    fprintf(stderr, "Usage: ./calcServer <port>\n");
		return -1;	
	}

	listenfd = Open_listenfd(argv[1]);
	if (listenfd == -1 || listenfd == -2) {
		fprintf(stderr, "Error: cannot open listenfd\n");
		return -1;
	}
	
	calc = calc_create();

	pthread_mutex_init(&lock, NULL);
	
	do {
		int conection_request = Accept(listenfd, NULL, NULL);
		if(conection_request < 0) {
			fprintf(stderr, "Error: cannot accept connection request\n");
			return -1;
		}

		pthread_t thread_id;
		pthread_create(&thread_id, NULL, (void *)chat_with_client, (void *)conection_request);
	} while(TRUE);

	return 0;
}

int chat_with_client(void *arg) {
	int infd = (int) arg;

	pthread_detach(pthread_self());

	printf("chat with client %d\n", infd);
	char linebuf[LINEBUF_SIZE];
	char output[LINEBUF_SIZE];

	/*
	 * Read lines of input, evaluate them as calculator expressions,
	 * and (if evaluation was successful) print the result of each
	 * expression.  Quit when "quit" command is received.
	 */
	int done = 0;
	while (!done) {
		memset(linebuf, '\0', sizeof(linebuf));
		ssize_t n = recv(infd, (void*) &linebuf, LINEBUF_SIZE, 0);

		if (n == -1) {
			return TRUE;
		}

		if (n == 0) {
			return TRUE;
		}

		linebuf[n] = '\0';
		char* pch = NULL;
		pch = strtok(linebuf, "\r\n");

		while (pch != NULL)
		{
			if(strcmp(pch, "shutdown\n") == 0 || strcmp(pch, "shutdown\r\n") == 0 || strcmp(pch, "shutdown") == 0) {
				close(infd);
				_shutdown();
				return FALSE;
			}
			
			if (strcmp(pch, "quit\n") == 0 || strcmp(pch, "quit\r\n") == 0 || strcmp(pch, "quit") == 0) {
				/* quit command */
				close(infd);
				return FALSE;
			}

			/* process input line */
			int result = -3;
			int calc_retval = 0;

			pthread_mutex_lock(&lock);
			calc_retval = calc_eval(calc, pch, &result);
			pthread_mutex_unlock(&lock);

			if (calc_retval == 0) {
				sprintf(output, "%s\n", "Error");
				write(infd, output, strlen(output));
			} else {
				/* output result */
				sprintf(output, "%i\n", result);
				write(infd, output, strlen(output));
			}

			pch = strtok(NULL, "\r\n");
		}
	}
	return TRUE;
}

void _shutdown() {
	pthread_mutex_destroy(&lock);
	calc_destroy(calc);
	close(listenfd);
	exit(0);
}
