//
// Created by Jip Boesenkool on 11/10/2017.
//
#ifndef CSE167_PROJECT1_OGL_RENDERER_H
#define CSE167_PROJECT1_OGL_RENDERER_H
#include "IRenderer.h"

class OGL_Renderer : public IRenderer
{
//Members
public:
	static OGL_Renderer *Instance;
private:
//Functions
public:
	OGL_Renderer( );

	virtual void Init(GLFWwindow* window, int width, int height) override;
	virtual void Setup() override;
	virtual void DisplayCallback(GLFWwindow* window) override;
private:
	void SetupMaterials();
	void SetupLighting();
	void SetupOpenglSettings();

	void SetupCallbacks();
};

#endif //CSE167_PROJECT1_OGL_RENDERER_H
