/*
 * hserr.h
 *
 *  Created on: 24/11/2014
 *      Author: K17K47
 */

#ifndef HSERR_H_
#define HSERR_H_

#include<string>
#include<chrono>

class Logger{
	public:
		static Logger* instance();
		void printErr(std::string funcID,std::string msg);
	private:
		Logger(){};
		Logger(Logger const&){};
		Logger& operator=(Logger const&){};
		static Logger* _instance;
		std::chrono::time_point<std::chrono::steady_clock> start=std::chrono::steady_clock::now();
};

#endif /* HSERR_H_ */
