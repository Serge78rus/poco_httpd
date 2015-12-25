/*
 * server.h
 *
 *  Created on: 18 дек. 2015 г.
 *      Author: serge78rus
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <Poco/Util/ServerApplication.h>

class Server: public Poco::Util::ServerApplication {
public:
	Server();
	~Server();
protected:
	void initialize(Application& self);
	void uninitialize();
	void defineOptions(Poco::Util::OptionSet& options);
	void handleOption(const std::string& name, const std::string& value);
	void displayHelp();
	int main(const std::vector<std::string>& args);
private:
	bool helpRequested;
	std::string confFile;
};

#endif /* SERVER_H_ */
