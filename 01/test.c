#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SCHEMESIZE 20
#define HOSTSIZE 500
#define PATHSIZE 100
#define STRSIZE 1000
#define PORTSIZE 100

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

  //  printf("i=%d",i);

  if(str[i]!= '\n'){
	i++;//:の分右に
	if(str[i]=='/' && str[i+1] == '/'){
	  i+=2;// //の分だけ右に
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

  printf("入力されたurlは書式を満たしていません\n");
  exit(1);
}



int main(){

  char str[STRSIZE]={};

  printf("Input URL\n");
  fgets(str,STRSIZE,stdin);

  urlcontents using = urlcheck(str);

  if(strcmp(using.scheme,"http") != 0){
	printf("入力されたurlのスキームがhttpでありません\n");
	exit(1);
  }

  printf("\n");
  printf("scheme = %s\n",using.scheme);
  printf("host = %s\n",using.host);
  printf("port = %d\n",using.port);
  printf("path = %s\n",using.path);

  return 0;
}


