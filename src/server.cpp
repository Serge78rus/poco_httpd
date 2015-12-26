/*
 * server.cpp
 *
 *  Created on: 18 дек. 2015 г.
 *      Author: serge78rus
 */

#include "http/server.h"

#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Logger.h>

#include <iostream>

#include "server.h"
#include "http/server.h"

using namespace std;

Server::Server()
	: helpRequested(false)
{
	addSubsystem(new http::Server());
}

Server::~Server()
{
}

void Server::initialize(Application& self)
{
	if (confFile.empty()) {
		loadConfiguration(); // load default configuration files, if present
	} else {
		loadConfiguration(confFile);
	}
	ServerApplication::initialize(self);
	poco_information_f1(logger(), "cwd: %s", Poco::Path::current());
}

void Server::uninitialize()
{
	ServerApplication::uninitialize();
}

void Server::defineOptions(Poco::Util::OptionSet& options)
{
	ServerApplication::defineOptions(options);
	options.addOption(
			Poco::Util::Option("help", "h",
					"display help information on command line arguments")
			.required(false)
			.repeatable(false));
	options.addOption(
			Poco::Util::Option("conf", "c",
					"configuration file")
			.required(false)
			.repeatable(false)
			.argument ("filename"));
}

void Server::handleOption(const std::string& name, const std::string& value)
{
	ServerApplication::handleOption(name, value);
	if (name == "help") {
		helpRequested = true;
		stopOptionsProcessing();
	} else if (name == "conf") {
		confFile = value;
	}
}

void Server::displayHelp()
{
	Poco::Util::HelpFormatter hf(options());
	hf.setCommand(commandName());
	hf.setUsage("OPTIONS");
	hf.setHeader("A test web server, based on POCO C++ library.");
	hf.format(std::cout);
}

int Server::main(const std::vector<std::string>& args)
{
	if (helpRequested)	{
		displayHelp();
	}	else	{
		// wait for CTRL-C or kill
		waitForTerminationRequest();
	}
	return Application::EXIT_OK;
}

