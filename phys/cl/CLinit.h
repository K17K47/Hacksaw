/*
 * CLinit.h
 *
 *  Created on: 19/06/2014
 *      Author: K17K47
 */

#ifndef CLINIT_H_
#define CLINIT_H_
#define CL_VERSION_1_2
#include <vector>
#include <CL/cl.hpp>


class CLcntxt{
	protected:
		cl::Platform def_platform;
		cl::Device def_device;
		cl::Context context;
	public:
		int init();

};



#endif /* CLINIT_H_ */
