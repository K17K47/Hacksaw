/*
 * GLFW.h
 *
 *  Created on: 02/07/2015
 *      Author: K17K47
 */

#ifndef GLFW_H_
#define GLFW_H_

#include <vector>
#include <string>
#include <GLFW/glfw3.h>

typedef struct window{
	unsigned int width;
	unsigned int height;
	unsigned int FxAA;
	GLFWwindow* pointer;
}sWindow;

class GLFW {
	public:
		static GLFW* instance();
		unsigned int newWindow(sWindow windowDesc);
		void chgCurrentWindow(unsigned int windowIndex);
		void chgWindowTitle(unsigned int windowIndex,const std::string windowTitle);
		bool mayWindowClose(unsigned int windowIndex);
		void terminate();
		void swapBuffers(unsigned int windowIndex);
	private:
		GLFW(){};
		GLFW(GLFW const&){};
		GLFW& operator=(GLFW const&){};
		static GLFW* _instance;

		static void errCallback(int error, const char* errMsg);

		std::vector<sWindow> windows;
};

#endif /* GLFW_H_ */
