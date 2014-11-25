/*
 * glRndr.cpp
 *
 *  Created on: 01/11/2014
 *      Author: K17K47
 */

#include <rndr/gl/glRndr.h>
#include <hserr.h>
#include <iostream>

namespace Rndr {
	int glRndr::glInit(){
		printErr("glRndr::glInit()","GLFW Init");
		if(!glfwInit()){
			printErr("glRndr::glInit()","GLFW Init failed!");
			return -1;
		}

		glfwSetErrorCallback(glfwErrCB); //funcao callback p/ erros

		glfwWindowHint(GLFW_SAMPLES, FxAA); //AntiAliasing
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window=glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		printErr("glRndr::glInit()","Creating window...");
		if(!window){
			glfwTerminate();
			printErr("glRndr::glInit()","GLFW failed to create window");
			return -1;
		}

		glfwMakeContextCurrent(window);

		printErr("glRndr::glInit()","Video cards OpenGL implementation found:");
		printErr("glRndr::glInit()","Vendor: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR))));
		printErr("glRndr::glInit()","Renderer: " + std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
		printErr("glRndr::glInit()","Version: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));

		printErr("glRndr::glInit()","GLEW Init");
		if(glewInit() != GLEW_OK){
			printErr("glRndr::glInit()","GLEW Init failed!");
			return -1;
		}

		return 0;
	}

	void glRndr::glfwErrCB(int error, const char* errMsg){
		printErr("glRndr::glfwErrCB()",errMsg);
	}

} /* namespace phys */
