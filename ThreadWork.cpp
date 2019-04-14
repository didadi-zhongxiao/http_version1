#include "ThreadWork.h"
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include "RequestParse.h"
#include "RequestHandler.h"
#include<string>
#include"iostream"
extern pthread_mutex_t mutx;
extern int server_socket;
ThreadWork::ThreadWork(int num) :nThreads(num)
{
	for (int i{}; i < nThreads; i++)
		threadsMake(i);
}
void ThreadWork::threadsMake(int i)
{
	pthread_t pid;
	pthread_create(&pid, NULL, &threadMain,(void*)pid);
	return;
}
void *ThreadWork::threadMain(void *arg)
{
	int confd;
	socklen_t client_size;
	struct sockaddr_in clitaddr;
	pthread_t pid=(pthread_t)arg;
	for(;;)
	{
		client_size = sizeof(clitaddr);
		pthread_mutex_lock(&mutx);
		confd = accept(server_socket,(struct sockaddr*)&clitaddr,
				   	&client_size);
		pthread_mutex_unlock(&mutx);
//		std::cout<<"connection accept"<<confd
//				<<"thread pid:"<<pid<<std::endl;
		work(confd,pid);
		close(confd);
	}
}
void ThreadWork::work(int confd,pthread_t pid)
{
//	write
	if(confd<=0)
		return;
	char buf[1024] = { 0 };
	int strlen = read(confd, buf, 1024);
	if (strlen <= 0)
	{
//		std::cout<<"pid:"<<pid<<"strlen = 0\n";
		return ;
	}
	else
	{
//		std::cout<<"pid"<<pid<<"read : "<<strlen<<"character\n";
		buf[strlen] = '\0';
		RequestParse requestparse(buf);
		HttpRequest hRequest;
		reply rep;
//		std::cout<<"pid:"<<pid<<"parse construct finished"<<std::endl;
//		std::cout<<"read buf:"<<buf<<std::endl;
		if (!requestparse.parse(hRequest))
		{
			rep = reply::stock_reply(reply::bad_request);
	//		std::cout<<"badrequest\n";
		}
		else
		{
	//		std::cout<<"parse finished\n";
			RequestHandler reqHandler("/root/test/http/http");
			reqHandler.handlerRequest(hRequest, rep);
		}
		std::string str=rep.toBuffer();
//		std::string buf;
		std::string buf=str+rep.headers[0].name+": "+
				rep.headers[0].value+"\r\n"+rep.headers[1].name+": "+
				rep.headers[1].value+"\r\n\r\n"+rep.content;
		int writelen=buf.size();
//		char *buf;
//		sprintf(buf,"%s\r\n%s: %s\r\n%s: %s\r\n\r\n%s",str,
//			rep.headers[0].name,rep.headers[0].value,rep.headers[1].name,
//			rep.headers[1].value,rep.content);
//		int writelen=buf.size();

//		int writelength=rep.content.size()+rep.headers[0].name.size()+
//				rep.headers[0].value.size()+rep.headers[1].value.size()+
//				rep.headers[1].name.size();
//		std::cout<<"content:"<<rep.content<<"\n";
		int len = write(confd,buf.c_str(), writelen);
//		std::cout<<"writelen:"<<writelen<<"len :"<<len<<"\n";
//		std::cout<<"buf:"<<buf<<std::endl;
		close(confd);
	}
}
