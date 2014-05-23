/*
 * DimInfoWithUpdateTime.h
 *
 *  Created on: May 23, 2014
 *      Author: root
 */

#ifndef DIMINFOWITHUPDATETIME_H_
#define DIMINFOWITHUPDATETIME_H_

#include <dim/dic.hxx>
#include <boost/timer/timer.hpp>

namespace na62 {
namespace dim {

class DimInfoWithUpdateTime: public DimInfo {
public:

	DimInfoWithUpdateTime(std::string serviceName) :
			DimInfo(serviceName.c_str(), -1), serviceName_(serviceName) {
		std::cout << "Registering " << serviceName << std::endl;
	}

	void infoHandler() {
		updateTime_.start();
	}

	/**
	 * Returns the number of seconds passed since the  value has last been updated
	 */
	float getInfoAge() const {
		return updateTime_.elapsed().wall / 1e9f;
	}

	std::string getServiceName() const {
		return serviceName_;
	}

private:
	std::string serviceName_;
	boost::timer::cpu_timer updateTime_;
};

} /* namespace dim */
} /* namespace na62 */

#endif /* DIMINFOWITHUPDATETIME_H_ */
