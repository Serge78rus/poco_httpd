/*
 * httpd.h
 *
 *  Created on: 21 дек. 2015 г.
 *      Author: serge78rus
 */

#ifndef HTTPD_H_
#define HTTPD_H_

#include <Poco/Util/Subsystem.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Logger.h>

namespace http {

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

#endif /* HTTPD_H_ */
