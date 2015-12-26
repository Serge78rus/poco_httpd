/*
 * h_root.cpp
 *
 *  Created on: 21 дек. 2015 г.
 *      Author: serge78rus
 */

#include "info.h"

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Process.h>
#include <Poco/Environment.h>
#include <Poco/Net/DNS.h>

using namespace std;
using namespace http;

void InfoHandler::handleRequest(Poco::Net::HTTPServerRequest& req,
		Poco::Net::HTTPServerResponse& res)
{
	poco_trace_f2(reqLogger, "InfoHandler::handleRequest() IP: %s URI: %s",
			req.clientAddress().toString(), req.getURI());

	res.setChunkedTransferEncoding(true);
	res.setContentType("text/html");

	long ut, kt;
	Poco::Process::times(ut, kt);

	ostream& os = res.send();
	os << "<html><head><title>Information</title></head><body>"
			<< "<h1><center>Information page</center></h1>"
			<< "<h2><center>HTTP server powered by POCO C++ Libraries</center></h2><hr/>"
			<< "<table><tbody>"
			<< "<tr><td>OS name:</td><td>" << Poco::Environment::osName() << "</td></tr>"
			<< "<tr><td>OS version:</td><td>" << Poco::Environment::osVersion() << "</td></tr>"
			<< "<tr><td>OS architecture:</td><td>" << Poco::Environment::osArchitecture() << "</td></tr>"
			<< "<tr><td>Node name:</td><td>" << Poco::Environment::nodeName() << "</td></tr>"
			<< "<tr><td>Node ID:</td><td>" << Poco::Environment::nodeId() << "</td></tr>";
	if (Poco::Environment::has("HOME"))
		os << "<tr><td>Home:</td><td>" << Poco::Environment::get("HOME") << "</td></tr>";
	os << "<tr><td>DNS host name:</td><td>" << Poco::Net::DNS::hostName() << "</td></tr>"
			<< "<tr><td>PID:</td><td>" << Poco::Process::id() << "</td></tr>"
			<< "<tr><td>User time:</td><td>" << ut << "</td></tr>"
			<< "<tr><td>Kernel time:</td><td>" << kt << "</td></tr>"
			<< "</tbody></table>"
			<< "<hr/><center><a href=\"/\">home</a></center></body></html>";
}

