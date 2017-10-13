//
// Created by Jip Boesenkool on 11/10/2017.
//
#include "GLFW_Rasterizer.h"
#include "Window.h"

#include <iostream>
#include <math.h>
using namespace std;

GLFW_Rasterizer *GLFW_Rasterizer::Instance;

//Public Functions
GLFW_Rasterizer::GLFW_Rasterizer( )
{
	Instance = this;
}

void GLFW_Rasterizer::Init( GLFWwindow *window, int width, int height )
{
#ifdef __APPLE__
	int scale = 2; // multiplier for retina display
#else
	int scale = 1;
#endif
	m_width = width * scale;
	m_height = height * scale;
	mp_pixels = new float[m_width * m_height* 3];

	mp_window = window;
}

void GLFW_Rasterizer::Setup()
{
	Window::rendererIsOgl = false;
	SetupCallbacks();
}

//Private Functions
void GLFW_Rasterizer::SetupCallbacks()
{
	// Set the window resize callback
	glfwSetWindowSizeCallback(mp_window, glfw_ResizeCallback);
}

// Called whenever the window size changes
void GLFW_Rasterizer::ResizeCallback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	int scale = 2; // multiplier for retina display
#else
	int scale = 1;
#endif
	m_width = width * scale;
	m_height = height * scale;
	delete[] mp_pixels;
	mp_pixels = new float[m_width * m_height * 3];
}

void GLFW_Rasterizer::DisplayCallback(GLFWwindow* window)
{
	ClearBuffer();

	Rasterize();

	// glDrawPixels writes a block of pixels to the framebuffer
	glDrawPixels(m_width, m_height, GL_RGB, GL_FLOAT, mp_pixels);

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

//Static callbacks for GLFW
void GLFW_Rasterizer::glfw_ResizeCallback(GLFWwindow* window, int width, int height)
{
	GLFW_Rasterizer::Instance->ResizeCallback(window, width, height);
}

//Private Functions
// Clear frame buffer
void GLFW_Rasterizer::ClearBuffer()
{
	Color clearColor = { 0.0, 0.0, 0.0 };   // clear color: black
	for (int i = 0; i<m_width*m_height; ++i)
	{
		mp_pixels[i * 3] = clearColor.r;
		mp_pixels[i * 3 + 1] = clearColor.g;
		mp_pixels[i * 3 + 2] = clearColor.b;
	}
}

// Draw a point into the frame buffer
void GLFW_Rasterizer::DrawPoint(int x, int y, float r, float g, float b)
{
	if(x > 0 && x < m_width && y > 0 && y < m_height){
		for(int xi = x; xi < x+Window::pointSize; xi++)
		{
			for(int yi = y; yi < y+Window::pointSize; yi++)
			{
				int offset = yi*m_width*3+xi*3;
				mp_pixels[offset] = r;
				mp_pixels[offset + 1] = g;
				mp_pixels[offset + 2] = b;
			}
		}
	}
}

void GLFW_Rasterizer::Rasterize()
{
	// Create transformations
	glm::mat4 model, view, projection, d, mvp, dmvp;
	model 		= Window::activeObject->toWorld;
	view = glm::lookAt(
			glm::vec3(0.0f, 0.0f, 20.0f),
			glm::vec3(0.0f, 0.0f, 19.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
	projection  = glm::perspective(glm::radians(60.0f), (GLfloat)m_width / (GLfloat)m_height, 1.0f, 1000.0f);
	int x0 = 0, x1 = m_width, y0 = 0, y1 = m_height;
	glm::vec4 viewport = glm::vec4(x0,y0,x1,y1);
	d 			= glm::mat4(
			(x1-x0)/2, 0, 0, (x0+x1)/2,
			0, (y1-y0)/2, 0, (y0+y1)/2,
			0,0,1.0f/2.0f,1.0f/2.0f,
			0,0,0,1 );
	mvp 		= projection * view * model;
	dmvp 		= d*mvp;

	// Put your main rasterization loop here
	// It should go over the point model and call drawPoint for every point in it
	glm::vec4 vertex;
	glm::vec3 normal;
	glm::vec3 offset = glm::vec3(0.5f);
	for(int i = 0; i < Window::activeObject->vertices.size(); i++)
	{
		vertex = glm::vec4(Window::activeObject->vertices[i],1.0f);
		//NOTE: ask TA why the manual dmvp does not work?! the d matrix is to blame!
		//vertex = dmvp*vertex;
		glm::vec3 projected = glm::project(Window::activeObject->vertices[i], view*model, projection, viewport);

		normal = glm::normalize( Window::activeObject->normals[i] );
		// -1 * 0.5 = -0.5 + 0.5 = 0, 1 * 0.5 = 0.5 + 0.5 = 1
		normal = (offset * normal) + offset;
		//DrawPoint((int)vertex.x, (int)vertex.y, normal.x, normal.y, normal.z);
		DrawPoint((int)projected.x, (int)projected.y, normal.x, normal.y, normal.z);
	}

}
