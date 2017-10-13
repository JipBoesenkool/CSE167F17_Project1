//
// Created by Jip Boesenkool on 11/10/2017.
//
#ifndef CSE167_PROJECT1_IRENDERER_H
#define CSE167_PROJECT1_IRENDERER_H
#include "IRenderer.h"

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

class IRenderer
{
//members:
public:
	int m_width;
	int m_height;
	GLFWwindow* mp_window;
private:
//functions
public:
	virtual void Init( GLFWwindow *window, int width, int height ) = 0;
	virtual void Setup() = 0;

	//virtual void ResizeCallback(GLFWwindow* window, int width, int height) = 0;

	virtual void DisplayCallback(GLFWwindow* window) = 0;
	void PrintVersions();
private:

};

#endif //CSE167_PROJECT1_IRENDERER_H
