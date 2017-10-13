#include "main.h"
#include "IRenderer.h"
#include "GLFW_Rasterizer.h"
#include "OGL_Renderer.h"

GLFWwindow* window;

static void ErrorCallback(int error, const char* description)
{
	// Print error
	fputs(description, stderr);
}

int main(void)
{
	int width = 640, height = 480;
	const char* window_title = "CSE167 - Assignment 1";

	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create the GLFW window
	window = glfwCreateWindow(width, height, window_title, NULL, NULL);

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

	Window::initialize_objects();
	OGL_Renderer *gpuRenderer = new OGL_Renderer();
	GLFW_Rasterizer *softwareRenderer = new GLFW_Rasterizer();

	//TODO: how to switch?
	GLFW_Rasterizer::Instance->Init(window, width, height);
	OGL_Renderer::Instance->Init(window, width, height);
	//Set current renderer
	Window::p_currentRenderer = GLFW_Rasterizer::Instance;

	// Print OpenGL and GLSL versions
	Window::p_currentRenderer->PrintVersions();
	Window::p_currentRenderer->Setup();

	// Set the key callback
	glfwSetErrorCallback(ErrorCallback);
	glfwSetKeyCallback(window, Window::key_callback);

	// Loop while GLFW window should stay open
	while (!glfwWindowShouldClose(window))
	{
		// Main render display callback. Rendering of objects is done here.
		Window::p_currentRenderer->DisplayCallback(window);
		// Idle callback. Updating objects, etc. can be done here.
		Window::idle_callback();
	}

	// Destroy the window
	glfwDestroyWindow(window);
	// Terminate GLFW
	glfwTerminate();

	exit(EXIT_SUCCESS);
}