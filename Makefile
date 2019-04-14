httpServer: httpServer.o Reply.o RequestHandler.o RequestParse.o ThreadWork.o
	g++ -std=c++11 -lpthread httpServer.o Reply.o RequestHandler.o RequestParse.o ThreadWork.o -o httpServer

httpServer.o: httpServer.cpp ThreadWork.h
	g++ -std=c++11 -lpthread -c httpServer.cpp

Reply.o: Reply.h Reply.cpp
	g++ -std=c++11 -lpthread -c Reply.cpp
	
RequestHandler.o: RequestHandler.cpp RequestHandler.h
	g++ -std=c++11 -lpthread -c RequestHandler.cpp
	
RequestParse.o: RequestParse.cpp RequestParse.h
	g++ -std=c++11 -lpthread -c RequestParse.cpp
	
ThreadWork.o: ThreadWork.h RequestParse.h RequestHandler.h ThreadWork.cpp
	g++ -std=c++11 -lpthread -c ThreadWork.cpp
	
clean:
	rm *.o httpServer
