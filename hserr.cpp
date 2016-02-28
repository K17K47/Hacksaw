/*
 * hserr.c
 *
 *  Created on: 24/11/2014
 *      Author: K17K47
 */

#include<stddef.h>
#include<iostream>
//#include<GLFW/glfw3.h>
#include"hserr.h"

Logger* Logger::_instance = NULL;
void Logger::printErr(std::string funcID,std::string msg){
	std::chrono::duration<double> t=std::chrono::steady_clock::now()-start;
	std::cout<<"["<<t.count()<<"] "<<funcID<<": "<<msg<<"\n";
}

Logger* Logger::instance(){
	if(!_instance)_instance= new Logger;
	return _instance;
}

