/*
 * conf.h
 *
 *  Created on: 21 дек. 2015 г.
 *      Author: serge78rus
 */

#ifndef HTTP_CONF_H_
#define HTTP_CONF_H_

#include <Poco/Util/ConfigurationView.h>

namespace http {

class Conf : public Poco::Util::ConfigurationView {
public:
	Conf(Poco::Util::AbstractConfiguration &src)
			: Poco::Util::ConfigurationView("http", &src)
	{
	}
	~Conf()
	{
	}
};

} //namespace http

#endif /* HTTP_CONF_H_ */
