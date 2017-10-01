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
	FILE* fp;     // file pointer
	float vx, vy, vz;  // vertex coordinates
	float vnx, vny, vnz;  // vertex normals
	float r,g,b;  // vertex color
	int c1,c2;    // characters read from file
	char str [64];

	fp = fopen(filepath,"rb");  // make the file name configurable so you can load other files
	if (fp==NULL)
	{
		std::cerr << "error loading file" << std::endl;
		exit(-1);
	}  // just in case the file can't be found or is corrupt

	//TODO: error prone, does this count as any error in the parser?
	while( !feof(fp) )
	{
		c1 = fgetc(fp);
		c2 = fgetc(fp);
		if (c1=='v' && c2==' ')
		{
			fscanf(fp, "%f %f %f %f %f %f", &vx, &vy, &vz, &r, &g, &b);
			vertices.push_back( glm::vec3(vx,vy,vz) );
			//TODO: store colors
		}
		else if (c1=='v' && c2=='n')
		{
			fscanf(fp, "%f %f %f", &vnx, &vny, &vnz);
			vertices.push_back( glm::vec3(vnx,vny,vnz) );
		}
		else
		{
			fgets(str, 64, fp);
		}
	}

	fclose(fp);   // make sure you don't forget to close the file when done

	//TODO parse the OBJ file
	// Populate the face indices, vertices, and normals vectors with the OBJ Object data
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
	}
	glEnd();

	// Pop the save state off the matrix stack
	// This will undo the multiply we did earlier
	glPopMatrix();
}