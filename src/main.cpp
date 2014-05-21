//============================================================================
// Name        : na62-farm-eob-collector
// Author      : 
// Version     :
// Description : Program collecting all kind of DC S data after each EOB
//============================================================================

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>

#include "EobListener.h"
#include "RegistryHandler.h"
#include "options/MyOptions.h"

using namespace na62::dim;

int main(int argc, char* argv[]) {
	/*
	 * Read program parameters
	 */
	std::cout << "Initializing Options" << std::endl;
	MyOptions::Load(argc, argv);

	EobListener server(new RegistryHandler() );

	while (true) {
		sleep(1);
	}

	return 0;
}
