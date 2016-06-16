#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define SCHEMESIZE 20
#define STRSIZE 1000
#define NUMSTR  3
#define BUFSIZE 20

int not_atoi(char* str){
  int i = 0;
  while(str[i] != '\0' && str[i] != '\n'){
	//	printf("%c\n",str[i]);
	if(str[i] <  '0' || str[i] > '9' ) return 0;
	i++;
  }

  return atoi(str);

}



int main(int argc, char* argv[]){
  FILE *fp,*fp2;
  int i, s, ns, port,status_code;
  struct sockaddr_in sin, fsin;
  char buf[BUFSIZE][STRSIZE];
  char *path;	
  char header[STRSIZE];
  char *reason;
  char mediaType[STRSIZE] ;
  char *subtype;
  char statusLine[STRSIZE];
  char str[STRSIZE];
  
  socklen_t fromlen = sizeof(struct sockaddr_in);
  
  if((argc <= 1) || ((port = not_atoi(argv[1])) == 0)) {
	perror("no port number");
	exit(1);		
	}
  
  if((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	perror("client socket()");
	exit(1);		
  }
	
  bzero(&sin, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  
  if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) == -1) {
	  perror("server bind()");
	  exit(1);	
  }
	
  if (listen(s, 128) == -1) {
	perror("server listen()");
	exit(1);	
	}
  
  if ((ns = accept(s, (struct sockaddr *)&fsin, &fromlen)) == -1) {
	perror("server accept()");	
	exit(1);
	}
  
  fp = fdopen(ns, "r");
  
  // receive requests from client (until an empty line)
  for(i = 0 ;(fgets(buf[i], sizeof(buf[i]), fp) != NULL) && i < BUFSIZE ; i++) {
	if(strcmp(buf[i],"\r\n") == 0) break;
	/* printf("%s", buf[i]);//debug */
	}
  
  //受け取った命令列は、buf[n]に格納された
  //これを解析してうまいことしよう
  
  
  //host部は、ここまで届いてる時点で読み捨てていいよね
  //これpath部だけ拾えば良いのでは???
  
  path = strtok(buf[0]," ");
  path = strtok(NULL," ");
  //  printf("%s",path);
  //sprintf(path,".%s",path);
  path++;
  
  //responseの文字列の作成
  //status-line
  //status-code
  //reason-phrase
  
  
  /* ファイルのオープン */
  if((fp2 = fopen(path, "r")) == NULL){
	status_code = 404;
	reason = "Not Found";
  }else{
	status_code = 200;
	reason = "OK";
  }

  sprintf(statusLine, "HTTP/1.1 %d %s \r\n",status_code,reason );
  //status_lineまで完成

  //entity-header

  subtype = "html";
  //これどうしよう
  
  sprintf(mediaType,"text/%s",subtype);

  sprintf(header,"Content-Type: %s \r\n",mediaType);
  
  
  // send contents to client
  send(ns,statusLine,strlen(statusLine),0);
  send(ns,header,strlen(header),0);

  while(fgets(str,sizeof(str),fp2) != NULL){
	send(ns,str,strlen(str),0);
	}
  
  fclose(fp);
  fclose(fp2);  

  
  close(ns);
  close(s);
  
  return 0;
}

