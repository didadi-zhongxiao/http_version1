#ifndef REQUEST_PARSE_H
#define REQUEST_PARSE_H
#include "Request.h"

class RequestParse
{
public:
	RequestParse(std::string req) :request(req) {};
	bool parse(HttpRequest &req);

	//��http������ÿ�е���ʽ��������
	bool separate();

	//������Ϣ��
	bool parseRequest_line(HttpRequest &req);

	//������Ϣͷ
	bool parseRequest_headers(HttpRequest &req);

	//������Ϣ����
	bool parseRequest_body(HttpRequest &req,int i);

private:
	std::string request;
	std::vector<std::string> m_lines;
	
	bool is_digit(int c);
};

#endif // !REQUEST_PARSE_H

