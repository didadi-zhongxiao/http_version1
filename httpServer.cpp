#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include"ThreadWork.h"
using namespace std;
pthread_mutex_t mutx;
int server_socket;
//mutx=PTHREAD_MUTEX_INITIALIZER;
int main(int argc,char *argv[])
{
	pthread_mutex_init(&mutx,NULL);
	char buf[30]={0};
	if(argc!=2)
	{
		cout<<"usage"<<argv[0]<<"<IP> <port>"<<endl;
		exit(1);
	}
	server_socket=socket(PF_INET,SOCK_STREAM,0);
	if(server_socket==-1)
		cout<<"socket error"<< endl;
	struct sockaddr_in serv_addr;
//	struct sockaddr_in clint_addr;
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
//	serv_addr.sin_port=htons(9190);
	if(bind(server_socket,(struct sockaddr*)&serv_addr,sizeof(serv_addr))
					== -1)
		cout<<"bind error"<<endl;
	if(listen(server_socket,20)== -1)
		cout<<"listen error"<<endl;
	ThreadWork threadwork(6);
//	ThreadWork threadwork(20,server_socket);
	for(;;)
		pause();
//	socklen_t clnt_addr_size;
//	clnt_addr_size=sizeof(clint_addr);
//	int status;
//		close(server_socket);
	return 0;

}


