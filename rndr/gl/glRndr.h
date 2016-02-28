/*
 * glRndr.h
 *
 *  Created on: 01/11/2014
 *      Author: K17K47
 */

#ifndef GLRNDR_H_
#define GLRNDR_H_

#include <mathHelper.h>
#include <string>
#include <rndr/scene.h>

namespace Rndr {

	class glRndr {
		protected:
			Matrix44 projection;
			Scene* cena;
			GLuint shaderID;
			GLuint textID;
			GLuint mvpID;
		public:
			unsigned int windowIndex;
			int glInit();
			void render();
			void loadShaders(const char* vertexShader, const char* fragmentShader);
			void chgScene(Scene* scene);
	};

} /* namespace phys */

#endif /* GLRNDR_H_ */
