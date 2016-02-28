/*
 * GLFW.cpp
 *
 *  Created on: 02/07/2015
 *      Author: K17K47
 */

#include<stddef.h>
#include<hserr.h>
#include<GLFW.h>

GLFW* GLFW::_instance = NULL;
GLFW* GLFW::instance(){
	if(!_instance){
		Logger::instance()->printErr("GLFW::Init()","GLFW Init");
		if(!glfwInit()){
			Logger::instance()->printErr("GLFW::Init()","GLFW Init Error");
			return NULL;
		}
		glfwSetErrorCallback(errCallback);
		_instance= new GLFW;
	}
	return _instance;
}

void GLFW::errCallback(int error, const char* errMsg){
	Logger::instance()->printErr("glRndr::glfwErrCB()","Error number " + std::to_string(error) + ":" + errMsg);
}

unsigned int GLFW::newWindow(sWindow windowDesc){
	glfwWindowHint(GLFW_SAMPLES, windowDesc.FxAA);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Logger::instance()->printErr("GLFW::newWindow()","Creating window...");
	windowDesc.pointer=glfwCreateWindow(windowDesc.width, windowDesc.height, "Hacksaw 0.01-indev", nullptr, nullptr);

	if(!windowDesc.pointer){
		Logger::instance()->printErr("GLFW::newWindow()","GLFW failed to create window");
		return 0;
	}

	Logger::instance()->printErr("GLFW::newWindow()","Window created, index " + std::to_string(windows.size()+1));

	windows.push_back(windowDesc);

	return windows.size();
}

void GLFW::chgCurrentWindow(unsigned int windowIndex){
	glfwMakeContextCurrent(windows[windowIndex-1].pointer);
}

void GLFW::chgWindowTitle(unsigned int windowIndex,const std::string windowTitle){
	glfwSetWindowTitle(windows[windowIndex-1].pointer, ("Hacksaw 0.01-indev " + windowTitle).c_str());
}

void GLFW::terminate(){
	Logger::instance()->printErr("GLFW::terminate()","Terminating GLFW, destroying windows...");
	for(std::vector<sWindow>::iterator it=windows.begin();it<windows.end();it++){
		glfwDestroyWindow(it->pointer);
	}
	Logger::instance()->printErr("GLFW::terminate()","Windows destroyed, killing GLFW...");
	windows.clear();
	glfwTerminate();
	Logger::instance()->printErr("GLFW::terminate()","GLFW terminated");
}

bool GLFW::mayWindowClose(unsigned int windowIndex){ return glfwWindowShouldClose(windows[windowIndex-1].pointer); }

void GLFW::swapBuffers(unsigned int windowIndex){ glfwSwapBuffers(windows[windowIndex-1].pointer); }
