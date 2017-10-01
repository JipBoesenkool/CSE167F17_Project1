#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h> // Remove this line in future projects
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

#include <fstream>
#include <sstream>
#include <string>

class OBJObject
{
//Members
private:
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	glm::mat4 toWorld;
	float angle;

//Functions
public:
	OBJObject();
	OBJObject(const char* filepath);

	void parse(const char* filepath);
	void draw();
	void update();

private:
	void spin(float deg);
};

#endif