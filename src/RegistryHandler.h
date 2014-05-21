/*
 * MyCommandHandler.h
 *
 *  Created on: Jun 21, 2012
 *      Author: Jonas Kunze (kunze.jonas@gmail.com)
 *
 *     This class mainly implements two DimCommand services:
 *     EOB_DATA_COLLECTOR/REGISTER
 *     EOB_DATA_COLLECTOR/UNREGISTER
 *
 *  	To (un)register dim services that should be read at EOB and put into the event data you
 *  	should send a string to one of the services with the following format:
 *     $DimServiceName1,$DimServiceName2,...,$DimServiceNameN
 */

#ifndef MYCOMMANDHANDLER_H_
#define MYCOMMANDHANDLER_H_

#include <dim/dis.hxx>
#include <dim/dic.hxx>
#include <map>
#include <string>
#include <vector>

class DimCommand;


namespace na62 {
namespace dim {
class RegistryHandler: public DimCommandHandler // In order to inherit "commandHandler" method
{
public:
	// The constructor creates the Commands
	RegistryHandler();

	// Overloaded method commandHandler called whenever commands arrive,
	void commandHandler();

	/**
	 * Registers new services in an idempotent way. The services will be read out at every EOB signal.
	 * @param services The services to be registered
	 */
	void registerServices(std::vector<std::string> services);

	/**
	 * Unregisters services in an idempotent way.
	 *
	 * @param services The services to be unregistered
	 */
	void unregisterServices(std::vector<std::string> services);

	/**
	 * Reads all registered services and generates a string in the format of $service1:$value1,$service2:$value2,...,$serviceN:$valueN
	 */
	std::string getAllData() const;

private:
	DimCommand *registerCommand;
	DimCommand *unregisterCommand;
	std::map<std::string, DimInfo*> registeredServices;

};
} /* namespace dim */
} /* namespace na62 */
#endif /* MYCOMMANDHANDLER_H_ */
