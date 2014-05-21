/*
 * EobListener.h
 *
 *  Created on: May 21, 2014
 *      Author: Jonas Kunze (kunze.jonas@gmail.com)
 */

#include "EobListener.h"

#include <cstdint>
#include <iostream>

#include "RegistryHandler.h"
#include "options/MyOptions.h"

namespace na62 {
namespace dim {

EobListener::EobListener(const RegistryHandler* registryHandler) :
		burstNumber_("RunControl/BurstNumber", -1, this), runNumber_(
				"RunControl/RunNumber", -1, this), SOB_TS_("NA62/Timing/SOB", 0,
				this), registryHandler_(registryHandler) {

	char hostName[1024];
		hostName[1023] = '\0';
		if (gethostname(hostName, 1023)) {
			std::cerr << "Unable to get host name! Refusing to start.";
			exit(1);
		}

		start(hostName);
}

EobListener::~EobListener() {
	delete registryHandler_;
	stop();
}

void EobListener::infoHandler() {
	DimInfo *curr = getInfo();
	if (curr == &runNumber_) {
		int runNumber = runNumber_.getInt();
		std::cout << "Updating RunNumber to " << runNumber << std::endl;
	} else if (curr == &SOB_TS_) {
		uint32_t timestamp = SOB_TS_.getInt();
		std::cout << "Updating SOB timestamp to " << timestamp << std::endl;
		std::cout << registryHandler_->getAllData() << std::endl;
	} else if (curr == &burstNumber_) {
		uint32_t burst = burstNumber_.getInt();
		std::cout << "Updating burst ID to " << burst << std::endl;
	}
}
} /* namespace dim */
} /* namespace na62 */
