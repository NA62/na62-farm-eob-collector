/*
 * MyCommandHandler.cpp
 *
 *  Created on: Jun 21, 2012
 *      Author: kunzejo
 */

#include "RegistryHandler.h"

#include <boost/algorithm/string.hpp>
#include <glog/logging.h>
#include <options/Options.h>
#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <vector>

//#include "options/MyOptions.h"

namespace na62 {
namespace dim {

void RegistryHandler::commandHandler() {
	DimCommand *currCmnd = getCommand();

	std::string message;
	message.resize(currCmnd->getSize());
	message = std::string(currCmnd->getString());

	if (Options::GetInt(OPTION_VERBOSITY) != 0) {
		std::cout << "Received message: " << message << std::endl;
	}

	std::vector<std::string> services;
	boost::split(services, message, boost::is_any_of(","));

	if (currCmnd == registerCommand) {
		std::copy(services.begin(), services.end(),
				std::inserter(registeredServices, registeredServices.end()));
	} else if (currCmnd == unregisterCommand) {
		for (std::string service : services) {
			registeredServices.erase(service);
		}
	} else {
		LOG(ERROR)<<"RegistryHandler received command from a non registered DimCommand";
	}

	std::cout << "All registered services: " << std::endl;
	for (std::string service : registeredServices) {
		std::cout << service << std::endl;
	}
}
}
/* namespace dim */
} /* namespace na62 */
