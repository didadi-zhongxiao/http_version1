#ifndef REQUEST_PARSE_H
#define REQUEST_PARSE_H
#include "Request.h"

class RequestParse
{
public:
	RequestParse(std::string req) :request(req) {};
	bool parse(HttpRequest &req);

	//将http请求以每行的形式保存下来
	bool separate();

	//解析消息行
	bool parseRequest_line(HttpRequest &req);

	//解析消息头
	bool parseRequest_headers(HttpRequest &req);

	//解析消息主体
	bool parseRequest_body(HttpRequest &req,int i);

private:
	std::string request;
	std::vector<std::string> m_lines;
	
	bool is_digit(int c);
};

#endif // !REQUEST_PARSE_H

