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
	glm::vec3 offset = glm::vec3(0.5f);
	for (unsigned int i = 0; i < vertices.size(); ++i) 
	{
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
//Assignment 3. Change color depending on normal
		// after normalize values are -1 to 1, convert them to 0, 1
		glm::vec3 norm = glm::normalize( normals[i] );
		norm = (offset * norm) + offset;
		// -1 * 0.5 = -0.5 + 0.5 = 0, 1 * 0.5 = 0.5 + 0.5 = 1
		glColor3f(norm.x, norm.y, norm.z);
	}
	glEnd();

	// Pop the save state off the matrix stack
	// This will undo the multiply we did earlier
	glPopMatrix();
}

void OBJObject::update()
{
	//update data for rendering
	automaticRotation();
	glm::mat4 transform(1);
	transform = glm::translate(transform, position);
	transform = glm::rotate(transform, this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(this->scale));
	this->toWorld = transform;
}

void OBJObject::move(glm::vec3 direction)
{
	position += direction;
}

void OBJObject::rotate(float deg)
{
	this->angle += deg;
	if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;
}

void OBJObject::automaticRotation()
{
	if(rotateCooldown > 0)
	{
		rotateCooldown -= 1;
	}
	else
	{
		rotate(1.0f);
	}
}

void OBJObject::manualRotation(float deg)
{
	rotateCooldown = 60;
	rotate(deg);
}

void OBJObject::scaleObject(bool scaleUp)
{
	(scaleUp) ? scale *= 2 : scale /= 2;
}

void OBJObject::resetPosition()
{
	this->position = glm::vec3(0);
}

void OBJObject::resetRotation()
{
	this->angle = 0.0f;
}

void OBJObject::resetScale()
{
	this->scale = 1.0f;
}