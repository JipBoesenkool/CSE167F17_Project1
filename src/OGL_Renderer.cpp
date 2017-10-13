//
// Created by Jip Boesenkool on 11/10/2017.
//

#include "OGL_Renderer.h"
#include "Window.h"

OGL_Renderer *OGL_Renderer::Instance;

//Public functions
OGL_Renderer::OGL_Renderer( )
{
	OGL_Renderer::Instance = this;
}

void OGL_Renderer::Init( GLFWwindow *window, int width, int height )
{
	m_width = width;
	m_height = height;

	mp_window = window;
}

void OGL_Renderer::Setup()
{
	Window::rendererIsOgl = true;

	SetupCallbacks();
	// Setup OpenGL settings, including lighting, materials, etc.
	SetupOpenglSettings();

	Window::resize_callback(mp_window, m_width, m_height);
}

//Private functions
void OGL_Renderer::SetupMaterials()
{
	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float shininess[] = { 100.0 };

	// Enable color materials
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void OGL_Renderer::SetupLighting()
{
	// Enable lighting
	glEnable(GL_LIGHTING);
	// Enable Local Viewer Light Model
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	// Lightsource position
	float position[] = { 10.0, 10.0, 10.0, 1.0 };

	// Generate light source
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	// Enable GL_LIGHT0
	glEnable(GL_LIGHT0);
}

void OGL_Renderer::SetupOpenglSettings()
{
	// Enable depth buffering
	glEnable(GL_DEPTH_TEST);
	// Related to shaders and z value comparisons for the depth buffer
	glDepthFunc(GL_LEQUAL);
	// Set polygon drawing mode to fill front and back of each polygon
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Disable backface culling to render both sides of polygons
	glDisable(GL_CULL_FACE);
	// Set clear color to black
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// Set shading to smooth
	glShadeModel(GL_SMOOTH);
	// Auto normalize surface normals
	glEnable(GL_NORMALIZE);

	// Setup materials
	SetupMaterials();
	// Setup lighting
	SetupLighting();
}

void OGL_Renderer::SetupCallbacks()
{
	// Set the window resize callback
	glfwSetWindowSizeCallback(mp_window, Window::resize_callback);
}

void OGL_Renderer::DisplayCallback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Set the matrix mode to GL_MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	// Load the identity matrix
	glLoadIdentity();

	glPointSize(Window::pointSize);
	// Render objects
	//cube.draw();

	Window::activeObject->draw();

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}