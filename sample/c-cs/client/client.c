#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define NUMSTR  2

char *reqlines[NUMSTR] = {
  "Request from client\r\n",
  "\r\n"
};

int main(int argc, char* argv[])
{
	FILE *fp;
	char hostname[128];
	int i, s, port;
	struct hostent *hp;
	struct sockaddr_in sin;
	char buf[128];

	if(argc <= 2) {
	  perror("host and port required");
	  exit(1);		
	}

	if((port = atoi(argv[2])) == 0) {
	  perror("no port");
	  exit(1);
	}

	if ((hp = gethostbyname(argv[1])) == NULL) {
		fprintf(stderr, "%s: unknown host.\n", hostname);
		exit(1);
	}

	if((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("client socket()");
		exit(1);		
	}

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	memcpy(&sin.sin_addr, hp->h_addr, hp-> h_length);
	
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) == -1) {
		perror("client connect()");
		exit(1);	
	}
	
	fp = fdopen(s, "r");
	
	// send request to server
	for(i = 0; i < NUMSTR; i++) {
	  send(s, reqlines[i], strlen(reqlines[i]), 0);
	}

	// receive contents from server
	while (fgets(buf, sizeof(buf), fp) != NULL) {
	  printf("%s", buf);
	}
	
	close(s);
	return 0;
}

 
