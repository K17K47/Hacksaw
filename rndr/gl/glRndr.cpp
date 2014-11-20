/*
 * glRndr.cpp
 *
 *  Created on: 01/11/2014
 *      Author: K17K47
 */

#include <rndr/gl/glRndr.h>
#include <iostream>

namespace Rndr {
	int glRndr::glInit(){
		std::cout<<"glRndr::glInit(): GLFW Init\n";
		if(!glfwInit()){
			std::cout<<"glRndr::glInit(): GLFW Init failed!\n";
			return -1;
		}

		glfwSetErrorCallback(glfwErrCB); //funcao callback p/ erros

		glfwWindowHint(GLFW_SAMPLES, FxAA); //AntiAliasing
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window=glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		std::cout<<glfwGetTime()<<" -> glRndr::glInit(): Creating window...\n";
		if(!window){
			glfwTerminate();
			std::cout<<"glRndr::glInit(): GLFW failed to create window\n";
			return -1;
		}

		glfwMakeContextCurrent(window);

		std::cout<<glfwGetTime()<<" -> glRndr::glInit(): GLEW Init\n";
		if(glewInit() != GLEW_OK){
			std::cout<<"glRndr::glInit(): GLEW Init failed!\n";
			return -1;
		}

		return 0;
	}

	void glRndr::glfwErrCB(int error, const char* errMsg){
		std::cout<<glfwGetTime()<<" -> glRndr::glfwErrCB():"<<errMsg<<"\n";
	}

} /* namespace phys */
