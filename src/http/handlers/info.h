/*
 * h_root.h
 *
 *  Created on: 21 дек. 2015 г.
 *      Author: serge78rus
 */

#ifndef H_ONFO_H_
#define H_INFO_H_

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Logger.h>

namespace http {

class InfoHandler: public Poco::Net::HTTPRequestHandler
{
public:
	InfoHandler(Poco::Logger &reql, Poco::Logger &resl);
	void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res);
private:
	Poco::Logger &reqLogger;
	Poco::Logger &resLogger;
};

inline InfoHandler::InfoHandler(Poco::Logger &reql, Poco::Logger &resl)
		:	reqLogger(reql),
			resLogger(resl)
{
}

} //namespace http

#endif /* H_INFO_H_ */
