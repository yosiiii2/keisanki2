#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define NUMSTR  2

//charのポインタの配列を二つ取る事で、文字列二つを並べてる？
char *reqlines[NUMSTR] = {
  "Request from client\r\n",
  "\r\n" //これなんぞ
};

int main(int argc, char* argv[]){

	FILE *fp;
	char hostname[128];
	int i, s, port;
	struct hostent *hp; //この構造体はどっかで決まってるのだろう
	struct sockaddr_in sin; //この構造体もどっかで決まってるのだろう
	char buf[128];

	//引数の数があってないならはじく(portとhostを指定するはず？なのかな？)
	if(argc <= 2) {
	  perror("host and port required");
	  exit(1);	
	}

	//argv[2]がport番号やから、これが0やったらはじく、と
	if((port = atoi(argv[2])) == 0) {
	  perror("no port");
	  exit(1);
	}

	//gethostbyname #とは
	//nameにはホスト名、ドット区切りのIPv4、コロン区切りのIPv6を指定する
	//んで、hostent構造体を返す
	//hostを名前から取ってくるんやけど、argv[1]がその名前なのかな
	//それがNULL、つまり見つからんかったらunknown hostではじくと
	if ((hp = gethostbyname(argv[1])) == NULL) {
		fprintf(stderr, "%s: unknown host.\n", hostname);
		exit(1);
	}


	//ここ多分決まった形
	//socketはこう書かないといけないのだろう
	//errorのときに-1が返るのかな？
	//socket(domain,type,protocol)で成功したらソケット記述子、失敗したら-1
	//AF_INETは2ホスト間プロセス通信
	//SOCK_STREAMは順次双方向バイトストリーム
	//0は自動設定
	//作ったsocketはcloseで閉じる
	if((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("client socket()");
		exit(1);		
	}


	//bzeroとか知らんのじゃい
	//bzero(void* s,size_t n)で、バイト列sの先頭nバイトを数値0で埋める
	//memsetと同じ感じ(memsetが推奨)
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	//アドレスファミリ.AF_INETで固定されることが多い(?)
	sin.sin_port = htons(port);
	//sin_portにはポート番号がはいる
	//big endianにするためにhtons関数を用いる
	memcpy(&sin.sin_addr, hp->h_addr, hp-> h_length);//hp->h_addrをhp->h_length分sin.sin_addrにコピー
	
	//int connect(int socket, const struct sochaddr *address, size_t address_len)
	//socket::socket()で作成したソケットディスクリプタを指定
	//address::sockadderへのポインタを指定
	//address_length::アドレス構造体のサイズを指定
	//戻り値は成功:0,失敗:-1
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

 
