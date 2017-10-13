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
public:
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	glm::mat4 toWorld;
private:
	glm::vec3 position;
	glm::vec3 rotation;
	float scale = 1;

//Functions
public:
	OBJObject();
	OBJObject(const char* filepath);

	void parse(const char* filepath);
	void draw();
	void update();

	void move(glm::vec3 direction);
	void rotate(glm::vec3 rotation);
	void manualRotation(float deg);
	void automaticRotation();
	void scaleObject(bool scaleUp);

	void resetPosition();
	void resetRotation();
	void resetScale();
};

#endif