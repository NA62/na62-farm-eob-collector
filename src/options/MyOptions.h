/*
 * MyOptions.h
 *
 *  Created on: Apr 11, 2014
 \*      Author: Jonas Kunze (kunze.jonas@gmail.com)
 */

#pragma once
#ifndef MYOPTIONS_H_
#define MYOPTIONS_H_

#include <options/Options.h>
#include <string>
#include <boost/thread.hpp>

/*
 * Available options
 */
#define OPTION_REGISTERED_SERVICES (char*)"registeredServices"
#define OPTION_EOB_TIMEOUT (char*)"EOBTimeout"

namespace na62 {
namespace dim {
class MyOptions: public Options {
public:
	MyOptions();
	virtual ~MyOptions();

	static void Load(int argc, char* argv[]) {
		desc.add_options()

		(OPTION_CONFIG_FILE,
				po::value<std::string>()->default_value(
						"/etc/na62-farm-eob-collector.conf"),
				"Config file for the options shown here")

		(OPTION_REGISTERED_SERVICES,
				po::value<std::string>()->default_value(""),
				"Instead of registering services via DIM you can list services to be registered here. The format must be $service1,$service2,....,$serviceN")

		(OPTION_EOB_TIMEOUT, po::value<std::string>()->default_value(""),
				"X seconds after every change of the EOB time the registered services will be read out. This enables the services to change their value triggered by the EOB signal.")

				;

		Options::Initialize(argc, argv, desc);
	}
};
} /* namespace dim */
} /* namespace na62 */

#endif /* MYOPTIONS_H_ */
