/*
 * h_root.h
 *
 *  Created on: 21 дек. 2015 г.
 *      Author: serge78rus
 */

#ifndef H_ROOT_H_
#define H_ROOT_H_

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Logger.h>

namespace http {

class RootHandler: public Poco::Net::HTTPRequestHandler
{
public:
	RootHandler(Poco::Logger &reql, Poco::Logger &resl);
	void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res);
private:
	Poco::Logger &reqLogger;
	Poco::Logger &resLogger;
};

} //namespace http

#endif /* H_ROOT_H_ */
