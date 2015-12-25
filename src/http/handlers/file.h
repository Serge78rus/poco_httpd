/*
 * file.h
 *
 *  Created on: 24 дек. 2015 г.
 *      Author: serge78rus
 */

#ifndef HTTP_HANDLERS_FILE_H_
#define HTTP_HANDLERS_FILE_H_

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>

namespace http {

class FileHandler: public Poco::Net::HTTPRequestHandler
{
public:
	FileHandler(const std::string &path, const std::string &type,
			Poco::Net::HTTPServerResponse::HTTPStatus = Poco::Net::HTTPServerResponse::HTTP_OK);
	void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res);
private:
	const std::string filePath;
	const std::string mimeType;
	const Poco::Net::HTTPServerResponse::HTTPStatus resStatus;
};

inline FileHandler::FileHandler(const std::string &path, const std::string &type,
		Poco::Net::HTTPServerResponse::HTTPStatus status)
		:	filePath(path),
			mimeType(type),
			resStatus(status)
{
}

inline void FileHandler::handleRequest(Poco::Net::HTTPServerRequest& req,
		Poco::Net::HTTPServerResponse& res)
{
	res.setChunkedTransferEncoding(true);
	if (resStatus != Poco::Net::HTTPServerResponse::HTTP_OK)
		res.setStatusAndReason(resStatus);
	res.sendFile(filePath, mimeType);
}

} //namespace http

#endif /* HTTP_HANDLERS_FILE_H_ */
