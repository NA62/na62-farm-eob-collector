/*
 * MyCommandHandler.h
 *
 *  Created on: Jun 21, 2012
 *      Author: kunzejo
 *
 *     This class mainly implements two DimCommand services:
 *     EOB_DATA_COLLECTOR/REGISTER
 *     EOB_DATA_COLLECTOR/UNREGISTER
 *
 *  	To (un)register a dim service that should be read at EOB and put into the event data you
 *  	should send a string to one of the services with following format:
 *     $DimServiceName1,$DimServiceName2,...,$DimServiceNameN
 */

#ifndef MYCOMMANDHANDLER_H_
#define MYCOMMANDHANDLER_H_

#include <dim/dis.hxx>
#include <set>
#include <string>

namespace na62 {
namespace dim {
class RegistryHandler: public DimCommandHandler // In order to inherit "commandHandler" method
{
public:
	// The constructor creates the Commands
	RegistryHandler(std::string& hostname);

	// Overloaded method commandHandler called whenever commands arrive,
	void commandHandler();

private:
	DimCommand *registerCommand;
	DimCommand *unregisterCommand;
	std::set<std::string> registeredServices;

};

inline RegistryHandler::RegistryHandler(std::string& hostname) :
		registerCommand(
				new DimCommand(
						std::string("EOB_DATA_COLLECTOR/REGISTER").data(),
						(char*) ("C"), this)), unregisterCommand(
				new DimCommand(
						std::string("EOB_DATA_COLLECTOR/UNREGISTER").data(),
						(char*) ("C"), this)) {
}

} /* namespace dim */
} /* namespace na62 */
#endif /* MYCOMMANDHANDLER_H_ */
