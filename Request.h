#ifndef REQUEST_H
#define REQUEST_H
#include <string>
#include <vector>

//��Ϣͷ�е��ײ��ֶ�
struct header
{
	std::string name;
	std::string value;
};
//������ɵ�����
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
