/*
 * EobListener.h
 *
 *  Created on: May 21, 2014
 *      Author: Jonas Kunze (kunze.jonas@gmail.com)
 *
 *  This is the main Dim server receiving EOB_TS state changes and triggering the
 *  writing of burst files (XML).
 */

#ifndef EOBLISTENER_H_
#define EOBLISTENER_H_

#include <dim/dic.hxx>
#include <dim/dis.hxx>
#include <cstdint>
#include <string>

namespace na62 {
namespace dim {

class RegistryHandler;

class EobListener: public DimClient, DimServer {
public:
	EobListener(const RegistryHandler* registryHandler);
	virtual ~EobListener();

private:
	/*
	 * Called whenever a registered DimInfo changes
	 */
	void infoHandler();

	DimInfo burstNumber_;
	DimInfo runNumber_;
	DimInfo SOB_TS_;
	DimUpdatedInfo EOB_TS_;

	int nextRunNumber;
	int nextBurst;
	int nextSob;

	const RegistryHandler* registryHandler_;
	std::string generateFileName(uint32_t runNumber, uint32_t burstID, uint32_t duplicate);
};
} /* namespace dim */
} /* namespace na62 */
#endif /* EOBLISTENER_H_ */
