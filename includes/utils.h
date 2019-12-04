//
// Created by Emilien Lemaire on 17/11/2019.
//

#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <debugbreak.h>
#include <CppLogger/Log.h>
#include <sstream>
#include <data/Data.h>


#define ASSERT(x) if(!(x)) debug_break();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

inline bool GLLogCall(const char* function, const char* file, int line){
    while (GLenum error = glGetError()){
        std::cout << "[OpenGL Error] (" << error << ") at " << function << " in " << file << ":" << line << std::endl;
        glDebugMessageControl(GL_DEBUG_SOURCE_API,
                      GL_DEBUG_TYPE_ERROR,
                      GL_DEBUG_SEVERITY_HIGH,
                      0, nullptr, GL_TRUE);
        return false;
    }
    return true;
}
inline void GLClearError(){
    while(glGetError()!= GL_NO_ERROR);
}

inline GLFWwindow * initGL(int width, int height){

    if ( !glfwInit( ) )
    {
        //Log::Error("Error while initializing GLFW");
        exit(EXIT_FAILURE);
    }
    GLFWwindow *window;


    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow( width, height, "Hello World", NULL, NULL );


    if ( !window )
    {
        Log::Error("Error while creating the window");
        glfwTerminate( );
        exit(EXIT_FAILURE);
    }

    // Make the window's context current
    glfwMakeContextCurrent( window );

    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        Log::Error("Error while initializing GLEW");
        exit(EXIT_FAILURE);
    }

	//glEnable(GL_NORMALIZE);

    //On gère la profondeur
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(1000.f, -10.f);

	std::stringstream sstr;
	sstr << "OpenGL Version: " << glGetString(GL_VERSION);

    Log::Info(sstr.str());


    // Assure que l'on peut capturer la touche d'échappement enfoncée ci-dessous
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    return window;
}

inline void displayPoint(GLfloat array[], GLuint size){
    for (int i = 0; i < size; i+=3) {
        std::cout << i << " " << array[i] << " " << array[i + 1] << " " << array[i + 2] << std::endl;
    }
}

inline void combineArray(const GLfloat array1[], const GLfloat array2[], GLfloat result[], GLuint size1, GLuint size2){
    for (int i = 0; i < size1; ++i) {
        result[i] = array1[i];
    }

    for (int j = 0; j < size2; ++j) {
        result[size1 + j] = array2[j];
    }
}

