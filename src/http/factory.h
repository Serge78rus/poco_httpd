/*
 * factory.h
 *
 *  Created on: 21 дек. 2015 г.
 *      Author: serge78rus
 */

#ifndef FACTORY_H_
#define FACTORY_H_

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Logger.h>
#include <Poco/Path.h>

#include "mime.h"

namespace http {

class Conf;

class Factory : public Poco::Net::HTTPRequestHandlerFactory {
public:
	Factory(Conf &conf);
	Poco::Net::HTTPRequestHandler *createRequestHandler(
			const Poco::Net::HTTPServerRequest& req);
protected:
	Poco::Net::HTTPRequestHandler *getErrorHandler(Poco::Net::HTTPServerResponse::HTTPStatus status,
			const std::string file = "");
private:
	Poco::Logger &logger;
	Poco::Logger &reqLogger;
	Poco::Logger &resLogger;
	//const Poco::Path rootDir;
	const std::string rootDir;
	Mime mime;
	const std::string err404page;
	const std::string err500page;
	const std::string err501page;
};

} //namespace http

#endif /* FACTORY_H_ */
