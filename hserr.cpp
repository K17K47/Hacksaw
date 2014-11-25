/*
 * hserr.c
 *
 *  Created on: 24/11/2014
 *      Author: K17K47
 */

#include<iostream>
#include<string>
#include<GLFW/glfw3.h>
#include"hserr.h"

void printErr(std::string funcID,std::string msg){
	double t=glfwGetTime();
	if(t==0){
		std::cout<<funcID<<": "<<msg<<"\n";
		return;
	}
	std::cout<<"["<<t<<"] "<<funcID<<": "<<msg<<"\n";
}

