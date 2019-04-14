#include "RequestParse.h"
#include <algorithm>
#include"iostream"
using namespace std;
bool RequestParse::parse(HttpRequest &req)
{
	bool b, c, d;
	try {
		b = separate();
//		cout<<"separate finish  "<< b <<endl;
		c = parseRequest_line(req);
//		cout<<"parse line finish  "<< c << endl;
		d = parseRequest_headers(req);
//		cout<<"parse headers finish  "<< d <<endl;
	}
	catch (std::out_of_range)
	{
		return false;
	}
	if (b&&c&&d)
		return true;
	else
		return false;
}
bool RequestParse::separate()
{
	int i=0,index = 0;
	if (request.empty())
		return false;
	while(i<request.size())
	{
		//"\r\n"代表换行符，如果索引越界异常，则捕获
		if (request.at(i) == '\r'&&request.at(i + 1) == '\n')
		{
			m_lines.push_back(std::string(request, index, i-index));
			i += 2;
			index = i;
		}
		else
		{
			i++;
		}
	}

	return true;
}

bool RequestParse::parseRequest_line(HttpRequest &req)
{
	std::string requestLine = m_lines.at(0);
	auto methodIter = std::find(requestLine.begin(), requestLine.end(), ' ');
	if (methodIter == requestLine.end())
		return false;
	/*int d;
	d= distance(requestLine.begin(), methodIter);
	std::vector<char> v;
	v.push_back('c');
	v.resize(100);
	std::copy(requestLine.cbegin(), requestLine.cend() ,v.begin());*/
	req.method.resize(requestLine.size());
	req.uri.resize(requestLine.size());
	std::copy(requestLine.begin(), methodIter, req.method.begin());
	auto uriIter = std::find(++methodIter, requestLine.end(), ' ');
	if (uriIter == requestLine.end())
		return false;
	std::copy(methodIter, uriIter, req.uri.begin());
	int majorVersion = 0;
	auto iter = uriIter + 1;
	req.http_version_major = 0;
	req.http_version_minor = 0;
	for (iter; *iter!='.'; iter++)
	{
		if (is_digit(*iter))
			req.http_version_major = req.http_version_major * 10 + (*iter)-'0';
	}
	for (++iter; iter != requestLine.end(); iter++)
	{
		if (is_digit(*iter))
			req.http_version_minor = req.http_version_minor * 10 + (*iter) - '0';
	}
	return true;
}
bool RequestParse::parseRequest_headers(HttpRequest &req)
{
	
	std::string requestHeaders;
	std::string::iterator iter;
	for (int i = 1; i < m_lines.size(); i++)
	{
		requestHeaders = m_lines.at(i);
		if (m_lines.at(i).empty())
		{
		//	if (i < m_lines.size() - 1)
		//	{ 
			//	if (parseRequest_body(req, i))
			//		return true;
			//	else
			//		return false;
		//	}
			return true;
		}
		else
		{
			iter= find(requestHeaders.begin(), requestHeaders.end(), ':');
			if (iter == requestHeaders.end())
				return false;
			req.headers.push_back(header());
			req.headers.back().name.resize(requestHeaders.size());
			req.headers.back().value.resize(requestHeaders.size());
			std::copy(requestHeaders.begin(), iter,
						   	req.headers.back().name.begin());
			if (++iter == requestHeaders.end())
				return false;
			std::copy(iter, requestHeaders.end(), 
							req.headers.back().value.begin());
		}
	}
	return true;
}
bool RequestParse::parseRequest_body(HttpRequest &req, int i)
{
	for (++i; i < m_lines.size(); i++)
	{
		if (m_lines.at(i).empty())
			return false;
		else
		{
			req.body += m_lines.at(i);
		}
	}
	return true;
}

bool RequestParse::is_digit(int c)
{
	return c >= '0' && c <= '9';
}
