//
// Created by Jip Boesenkool on 11/10/2017.
//

#ifndef CSE167_PROJECT1_GLFW_RASTERIZER_H
#define CSE167_PROJECT1_GLFW_RASTERIZER_H
#include "IRenderer.h"
#include "OBJObject.h"

//Typedef
struct Color    // generic color class
{
	float r, g, b;  // red, green, blue
};

class GLFW_Rasterizer : public IRenderer
{
//Members
public:
	float* mp_pixels;
	static GLFW_Rasterizer *Instance;
private:
//Functions
public:
	GLFW_Rasterizer();
	virtual void Init(GLFWwindow* window, int width, int height) override;
	virtual void Setup() override;

	void ResizeCallback(GLFWwindow* window, int width, int height);
	virtual void DisplayCallback(GLFWwindow* window) override;

	//Static callbacks for GLFW
	static void glfw_ResizeCallback(GLFWwindow* window, int width, int height);
private:
	void SetupCallbacks();

	void ClearBuffer();
	void DrawPoint(int x, int y, float r, float g, float b);
	void Rasterize();
};

#endif //CSE167_PROJECT1_GLFW_RASTERIZER_H
