/*
 * CLinit.cpp
 *
 *  Created on: 19/06/2014
 *      Author: K17K47
 */

#include <iostream>
#include <vector>
#include "CLinit.h"

int CLcntxt::init(void){
	std::cout<<"CLcntxt::init(): Initializing OpenCL...\n";
	std::cout<<"\n";

	std::vector<cl::Platform> platforms;
	if (cl::Platform::get(&platforms)!=CL_SUCCESS){
		std::cout<<"CLcntxt::init(): No OpenCL platforms!\n";
		return 1;
	}

	std::cout<<"CLcntxt::init(): OpenCL Platforms found:\n";
	for(std::vector<cl::Platform>::iterator it = platforms.begin(); it !=platforms.end(); it++){
		std::cout<<it->getInfo<CL_PLATFORM_NAME>()<<"\n";
	}
	std::cout<<"\n";

	CLcntxt::def_platform=platforms[0];
	std::cout<<"CLcntxt::init(): Using OpenCL platform "<<CLcntxt::def_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";
	std::cout<<"\n";

	std::vector<cl::Device> devices;
	if(def_platform.getDevices(CL_DEVICE_TYPE_ALL,&devices)!=CL_SUCCESS){
		std::cout<<"CLcntxt::init(): No OpenCL devices!\n";
		return 1;
	}

	std::cout<<"CLcntxt::init(): OpenCL Devices found:\n";
	for(std::vector<cl::Device>::iterator it = devices.begin(); it !=devices.end(); it++){
		std::cout<<it->getInfo<CL_DEVICE_NAME>()<<"\n";
	}
	std::cout<<"\n";

	CLcntxt::def_device=devices[0];
	std::cout<<"CLcntxt::init(): Using OpenCL device "<<CLcntxt::def_device.getInfo<CL_DEVICE_NAME>()<<"\n";
    std::cout<<"\n";

	return 0;
}

