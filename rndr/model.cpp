/*
 * model.cpp
 *
 *  Created on: 25/11/2014
 *      Author: K17K47
 */

#include <GL/glew.h>
#include <rndr/model.h>
#include <rndr/gl/glRndr.h>

namespace Rndr {

	Model::Model(unsigned int numVtx, unsigned int numTriangles, unsigned int* indexes, Vector3* vertices, Vector3* normals, Vector2* texCoords, GLubyte* tex) {
		nVertex=numVtx;
		nTriangles=numTriangles;

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// Generate And Bind The Vertex Buffer
		glGenBuffers( 1, &vertexVBO );                  // Get A Valid Name
		glBindBuffer( GL_ARRAY_BUFFER, vertexVBO );         // Bind The Buffer
		// Load The Data
		glBufferData( GL_ARRAY_BUFFER, nVertex*3*sizeof(real), vertices, GL_STATIC_DRAW );
		glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, (const GLvoid *)0 );

		glGenBuffers( 1, &indexVBO);
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexVBO);
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, nTriangles*3*sizeof(unsigned int), indexes, GL_STATIC_DRAW );
		glVertexAttribPointer(1, 1, GL_UNSIGNED_INT, GL_FALSE, 0, (const GLvoid *)0 );

		// Generate And Bind The Texture Coordinate Buffer
		glGenBuffers( 1, &texCoordVBO );                 // Get A Valid Name
		glBindBuffer( GL_ARRAY_BUFFER, texCoordVBO );        // Bind The Buffer
		// Load The Data
		glBufferData( GL_ARRAY_BUFFER, nVertex*2*sizeof(real), texCoords, GL_STATIC_DRAW );
		glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, 0, (const GLvoid *)0 );

		/*
		glGenBuffers( 1, &normalVBO );
		glBindBuffer( GL_ARRAY_BUFFER, normalVBO );
		glBufferData( GL_ARRAY_BUFFER, nVertex*3*sizeof(real), normals, GL_STATIC_DRAW );
		glVertexAttribPointer(2, 3, GL_DOUBLE, GL_FALSE, 0, (const GLvoid *)0 );
		*/

		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);

		// Give the image to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, tex);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	Model::~Model() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers( 1, &indexVBO);
		glDeleteBuffers( 1, &normalVBO);
		glDeleteBuffers( 1, &texCoordVBO);		// Deallocate Vertex Buffer
		glDeleteBuffers( 1, &vertexVBO);
		glDeleteTextures(1, &texID);
	}

} /* namespace Rndr */
