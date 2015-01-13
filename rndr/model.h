/*
 * model.h
 *
 *  Created on: 25/11/2014
 *      Author: K17K47
 */

#ifndef MODEL_H_
#define MODEL_H_
#include <mathHelper.h>
#include<GL/gl.h>

namespace Rndr {

	class Model {
		public:
				unsigned int nVertex;
				unsigned int nTriangles;
				//unsigned int* indexes;
				//Vector3* vertices;
				//Vector3* normals;
				//Vector2* texCoords;

				unsigned int texID;
				unsigned int indexVBO;
				unsigned int vertexVBO;
				unsigned int normalVBO;
				unsigned int texCoordVBO;
				unsigned int VAO;
		public:
			Model(unsigned int numVtx, unsigned int numTriangles, unsigned int* indexes, Vector3* vertices, Vector3* normals, Vector2* texCoords, GLubyte* tex);
			~Model();
	};

} /* namespace Rndr */

#endif /* MODEL_H_ */
