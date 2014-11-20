/*
 * glRndr.h
 *
 *  Created on: 01/11/2014
 *      Author: K17K47
 */

#ifndef GLRNDR_H_
#define GLRNDR_H_

#include <string>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

namespace Rndr {

	class glRndr {
		protected:
			unsigned width=640;
			unsigned height=320;
			unsigned short FxAA=4;
			std::string title="Hacksaw 0.01-indev";
			bool fullscreen=false;
			GLFWwindow* window;
		public:
			int glInit();
		private:
			static void glfwErrCB(int error, const char* errMsg);
	};

} /* namespace phys */

#endif /* GLRNDR_H_ */
