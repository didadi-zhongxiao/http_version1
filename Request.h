#ifndef REQUEST_H
#define REQUEST_H
#include <string>
#include <vector>

//消息头中的首部字段
struct header
{
	std::string name;
	std::string value;
};
//解析完成的请求
struct HttpRequest
{
	std::string method;
	std::string uri;
	int http_version_major;
	int http_version_minor;
	std::vector<header> headers;
	std::string body;
};

#endif
