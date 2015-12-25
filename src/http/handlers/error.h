/*
 * error.h
 *
 *  Created on: 25 дек. 2015 г.
 *      Author: serge78rus
 */

#ifndef HTTP_HANDLERS_ERROR_H_
#define HTTP_HANDLERS_ERROR_H_

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>

#include <iostream>

namespace http {

class ErrorHandler: public Poco::Net::HTTPRequestHandler
{
public:
	ErrorHandler(Poco::Net::HTTPServerResponse::HTTPStatus);
	void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res);
private:
	const Poco::Net::HTTPServerResponse::HTTPStatus resStatus;
};

inline ErrorHandler::ErrorHandler(Poco::Net::HTTPServerResponse::HTTPStatus status)
		:	resStatus(status)
{
}

inline void ErrorHandler::handleRequest(Poco::Net::HTTPServerRequest& req,
		Poco::Net::HTTPServerResponse& res)
{
	res.setChunkedTransferEncoding(true);
	res.setStatusAndReason(resStatus);
	res.setContentType("text/html");
	std::ostream& os = res.send();
	os << "<html><head><title>" << int(res.getStatus()) << " " << res.getReason()
			<< "</title><body bgcolor=\"white\"><center><h1>"	<< int(res.getStatus())
			<< " " << res.getReason() << "</h1></center><hr/></body></html>";
}

} //namespace http

#endif /* HTTP_HANDLERS_ERROR_H_ */
