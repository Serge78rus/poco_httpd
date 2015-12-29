/*
 * httpd.h
 *
 *  Created on: 21 дек. 2015 г.
 *      Author: serge78rus
 */

#ifndef HTTP_SERVER_H_
#define HTTP_SERVER_H_

#include <Poco/Util/Subsystem.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Logger.h>

namespace http {

const int DEFAULT_PORT = 8888;
const int DEFAULT_MAX_QUEUED = 100;
const int DEFAULT_MAX_THREADS = 16;
const std::string DEFAULT_SOFTWARE_VERSION = "pocohttpd/0.1.1";

class Server : public Poco::Util::Subsystem {
public:
	Server();
	~Server();
	virtual const char *name() const {return "http::Server";}
	virtual void initialize(Poco::Util::Application& app);
	virtual void uninitialize();
private:
	Poco::Net::HTTPServer *server;
	Poco::Logger &logger;
};

} //namespace http

#endif /* HTTP_SERVER_H_ */
