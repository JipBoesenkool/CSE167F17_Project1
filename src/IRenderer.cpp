//
// Created by Jip Boesenkool on 11/10/2017.
//
#include "IRenderer.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>

//public functions
void IRenderer::PrintVersions()
{
	// Get info of GPU and supported OpenGL version
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

	//If the shading language symbol is defined
#ifdef GL_SHADING_LANGUAGE_VERSION
	std::printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif
}
