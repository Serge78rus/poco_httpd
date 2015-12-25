/*
 * mime.h
 *
 *  Created on: 25 дек. 2015 г.
 *      Author: serge78rus
 */

#ifndef HTTP_MIME_H_
#define HTTP_MIME_H_

#include <string>
#include <map>

namespace http {

class Mime : protected std::map<std::string, std::string> {
public:
	Mime();
	std::string &getType(const std::string &ext);
private:
	std::map<std::string, std::string> data;
	static const char *src[][2];
};

inline std::string &Mime::getType(const std::string &ext)
{
	return at(ext);
}

} //namespace http

#endif /* HTTP_MIME_H_ */
