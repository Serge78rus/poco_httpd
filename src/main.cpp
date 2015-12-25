//============================================================================
// Name        : poco_httpd.cpp
// Author      : Serge L. Ryadkow
// Version     : 0.1.0
// Copyright   : (C) 2015 by Serge L. Ryadkow
// Description : sample POCO HTTP server
//               based on poco-1.6.1-all/Net/samples/HTTPTimeServer
//============================================================================

#include "server.h"

int main(int argc, char** argv)
{
	Server srv;
	return srv.run(argc, argv);
}
