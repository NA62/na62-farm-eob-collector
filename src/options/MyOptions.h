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
#define OPTION_FARM_EXEC_PATH (char*)"farmExecPath"
#define OPTION_HEARTBEAT_TIMEOUT_MILLIS (char*)"hearbeatTimeoutMillis"

#define OPTION_MULTI_STAT_SERVICES (char*)"multiStatServices"
#define OPTION_LONGLONG_SERVICES (char*)"singlelongServices"
#define OPTION_IS_MERGER (char*)"isMerger"

/*
 * Performance
 */
#define OPTION_ZMQ_IO_THREADS (char*)"zmqIoThreads"

namespace na62 {
namespace dim {
class MyOptions: public Options {
public:
	MyOptions();
	virtual ~MyOptions();

	static void Load(int argc, char* argv[]) {
		desc.add_options()

		(OPTION_CONFIG_FILE,
				po::value<std::string>()->default_value("/etc/na62-farm-dim.conf"),
				"Config file for the options shown here")

		(OPTION_FARM_EXEC_PATH, po::value<std::string>()->required(),
				"Path to the executable farm program")

		( OPTION_HEARTBEAT_TIMEOUT_MILLIS, po::value<int>()->required(),
				"Number of milliseconds that have to pass without receiving a heart beat from the farm program until we go into error mode.")

		( OPTION_MULTI_STAT_SERVICES, po::value<std::string>()->required(),
				"Comma separated (S1,S2,S3...) list of services with multiple stats like \"A:a;B:b\"")

		( OPTION_LONGLONG_SERVICES, po::value<std::string>()->required(),
				"Comma separated list (S1,S2,S3...) of services with single long values.")

		( OPTION_IS_MERGER, po::value<int>()->required(),
				"Set 1 if this is the dim connector for a merger and 0 if it is running on a farm PC.")

				;

		Options::Initialize(argc, argv, desc);
	}
};
} /* namespace dim */
} /* namespace na62 */

#endif /* MYOPTIONS_H_ */
