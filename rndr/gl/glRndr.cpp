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
#include <hserr.h>
#include <iostream>
#include <fstream>

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
		//glfwSetWindowCloseCallback(window, glfwKillCB);

		printErr("glRndr::glInit()","Video cards OpenGL implementation found:");
		printErr("glRndr::glInit()","Vendor: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR))));
		printErr("glRndr::glInit()","Renderer: " + std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
		printErr("glRndr::glInit()","Version: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));

		printErr("glRndr::glInit()","GLEW Init");
		glewExperimental = GL_TRUE;
		if(glewInit() != GLEW_OK){
			printErr("glRndr::glInit()","GLEW Init failed!");
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

		for(unsigned int i=0;i<cena->nObjects;++i){

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, cena->objects[i]->model->texID);
			glUniform1i(textID, 0);

			Matrix44 MVP=projection * view;
			glUniformMatrix4dv(mvpID, 1, GL_FALSE, MVP.data());

			glBindVertexArray(cena->objects[i]->model->VAO);

			glDrawElements(GL_TRIANGLES, cena->objects[i]->model->nTriangles*3, GL_UNSIGNED_INT, 0);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void glRndr::chgWindowTitle(const std::string windowTitle){
		glfwSetWindowTitle(window, (title+" "+windowTitle).c_str());
	}

	void glRndr::terminate(){
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void glRndr::glfwErrCB(int error, const char* errMsg){
		printErr("glRndr::glfwErrCB()",errMsg);
	}

	bool glRndr::mayWindowClose(){ return glfwWindowShouldClose(window); }

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
	    printErr("glRndr::loadShaders()","Compiling shader:" + std::string(vertexShader));
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
	    printErr("glRndr::loadShaders()","Compiling shader:"+std::string(fragmentShader));
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
	    printErr("glRndr::loadShaders()","Linking program");
	    GLuint ProgramID = glCreateProgram();
	    glAttachShader(ProgramID, VertexShaderID);
	    glAttachShader(ProgramID, FragmentShaderID);
	    glLinkProgram(ProgramID);

	    // Check the program
	    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	    std::vector<char> ProgramErrorMessage( std::max(InfoLogLength, int(1)) );
	    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	    printErr("glRndr::loadShaders()", std::string(&ProgramErrorMessage[0]));

	    glDeleteShader(VertexShaderID);
	    glDeleteShader(FragmentShaderID);

	    shaderID=ProgramID;
	}

} /* namespace phys */
