#include <stdio.h>
#include <string.h>

#define STRSIZE 500
#define DEFAULT_PORT "80"
#define INPUT 4

//�O�����������𖞂����Ă��邩��check
int html_check(char* str){

  int i;
  char checking[10];

  for(i=0;i<7;i++){
	checking[i] = str[i];
  }

  char checker[10] = "http://";

  if(strcmp(checking,checker) == 0) return 1;
  else return 0;

}


//port�ԍ���check



int main(){

  char str[STRSIZE] = {};

  printf("Input URL\n");
  fgets(str,STRSIZE,stdin);

  int i;

  if(html_check(str)){
	char asuka[STRSIZE];
	//delete "http://"
	for(i=7;str[i]!='\n';i++){
	  asuka[i-7] = str[i];
	}
	asuka[i]='\0';

	char *slash;
	char *path;
	slash = strtok(asuka, "/");
	path = strtok(NULL, "\n");

	

	char *host;
	char *port_str;
	host = strtok(slash, ":");
	port_str = strtok(NULL, ":");


	//�R��������������A�|�[�g�ԍ��𕶎���̂܂�port_str�Ɋi�[����

	if(port_str!=NULL){
	  int j;
	  for(j = 0 ; port_str[j] != '\0'; j++){
		if(port_str[j] < '0' || port_str[j] > '9') {
		  printf("�|�[�g�ԍ��ɕ����������Ă��܂����B�����I�����܂�\n");//�������O��
		  return -1;
		}
	  }
	}else{
	  port_str=DEFAULT_PORT;
	}
	if((strchr(host,':')!=NULL)||(strchr(port_str,':')!=NULL)||(strchr(path,':')!=NULL)) return 0;



    printf("\n");
	printf("host = %s\n",host);
	printf("port = %s\n",port_str);
	printf("path = %s\n",path);

	
  }

  return 0;
  
}
