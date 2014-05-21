/*
 * EobListener.h
 *
 *  Created on: May 21, 2014
 *      Author: Jonas Kunze (kunze.jonas@gmail.com)
 */

#ifndef EOBLISTENER_H_
#define EOBLISTENER_H_

#include <dim/dic.hxx>
#include <dim/dis.hxx>

namespace na62 {
namespace dim {

class RegistryHandler;

class EobListener: public DimClient, DimServer {
public:
	EobListener(const RegistryHandler* registryHandler);
	virtual ~EobListener();

private:
	void infoHandler();

	DimInfo burstNumber_;
	DimInfo runNumber_;
	DimInfo SOB_TS_;

	const RegistryHandler* registryHandler_;
};
} /* namespace dim */
} /* namespace na62 */
#endif /* EOBLISTENER_H_ */
