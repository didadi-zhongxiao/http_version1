#ifndef THREAD_WORK_H
#define THREAD_WORK_H
#include <pthread.h>
#include <vector>
//pthread_mutex_t mutx;
class ThreadWork
{
public:
	ThreadWork() {};
	ThreadWork(int num);


private:
	int nThreads;
//	int listenfd;
	void threadsMake(int i);
	static void * threadMain(void *arg);
	static void work(int confd,pthread_t pid);
};


#endif // 
