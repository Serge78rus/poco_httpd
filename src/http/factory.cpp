/*
 * factory.cpp
 *
 *  Created on: 21 дек. 2015 г.
 *      Author: serge78rus
 */

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Exception.h>
#include <Poco/File.h>

#include "factory.h"
#include "conf.h"
#include "handlers/file.h"
#include "handlers/error.h"
#include "handlers/info.h"

using namespace std;
using namespace http;

Factory::Factory(Conf &conf)
		: logger(Poco::Logger::get("http.factory")),
			reqLogger(Poco::Logger::get("http.req")),
			resLogger(Poco::Logger::get("http.res")),
			rootDir(conf.getString("root", DEFAULT_ROOT)),
			err404page(conf.getString("error404", "")),
			err500page(conf.getString("error500", "")),
			err501page(conf.getString("error501", ""))
{
	poco_trace(logger, "Factory::Factory()");
	//poco_information_f1(logger, "root: %s", rootDir.toString());
	poco_information_f1(logger, "root: %s", rootDir);
}

Poco::Net::HTTPRequestHandler *Factory::createRequestHandler(
		const Poco::Net::HTTPServerRequest& req)
{
	try {
		string uri = req.getURI();
		string met = req.getMethod();
		if (logger.trace()) {
			string ip = req.clientAddress().toString();
			string ver = req.getVersion();
			poco_trace_f4(logger, "Factory::createRequestHandler() URI: %s met: %s IP: %s ver: %s",
					uri, met, ip, ver);
			for (Poco::Net::HTTPServerRequest::ConstIterator it = req.begin();
					it != req.end(); ++it) {
				poco_trace_f2(logger, "Factory::createRequestHandler() %s: %s", it->first, it->second);
			}
		}
		if (met == "GET") {
			if (uri == "/info") {
				return new InfoHandler(reqLogger, resLogger);
			//else if (uri == ...) {
			} else {
				Poco::Path path(rootDir + uri);
				//poco_information_f1(logger, "path1: %s", path.toString());
				if (path.isDirectory() || path.getExtension().empty()) {
					path = Poco::Path(path, "index.html");
					//poco_information_f1(logger, "path2: %s", path.toString());
				}
				if (Poco::File(path).exists()) {
					return new FileHandler(path.toString(),
							mime.getType(path.getExtension()));
				} else {
					poco_error_f1(logger, "Not found: %s", path.toString());
					return getErrorHandler(Poco::Net::HTTPServerResponse::HTTP_NOT_FOUND,
							err404page);
				}
			}
		} else {
			poco_error_f1(logger, "Bad method: %s", met);
			return getErrorHandler(Poco::Net::HTTPServerResponse::HTTP_NOT_IMPLEMENTED, err501page);
		}
	} catch(Poco::Exception &e) {
		poco_error_f1(logger, "Error: %s", e.displayText());
		return getErrorHandler(Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR, err500page);
	}
}

Poco::Net::HTTPRequestHandler *Factory::getErrorHandler(
		Poco::Net::HTTPServerResponse::HTTPStatus status, const std::string file)
{
	if (file.empty()) {
		return new ErrorHandler(status);
	} else {
		Poco::Path path(rootDir, file);
		return new FileHandler(path.toString(), mime.getType(path.getExtension()), status);
	}
}

