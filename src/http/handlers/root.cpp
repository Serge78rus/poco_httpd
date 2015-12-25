/*
 * h_root.cpp
 *
 *  Created on: 21 дек. 2015 г.
 *      Author: serge78rus
 */

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include "root.h"

using namespace std;
using namespace http;

RootHandler::RootHandler(Poco::Logger &reql, Poco::Logger &resl)
		:	reqLogger(reql),
			resLogger(resl)
{
}

void RootHandler::handleRequest(Poco::Net::HTTPServerRequest& req,
		Poco::Net::HTTPServerResponse& res)
{
	poco_trace_f2(reqLogger, "RootHandler::handleRequest() IP: %s URI: %s",
			req.clientAddress().toString(), req.getURI());

	res.setChunkedTransferEncoding(true);
	res.setContentType("text/html");

	ostream& os = res.send();
	os << "<html><head><title>HTTPServer powered by POCO C++ Libraries</title>";
	//os << "<meta http-equiv=\"refresh\" content=\"1\"></head>";
	os << "<body><p style=\"text-align: center; font-size: 48px;\">";
	os << "Test page";
	os << "</p></body></html>";
}

