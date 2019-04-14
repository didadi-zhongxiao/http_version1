#ifndef REPLY_H
#define REPLY_H
#include<vector>
#include "Request.h"
struct reply
{
	//响应状态码
	enum status_type
	{
		ok = 200,
		created = 201,
		accepted = 202,
		no_content = 204,
		multiple_choices = 300,
		moved_permanently = 301,
		moved_temporarily = 302,
		not_modified = 304,
		bad_request = 400,
		unauthorized = 401,
		forbidden = 403,
		not_found = 404,
		internal_server_error = 500,
		not_implemented = 501,
		bad_gateway = 502,
		service_unavailable = 503
	} status;

	//响应的首部字段
	std::vector<header> headers;

	std::string content;

	std::string toBuffer();
	static reply stock_reply(status_type status);

};

#endif
