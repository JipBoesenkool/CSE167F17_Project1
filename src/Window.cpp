#include "Window.h"
#include "GLFW_Rasterizer.h"
#include "OGL_Renderer.h"

const char* window_title = "CSE167 - Assignment 1";
Cube cube(5.0f);
OBJObject Window::bunny;
OBJObject Window::dragon;
OBJObject Window::bear;
OBJObject* Window::activeObject;
IRenderer* Window::p_currentRenderer;
bool Window::rendererIsOgl;

int Window::pointSize = 1;

int Window::width;
int Window::height;

//Public functions
void Window::initialize_objects()
{
	Window::bunny.parse("resources/models/bunny.obj");
	Window::dragon.parse("resources/models/dragon.obj");
	Window::bear.parse("resources/models/bear.obj");

	Window::activeObject = &bunny;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
	glfwGetFramebufferSize(window, &width, &height);
	Window::width = width;
	Window::height = height;
	// Set the viewport size
	glViewport(0, 0, width, height);
	// Set the matrix mode to GL_PROJECTION to determine the proper camera properties
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the perspective of the projection viewing frustum
	//gluPerspective(60.0, double(width) / (double)height, 1.0, 1000.0);
	perspectiveGL(60.0, double(width) / (double)height, 1.0, 1000.0);
	// Move camera back 20 units so that it looks at the origin (or else it's in the origin)
	glTranslatef(0, 0, -20);
}

void Window::idle_callback()
{
	// Perform any updates as necessary. Here, we will spin the cube slightly.
	//cube.update();
	Window::activeObject->update();
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		if(action == GLFW_PRESS)
		{
			// Check if escape was pressed
			if (key == GLFW_KEY_ESCAPE)
			{
				// Close the window. This causes the program to also terminate.
				glfwSetWindowShouldClose(window, GL_TRUE);
			}
			if (key == GLFW_KEY_F1)
			{
				Window::activeObject = &bunny;
			}
			if (key == GLFW_KEY_F2)
			{
				Window::activeObject = &dragon;
			}
			if (key == GLFW_KEY_F3)
			{
				Window::activeObject = &bear;
			}
			//Reset transform
			if (key == GLFW_KEY_R)
			{
				if(mods == GLFW_MOD_SHIFT)
				{
					Window::activeObject->resetRotation();
					Window::activeObject->resetScale();
				}
				else
				{
					Window::activeObject->resetPosition();
				}
			}
			//Switch renderer
			if (key == GLFW_KEY_M)
			{
				if(Window::rendererIsOgl)
				{
					std::cout << "RENDERER: switching to rasterizer." << std::endl;
					Window::p_currentRenderer = GLFW_Rasterizer::Instance;
				}
				else
				{
					std::cout << "RENDERER: switching to OGL." << std::endl;
					Window::p_currentRenderer = OGL_Renderer::Instance;
				}
				Window::p_currentRenderer->Setup();
			}
		}

//3. Rendering the Points with OpenGL (20 Points) (point size)
		if (key == GLFW_KEY_P)
		{
			//capital P
			if (mods == GLFW_MOD_SHIFT )
			{
				Window::pointSize--;
				if(Window::pointSize < 1)
				{
					Window::pointSize = 1;
				}
			}
			else
			{
				Window::pointSize++;
			}
		}
//4. Manipulating the Points (20 Points)
		//Translation
		if (key == GLFW_KEY_X)
		{
			glm::vec3 dir;
			(mods == GLFW_MOD_SHIFT) ? dir = glm::vec3(1,0,0) : dir = glm::vec3(-1,0,0);
			Window::activeObject->move(dir);
		}
		if (key == GLFW_KEY_Y)
		{
			glm::vec3 dir;
			(mods == GLFW_MOD_SHIFT) ? dir = glm::vec3(0,1,0) : dir = glm::vec3(0,-1,0);
			Window::activeObject->move(dir);
		}
		if (key == GLFW_KEY_Z)
		{
			glm::vec3 dir;
			(mods == GLFW_MOD_SHIFT) ? dir = glm::vec3(0,0,1) : dir = glm::vec3(0,0,-1);
			Window::activeObject->move(dir);
		}
		//Rotation
		if (key == GLFW_KEY_O)
		{
			float deg;
			(mods == GLFW_MOD_SHIFT) ? deg=-10.0f : deg=10.0f;
			Window::activeObject->manualRotation(deg);
		}
		//Scale
		if (key == GLFW_KEY_S)
		{
			bool scaleUp;
			(mods == GLFW_MOD_SHIFT) ? scaleUp = true : scaleUp = false;
			Window::activeObject->scaleObject(scaleUp);
		}
	}
}

//Private functions
void Window::perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
	GLdouble fW, fH;

	fH = tan( fovY / 360 * glm::pi<float>() ) * zNear;
	fW = fH * aspect;

	glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}
