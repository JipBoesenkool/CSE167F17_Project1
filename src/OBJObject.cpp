#include "OBJObject.h"

OBJObject::OBJObject()
{
	toWorld = glm::mat4(1.0f);
}

OBJObject::OBJObject(const char *filepath) 
{
	toWorld = glm::mat4(1.0f);
	parse(filepath);
}

void OBJObject::parse(const char *filepath) 
{
	float vx, vy, vz;  // vertex coordinates
	float vnx, vny, vnz;  // vertex normals
	float r,g,b;  // vertex color
	std::string firstToken;
	//debug counter
#ifdef NDEBUG
	int counter = 0;
#endif

	std::ifstream file(filepath);
	std::string line;
	while ( std::getline(file, line) )
	{
		std::istringstream iss(line);
		iss >> firstToken;

#ifdef NDEBUG
		counter++;
		std::cout << "line " << counter << ": " << line << std::endl;
#endif

		if (firstToken == "v")
		{
			iss >> vx >> vy >> vz;// >> r >> g >> b;
			vertices.push_back( glm::vec3(vx,vy,vz) );
			//TODO: store colors
		}
		else if (firstToken == "vn")
		{
			iss >> vnx >> vny >> vnz;
			normals.push_back( glm::vec3(vnx,vny,vnz) );
		}
		else if(firstToken == "f")
		{
			//NOTE: Optimization we don't care about the rest of the file
			break;
		}
	}
}

void OBJObject::draw() 
{
	glMatrixMode(GL_MODELVIEW);

	// Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf(&(toWorld[0][0]));

	glBegin(GL_POINTS);
	// Loop through all the vertices of this OBJ Object and render them
	for (unsigned int i = 0; i < vertices.size(); ++i) 
	{
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
//Assignment 3. Change color depending on normal
		glm::vec3 norm = glm::normalize( normals[i] );
		glColor3f(norm.x, norm.y, norm.z);
	}
	glEnd();

	// Pop the save state off the matrix stack
	// This will undo the multiply we did earlier
	glPopMatrix();
}

void OBJObject::update()
{
	spin(1.0f);
}

//Private Functions
void OBJObject::spin(float deg)
{
	this->angle += deg;
	if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;
	// This creates the matrix to rotate the cube
	this->toWorld = glm::rotate(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
}