/*
 * MyCommandHandler.cpp
 *
 *  Created on: Jun 21, 2012
 *      Author: Jonas Kunze (kunze.jonas@gmail.com)
 */

#include "RegistryHandler.h"

#include <boost/algorithm/string.hpp>
#include <glog/logging.h>
#include <algorithm>
#include <deque>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <sstream>

#include "options/MyOptions.h"
#include "DimInfoWithUpdateTime.h"

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

	registerServices(Options::GetStringList(OPTION_REGISTERED_SERVICES));
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
			DimInfoWithUpdateTime* info = new DimInfoWithUpdateTime(service);
			registeredServices[service] = info;
		}
	}
}

void RegistryHandler::unregisterServices(std::vector<std::string> services) {
	for (std::string service : services) {
		if (registeredServices.find(service) != registeredServices.end()) {
			DimInfoWithUpdateTime* info = registeredServices[service];
			delete info;
			registeredServices.erase(service);
		}
	}
}

std::string RegistryHandler::generateAllServicesXml(uint runNumber, uint burst, uint sob, uint eob) const {
	std::stringstream output;
	output << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n";
	output << "<burst>\n";
	output << "\t<run>"<<runNumber<<"</run>\n";
	output << "\t<burstID>"<<burst<<"</burstID>\n";
	output << "\t<sob>"<<sob<<"</sob>\n";
	output << "\t<eob>"<<eob<<"</eob>\n";
	for (auto kv : registeredServices) {
		std::string serviceName = kv.first;
		DimInfoWithUpdateTime* info = kv.second;
		addXmlEntity(output, info);
	}
	output << "</burst>\n";
	return output.str();
}

void RegistryHandler::addXmlEntity(std::stringstream& stream,
		DimInfoWithUpdateTime* info) {
	stream << "\t<service>\n";
	stream << "\t\t<name>" << info->getServiceName() << "</name>\n";
	stream << "\t\t<age>" << info->getInfoAge() << "</age>\n";
	stream << "\t\t<value>";
	char* format = info->getFormat();

	if (strcmp(format, "C") == 0) { // String
		stream << info->getString();
	} else if (strcmp(format, "S") == 0) { // Short
		stream << info->getShort();
	} else if (strcmp(format, "I") == 0 || strcmp(format, "I:1") == 0) { // Integer
		stream << info->getInt();
	} else if (strcmp(format, "L") == 0 || strcmp(format, "L:1") == 0) { // Long
		stream << info->getLonglong();
	} else if (strcmp(format, "F") == 0 || strcmp(format, "F:1") == 0) { // Float
		stream << info->getFloat();
	}	else {
		stream << "Unknown Value type: " << std::string(info->getFormat());
	}

	stream << "</value>\n\t</service>\n";
}

}
/* namespace dim */
} /* namespace na62 */
