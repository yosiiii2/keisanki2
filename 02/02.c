#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define SCHEMESIZE 20
#define HOSTSIZE 500
#define PATHSIZE 100
#define STRSIZE 1000
#define PORTSIZE 100
#define NUMSTR 3

typedef struct {
  char scheme[SCHEMESIZE];
  char host[HOSTSIZE];
  char portstr[PORTSIZE];
  int port;
  char path[PATHSIZE];

} urlcontents;



urlcontents urlcheck(char* str){

  urlcontents hoge;
  int i=0;
  int j=0;
  int k=0;
  int l=0;

  while(str[i]!='\n'&&str[i]!=':'){
	hoge.scheme[i]=str[i];
	i++;
  }//copy the scheme
  hoge.scheme[i]='\0';

  if(str[i]!= '\n'){
	i++;//:‚Ì•ª‰E‚É
	if(str[i]=='/' && str[i+1] == '/'){
	  i+=2;// //‚Ì•ª‚¾‚¯‰E‚É
	  while(str[i]!='/' && str[i]!=':' && str[i]!='\n'){
		hoge.host[j]=str[i];
		j++;i++;
	  }
	  if(str[i]==':'){
		i++;
		while(str[i]>='0'&&str[i]<='9'){
		  hoge.portstr[k]=str[i];
		  k++; i++;
		}
		hoge.portstr[k]='\0';
	  }if(str[i]=='/'){
		i++;
		while(str[i]!='\n'&&str[i]!=':'){
		  hoge.path[l] = str[i];
		  i++; l++;
		}
		hoge.path[l]='\0';
	  }if(str[i]=='\n'){
		if(k) hoge.port=atoi(hoge.portstr);
		else hoge.port=80;
	   
		if(l==0) strcpy(hoge.path,"None");

		return hoge;
	  }
	}
  }

  printf("“ü—Í‚³‚ê‚½url‚Í‘Ž®‚ð–ž‚½‚µ‚Ä‚¢‚Ü‚¹‚ñ\n");
  //  exit(1);
  hoge.port = -1;
  return hoge;
}

int main(){
  FILE *fp;
  int i, s;
  struct hostent *hp;
  struct sockaddr_in sin;
  char buf[STRSIZE];
  char str[STRSIZE] = {};
  char reqline[STRSIZE];
  char reqhead[STRSIZE];

  urlcontents using;

  while(1){
	while(1){
	  printf("Input URL\n");
	  printf("end‚ÅI—¹\n");
	  fgets(str,STRSIZE,stdin);

	  if(strcmp(str,"end\n") == 0) exit(0);

	  using = urlcheck(str);
	  if(using.port != -1) break;
	}

	
	if ((hp = gethostbyname(using.host)) == NULL) {
	  fprintf(stderr, "%s: unknown host.\n", using.host);
	  exit(1);
	}

	if((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	  perror("client socket()");
	  exit(1);		
	}

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;

	sin.sin_port = htons(using.port);
	memcpy(&sin.sin_addr, hp->h_addr, hp-> h_length);
	
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) == -1) {
	  perror("client connect()");
	  printf( "%s\n", strerror( errno ) );
	  exit(1);	
	}
	
	fp = fdopen(s, "r");

	sprintf(reqline,"GET /%s HTTP/1.1\r\n",using.path);
	sprintf(reqhead,"Host: %s\r\n",using.host);

	char *reqlines[NUMSTR] = {
	  reqline,
	  reqhead,
	  "\r\n"
	};

	for(i = 0; i < NUMSTR; i++) {
	  send(s, reqlines[i], strlen(reqlines[i]), 0);
	}

	while (fgets(buf, sizeof(buf), fp) != NULL) {
	  printf("%s", buf);
	}

   	close(s);

  }

  return 0;
}

 
