#include "RequestHandler.h"
#include <string>
#include <sstream>
#include <fstream>
RequestHandler::RequestHandler(std::string mdoc_root)
	:doc_root(mdoc_root) {}

void RequestHandler::handlerRequest(const HttpRequest& req, reply &rep)
{
	std::string request_path;
	if (!uriDecode(req.uri, request_path))
	{
		rep = reply::stock_reply(reply::bad_request);
		return;
	}
	if (request_path.empty() || request_path[0] != '/')
	{
		rep = reply::stock_reply(reply::bad_request);
		return;
	}
	if (request_path[request_path.size() - 1] == '/')
		request_path += "index.html";
	std::string path = doc_root.append(request_path);
	std::ifstream ifs(path, std::ios_base::in | std::ios_base::binary);
	if (!ifs)
	{
		rep = reply::stock_reply(reply::not_found);
		return;
	}
	rep.status = reply::ok;
	char buf[512] = {0};
	while (ifs.read(buf, sizeof(buf)).gcount() > 0)
		rep.content.append(buf, ifs.gcount());
	rep.headers.resize(2);
	char contentbuf[32];
//	sprintf_s(contentbuf, 32, "%d", rep.content.size());
	sprintf(contentbuf, "%d", rep.content.size());
	rep.headers[0].name = "Content-Length";
	rep.headers[0].value = contentbuf;
	rep.headers[1].name = "Content-Type";
	rep.headers[1].value = "text/html";
}

bool RequestHandler::uriDecode(const std::string in, std::string &out)
{
	out.clear();
	out.reserve(in.size());
	for (int i = 0; i < in.size(); i++)
	{
		if (in[i] == '%')	//数据经过加密了，需要解密
		{
			int value = 0;
			if (i + 3 <= in.size())
			{
				std::istringstream is(in.substr(i + 1, 2));
				if (is >> std::hex >> value)
				{
					i += 2;
					out += static_cast<char>(value);
				}
				else
					return false;
			}
			else
				return false;
		}
		else if (in[i] == '+')
			out += ' ';
		else
			out += in[i];
	}
	return true;
}
