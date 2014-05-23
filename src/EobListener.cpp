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
				"RunControl/RunNumber", -1, this), SOB_TS_("NA62/Timing/SOB",
				-1, this), EOB_TS_("NA62/Timing/EOB", -1, this), registryHandler_(
				registryHandler) {

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
	if (curr == &EOB_TS_) {
		int runNumber = runNumber_.getInt();
		int burst = burstNumber_.getInt();
		int sob = SOB_TS_.getInt();
		int eob = EOB_TS_.getInt();
		std::cout << "runNumber: " << runNumber << std::endl;
		std::cout << "burst: " << burst << std::endl;
		std::cout << "EOB: " << eob << std::endl;
		std::cout << "SOB: " << sob << std::endl;
		std::cout
				<< registryHandler_->generateAllServicesXml(runNumber, burst,
						sob, eob) << std::endl;
	}
}
} /* namespace dim */
} /* namespace na62 */
