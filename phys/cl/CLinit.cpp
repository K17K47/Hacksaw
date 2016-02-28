/*
 * CLinit.cpp
 *
 *  Created on: 19/06/2014
 *      Author: K17K47
 */

#include <iostream>
#include <vector>
#include "CLinit.h"
#include "hserr.h"

int CLcntxt::init(void){
	std::string tmpString;
	Logger::instance()->printErr("CLcntxt::init()","Initializing OpenCL...");

	std::vector<cl::Platform> platforms;
	if (cl::Platform::get(&platforms)!=CL_SUCCESS){
		Logger::instance()->printErr("CLcntxt::init()","No OpenCL platforms!");
		return 1;
	}

	Logger::instance()->printErr("CLcntxt::init()","OpenCL Platforms found:");
	for(std::vector<cl::Platform>::iterator it = platforms.begin(); it !=platforms.end(); it++){
		tmpString=tmpString + " \n" + it->getInfo<CL_PLATFORM_NAME>();
	}
	Logger::instance()->printErr("CLcntxt::init()",tmpString);

	CLcntxt::def_platform=platforms[0];
	Logger::instance()->printErr("CLcntxt::init()","Using OpenCL platform " + CLcntxt::def_platform.getInfo<CL_PLATFORM_NAME>());

	std::vector<cl::Device> devices;
	if(def_platform.getDevices(CL_DEVICE_TYPE_ALL,&devices)!=CL_SUCCESS){
		Logger::instance()->printErr("CLcntxt::init()","No OpenCL devices!");
		return 1;
	}

	tmpString.clear();
	Logger::instance()->printErr("CLcntxt::init()","OpenCL Devices found:");
	for(std::vector<cl::Device>::iterator it = devices.begin(); it !=devices.end(); it++){
		tmpString=tmpString + "\n" + it->getInfo<CL_DEVICE_NAME>();
	}
	Logger::instance()->printErr("CLcntxt::init()",tmpString);

	CLcntxt::def_device=devices[0];
	Logger::instance()->printErr("CLcntxt::init()","Using OpenCL device " + CLcntxt::def_device.getInfo<CL_DEVICE_NAME>());

	return 0;
}

