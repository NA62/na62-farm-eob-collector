//============================================================================
// Name        : na62-farm-control.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Adapter between the farm software and the run control dmi server
//============================================================================

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>

#include "options/MyOptions.h"
#include "MonitorDimServer.h"

using namespace na62::dim;

int main(int argc, char* argv[]) {
	/*
	 * Read program parameters
	 */
	std::cout << "Initializing Options" << std::endl;
	MyOptions::Load(argc, argv);

	char hostName[1024];
	hostName[1023] = '\0';
	if (gethostname(hostName, 1023)) {
		std::cerr << "Unable to get host name! Refusing to start.";
		exit(1);
	}


	na62::dim::MonitorDimServer_ptr dimServer_(
			new MonitorDimServer(std::string(hostName)));

	while(true){
		sleep(1);
	}

	return 0;
}
