#include "Window.h"

const char* window_title = "GLFW Starter Project";
Cube cube(5.0f);
OBJObject bunny;
OBJObject dragon;
OBJObject bear;
OBJObject* activeObject;

int pointSize = 1;

int Window::width;
int Window::height;

//Public functions
void Window::initialize_objects()
{
	bunny.parse("resources/models/bunny.obj");
	dragon.parse("resources/models/dragon.obj");
	bear.parse("resources/models/bear.obj");

	activeObject = &bunny;
}

void Window::clean_up()
{
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW.
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
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
	glTranslatef(0, 0, -5);
}

void Window::idle_callback()
{
	// Perform any updates as necessary. Here, we will spin the cube slightly.
	//cube.update();
	activeObject->update();
}

void Window::display_callback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Set the matrix mode to GL_MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	// Load the identity matrix
	glLoadIdentity();

	glPointSize(pointSize);
	// Render objects
	//cube.draw();

	activeObject->draw();

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS)
	{
		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (key == GLFW_KEY_F1)
		{
			activeObject = &bunny;
		}
		if (key == GLFW_KEY_F2)
		{
			activeObject = &dragon;
		}
		if (key == GLFW_KEY_F3)
		{
			activeObject = &bear;
		}
		if (key == GLFW_KEY_P)
		{
			//capital P
			if (mods == GLFW_MOD_SHIFT )
			{
				pointSize--;
				if(pointSize < 1)
				{
					pointSize = 1;
				}
			}
			else
			{
				pointSize++;
			}
		}
	}
}

//Private functions
void Window::perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fW, fH;

	//fH = tan( (fovY / 2) / 180 * pi ) * zNear;
	fH = tan( fovY / 360 * pi ) * zNear;
	fW = fH * aspect;

	glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}
