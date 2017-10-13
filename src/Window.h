#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>

#ifdef __APPLE__
// If modern OpenGL replace gl.h with gl3.h
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include "Cube.h"

#include "OBJObject.h"
#include "IRenderer.h"

class Window
{
public:
	static OBJObject bunny;
	static OBJObject dragon;
	static OBJObject bear;
	static OBJObject *activeObject;
	static IRenderer *p_currentRenderer;
	static bool rendererIsOgl;
	static int pointSize;
	static int width;
	static int height;
	static void initialize_objects();
	//static GLFWwindow* create_window(int width, int height);
	static void resize_callback(GLFWwindow* window, int width, int height);
	static void idle_callback();
	static void display_callback(GLFWwindow*);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	//replacement for gluPerspective
	//https://stackoverflow.com/questions/12943164/replacement-for-gluperspective-with-glfrustrum
	static void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar );
};

#endif
