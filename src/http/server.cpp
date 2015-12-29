/*
 * httpd.cpp
 *
 *  Created on: 21 дек. 2015 г.
 *      Author: serge78rus
 */

#include <Poco/Util/Application.h>

#include <Poco/ThreadPool.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/ServerSocket.h>

#include <iostream>

#include "server.h"
#include "factory.h"
#include "conf.h"

using namespace std;
using namespace http;

Server::Server()
		:	logger(Poco::Logger::get("http"))
{
}

Server::~Server()
{
}

//virtual
void Server::initialize(Poco::Util::Application& app)
{
	poco_trace(logger, "Server::initialize()");

	Conf conf(app.config());
	unsigned short port = (unsigned short)conf.getInt("port", DEFAULT_PORT);
	int maxQueued  = conf.getInt("maxQueued", DEFAULT_MAX_QUEUED);
	int maxThreads = conf.getInt("maxThreads", DEFAULT_MAX_THREADS);
	string softwareVersion = conf.getString("softwareVersion", DEFAULT_SOFTWARE_VERSION);

	Poco::ThreadPool::defaultPool().addCapacity(maxThreads);

	Poco::Net::HTTPServerParams* pars = new Poco::Net::HTTPServerParams;
	pars->setMaxQueued(maxQueued);
	pars->setMaxThreads(maxThreads);
	pars->setSoftwareVersion(softwareVersion);

	poco_information_f1(logger, "port: %hu", port);
	poco_information_f1(logger, "maxQueued: %i", pars->getMaxQueued());
	poco_information_f1(logger, "maxThreads: %i", pars->getMaxThreads());
	poco_information_f1(logger, "softwareVersion: %s", pars->getSoftwareVersion());

	server = new Poco::Net::HTTPServer(new Factory(conf), port, pars);
	server->start();
}

//virtual
void Server::uninitialize()
{
	poco_trace(logger, "Server::uninitialize()");

	server->stop();
	delete server;
}


