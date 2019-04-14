#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H
#include "Request.h"
#include "Reply.h"
class RequestHandler 
{
public:
	explicit RequestHandler(const std::string mdoc_root);
	void handlerRequest(const HttpRequest& req, reply &rep);
	
private:
	bool uriDecode(const std::string in, std::string &out);


	std::string doc_root;



};


#endif // 
