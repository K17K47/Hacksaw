/*
 * glRndr.cpp
 *
 *  Created on: 01/11/2014
 *      Author: K17K47
 */
#define GLEW_STATIC
#define GL_GLEXT_PROTOTYPES

#include <GL/glew.h>
#include <GL/glext.h>
#include <rndr/gl/glRndr.h>
#include "hserr.h"
#include "GLFW.h"
#include <iostream>
#include <fstream>

namespace Rndr {
	int glRndr::glInit(){
		sWindow windowDesc;
		windowDesc.FxAA=4;
		windowDesc.width=640;
		windowDesc.height=480;

		windowIndex=GLFW::instance()->newWindow(windowDesc);

		GLFW::instance()->chgCurrentWindow(windowIndex);

		Logger::instance()->printErr("glRndr::glInit()","Video cards OpenGL implementation found:");
		Logger::instance()->printErr("glRndr::glInit()","Vendor: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR))));
		Logger::instance()->printErr("glRndr::glInit()","Renderer: " + std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
		Logger::instance()->printErr("glRndr::glInit()","Version: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));

		Logger::instance()->printErr("glRndr::glInit()","GLEW Init");
		glewExperimental = GL_TRUE;
		if(glewInit() != GLEW_OK){
			Logger::instance()->printErr("glRndr::glInit()","GLEW Init failed!");
			return -1;
		}

		loadShaders("shaders/basic.vsr","shaders/basic.fsr");

		textID = glGetUniformLocation(shaderID, "myTextureSampler");
		mvpID = glGetUniformLocation(shaderID, "MVP");

		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		projection=perspective<double>(90,4.0/3.0,0.1,10.0);

		return 0;
	}

	void glRndr::render(){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderID);

		Matrix44 view=lookAt(cena->activeCamera->pos, Vector3(0.0,0.0,0.0),Vector3(0.0,1.0,0.0));//cena->activeCamera->pos
		Matrix44 MVP=projection * view;

		for(unsigned int i=0;i<cena->nObjects;++i){

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, cena->objects[i]->model->texID);
			glUniform1i(textID, 0);

			Matrix44 rotation(Matrix44::Identity());
			Matrix44 translation(rotation);
			Matrix44 scale(rotation);

			rotation.block<3,3>(0,0)=cena->objects[i]->rot->matrix();

			translation(0,3)=cena->objects[i]->pos->x();
			translation(1,3)=cena->objects[i]->pos->y();
			translation(2,3)=cena->objects[i]->pos->z();

			MVP*=(rotation*translation);

			glUniformMatrix4dv(mvpID, 1, GL_FALSE, MVP.data());

			glBindVertexArray(cena->objects[i]->model->VAO);

			glDrawElements(GL_TRIANGLES, cena->objects[i]->model->nTriangles*3, GL_UNSIGNED_INT, 0);
		}
		GLFW::instance()->swapBuffers(windowIndex);
		glfwPollEvents();
	}

	void glRndr::chgScene(Scene* scene){ cena=scene;}

	void glRndr::loadShaders(const char* vertexShader,const char* fragmentShader){

	    // Create the shaders
	    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	    // Read the Vertex Shader code from the file
	    std::string VertexShaderCode;
	    std::ifstream VertexShaderStream(vertexShader, std::ios::in);
	    if(VertexShaderStream.is_open())
	    {
	        std::string Line = "";
	        while(getline(VertexShaderStream, Line))
	            VertexShaderCode += "\n" + Line;
	        VertexShaderStream.close();
	    }

	    // Read the Fragment Shader code from the file
	    std::string FragmentShaderCode;
	    std::ifstream FragmentShaderStream(fragmentShader, std::ios::in);
	    if(FragmentShaderStream.is_open()){
	        std::string Line = "";
	        while(getline(FragmentShaderStream, Line))
	            FragmentShaderCode += "\n" + Line;
	        FragmentShaderStream.close();
	    }

	    GLint Result = GL_FALSE;
	    int InfoLogLength;

	    // Compile Vertex Shader
	    Logger::instance()->printErr("glRndr::loadShaders()","Compiling shader:" + std::string(vertexShader));
	    char const * VertexSourcePointer = VertexShaderCode.c_str();
	    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	    glCompileShader(VertexShaderID);

	    // Check Vertex Shader
	    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	    //printErr("glRndr::loadShaders",std::string(&VertexShaderErrorMessage[0]));

	    // Compile Fragment Shader
	    Logger::instance()->printErr("glRndr::loadShaders()","Compiling shader:"+std::string(fragmentShader));
	    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	    glCompileShader(FragmentShaderID);

	    // Check Fragment Shader
	    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	   // printErr("glRndr::loadShaders", std::string(&FragmentShaderErrorMessage[0]));

	    // Link the program
	    Logger::instance()->printErr("glRndr::loadShaders()","Linking program");
	    GLuint ProgramID = glCreateProgram();
	    glAttachShader(ProgramID, VertexShaderID);
	    glAttachShader(ProgramID, FragmentShaderID);
	    glLinkProgram(ProgramID);

	    // Check the program
	    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	    std::vector<char> ProgramErrorMessage( std::max(InfoLogLength, int(1)) );
	    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	    Logger::instance()->printErr("glRndr::loadShaders()", std::string(&ProgramErrorMessage[0]));

	    glDeleteShader(VertexShaderID);
	    glDeleteShader(FragmentShaderID);

	    shaderID=ProgramID;
	}

} /* namespace phys */
