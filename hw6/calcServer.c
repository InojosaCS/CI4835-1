#include <stdio.h>      /* for snprintf */
#include "csapp.h"
#include "calc.h"

/* buffer size for reading lines of input from user */
#define LINEBUF_SIZE 1024

int chat_with_client(struct Calc *calc, int infd, int outfd);


int main(int argc, char **argv) {
	/* TODO: implement this program */
	if(argc != 2){
	    fprintf(stderr, "Usage: ./calcServer <port>\n");
		return -1;	
	}

	int listenfd = Open_listenfd(argv[1]);
	if (listenfd == -1 || listenfd == -2) {
		fprintf(stderr, "Error: cannot open listenfd\n");
		return -1;
	}
	
	struct Calc *calc = calc_create();
	int open_session = 1;
	
	do {
		int conection_request = Accept(listenfd, NULL, NULL);
		if(conection_request < 0) {
			fprintf(stderr, "Error: cannot accept connection request\n");
			return -1;
		}
		open_session = chat_with_client(calc, conection_request, conection_request);
		close(conection_request);
	} while(open_session);

	calc_destroy(calc);
	close(listenfd);

	return 0;
}

int chat_with_client(struct Calc *calc, int infd, int outfd) {
	char linebuf[LINEBUF_SIZE];
	char output[LINEBUF_SIZE];
	char * input = (char *) malloc(sizeof(char) * LINEBUF_SIZE);

	/*
	 * Read lines of input, evaluate them as calculator expressions,
	 * and (if evaluation was successful) print the result of each
	 * expression.  Quit when "quit" command is received.
	 */
	int done = 0;
	while (!done) {
		ssize_t n = recv(infd, (void*) &linebuf[LINEBUF_SIZE], LINEBUF_SIZE, 0);
		input = linebuf;
		
		if(strcmp(input, "shutdown\n") == 0 || strcmp(input, "shutdown\r\n") == 0) {
			done = 1;
			return FALSE;
		}
		
		if (n <= 0) {
			/* error or end of input */
			done = 1;
		} else if (strcmp(input, "quit\n") == 0 || strcmp(input, "quit\r\n") == 0) {
			/* quit command */
			done = 1;
		} else {
			/* process input line */
			int result;
			if (calc_eval(calc, input, &result) == 0) {
				/* expression couldn't be evaluated */
				rio_writen(outfd, "Error?\n", 7);
				sprintf(output, "%s", linebuf);
				write(infd, output, strlen(output));
			} else {
				/* output result */
				int len = snprintf(linebuf, LINEBUF_SIZE, "%d\n", result);
				if (len < LINEBUF_SIZE) {
					rio_writen(outfd, linebuf, len);
				}
			}
		}
	}
	return TRUE;
}

