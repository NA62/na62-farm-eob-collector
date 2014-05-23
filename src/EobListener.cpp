/*
 * EobListener.h
 *
 *  Created on: May 21, 2014
 *      Author: Jonas Kunze (kunze.jonas@gmail.com)
 */

#include "EobListener.h"

#include <cstdint>
#include <iostream>
#include <fstream>
#include<boost/filesystem.hpp>

#include "RegistryHandler.h"
#include "options/MyOptions.h"

namespace na62 {
namespace dim {

EobListener::EobListener(const RegistryHandler* registryHandler) :
		burstNumber_("RunControl/BurstNumber", -1, this), runNumber_(
				"RunControl/RunNumber", -1, this), SOB_TS_("NA62/Timing/SOB", 0,
				this), EOB_TS_("NA62/Timing/EOB", -1, this), registryHandler_(
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
		std::cout << "EOB has been updated. Writing new file:" << std::endl;
		usleep(Options::GetFloat(OPTION_EOB_TIMEOUT) * 1E6);
		int runNumber = runNumber_.getInt();
		int burst = burstNumber_.getInt();
		int sob = SOB_TS_.getInt();
		int eob = EOB_TS_.getInt();

		/*
		 * Generate the filename and create a ofstream to the file
		 */
		std::string fileName = generateFileName(runNumber, burst, 0);
		std::string filePath = Options::GetString(OPTION_STORAGE_DIR) + "/"
				+ fileName;
		std::cout << "Writing file " << filePath << std::endl;

		if (boost::filesystem::exists(filePath)) {
			std::cerr << "File already exists: " << filePath << std::endl;
			int counter = 2;
			std::string tmpName;
			tmpName = generateFileName(runNumber, burst, counter);
			while (boost::filesystem::exists(
					Options::GetString(OPTION_STORAGE_DIR) + "/" + tmpName)) {
				std::cerr << "File already exists: " << tmpName << std::endl;
				tmpName = generateFileName(runNumber, burst, ++counter);
			}

			std::cerr << "Instead writing file: " << tmpName << std::endl;
			fileName = tmpName;
			filePath = Options::GetString(OPTION_STORAGE_DIR) + "/" + fileName;
		}

		std::ofstream eobFile;
		eobFile.open(filePath.data(), std::ios::out | std::ios::trunc);

		if (!eobFile.good()) {
			std::cerr << "Unable to write to file " << filePath << std::endl;
			// carry on to free the memory. myfile.write will not throw!
		}

		/*
		 * Generate the XML and pipe it into the file
		 */
		eobFile
				<< registryHandler_->generateAllServicesXml(runNumber, burst,
						sob, eob);
		eobFile.close();
		system(std::string("chown na62cdr:vl " + filePath).data());

		std::cout << "Wrote EOB file of run " << runNumber << " and burst "
				<< burst << " to: " << filePath << std::endl;

	}
}

std::string EobListener::generateFileName(uint32_t runNumber, uint32_t burstID,
		uint32_t duplicate) {
	char buffer[64];

	if (duplicate == 0) {
		sprintf(buffer, "burstinfo%06d-%04d.dat", runNumber, burstID);
	} else {
		sprintf(buffer, "burstinfo%06d-%04d_%d.dat", runNumber, burstID,
				duplicate);
	}
	return std::string(buffer);
}
} /* namespace dim */
} /* namespace na62 */
