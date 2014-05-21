/*
 * MyCommandHandler.cpp
 *
 *  Created on: Jun 21, 2012
 *      Author: Jonas Kunze (kunze.jonas@gmail.com)
 */

#include "RegistryHandler.h"

#include <boost/algorithm/string.hpp>
#include <glog/logging.h>
#include <options/Options.h>
#include <algorithm>
#include <deque>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>

//#include "options/MyOptions.h"

namespace na62 {
namespace dim {

RegistryHandler::RegistryHandler() :
		registerCommand(
				new DimCommand(
						std::string("EOB_DATA_COLLECTOR/REGISTER").data(),
						(char*) ("C"), this)), unregisterCommand(
				new DimCommand(
						std::string("EOB_DATA_COLLECTOR/UNREGISTER").data(),
						(char*) ("C"), this)) {
}

void RegistryHandler::commandHandler() {
	DimCommand *currCmnd = getCommand();

	std::string message;
	message.resize(currCmnd->getSize());
	message = std::string(currCmnd->getString());

	std::cout << "Received message: " << message << std::endl;

	std::vector<std::string> services;
	boost::split(services, message, boost::is_any_of(","));

	if (currCmnd == registerCommand) {
		registerServices(services);
	} else if (currCmnd == unregisterCommand) {
		unregisterServices(services);
	} else {
		LOG(ERROR)<<"RegistryHandler received command from a non registered DimCommand";
	}

	std::cout << "All registered services: " << std::endl;
	for (auto kv : registeredServices) {
		std::cout << kv.first << std::endl;
	}
}

void RegistryHandler::registerServices(std::vector<std::string> services) {
	for (std::string service : services) {
		if (registeredServices.find(service) == registeredServices.end()) {
			DimInfo* info = new DimInfo(service.c_str(), -1);
			registeredServices[service] = info;
		}
	}
}

void RegistryHandler::unregisterServices(std::vector<std::string> services) {
	for (std::string service : services) {
		if (registeredServices.find(service) != registeredServices.end()) {
			DimInfo* info = registeredServices[service];
			delete info;
			registeredServices.erase(service);
		}
	}
}

std::string RegistryHandler::getAllData() const {
	std::stringstream output;
	for (auto kv : registeredServices) {
		std::string serviceName = kv.first;
		DimInfo* info = kv.second;
		output << serviceName << ":" << info->getString() << ",";
	}
	return output.str();
}

}
/* namespace dim */
} /* namespace na62 */
