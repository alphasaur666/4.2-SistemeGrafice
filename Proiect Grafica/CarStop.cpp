#include "CarStop.h"

// Car stop on the parking area
CarStop::CarStop(string filename) : ObjLoader(filename)
{
}

void CarStop::Display()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rotation[1], 0.f, 1.f, 0.f);
	glRotatef(rotation[0], 1.f, 0.f, 0.f);
	glRotatef(rotation[2], 0.f, 0.f, 1.f);

	Draw();

	glPopAttrib();
	glPopMatrix();
}

void CarStop::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glBegin(GL_TRIANGLES);

	int mtlNow = 1;

	for (int i = 0; i < (int)fvSets.size(); i++) {
		// Change the material
		if (i == mtlNum[mtlNow]) {
			mtlNow++;
		}

		// Set the color
		switch (mtlNow) {
		case 1: // Black
			glColor3ub(0, 0, 0);
			break;
		case 2: // White
			glColor3ub(255, 255, 255);
			break;
		case 3: // Window
			glColor3ub(175, 238, 238);
			break;
		case 4: // Sliver
		case 5: // Sliver
			glColor3ub(169, 169, 169);
			break;
		case 6: // Blue
			glColor3ub(30, 144, 255);
			break;
		case 7: // Brown
			glColor3ub(210, 105, 30);
			break;
		}

		//	Use Triangles to draw
		for (int j = 0; j < 3; j++) {
			int vIndex = fvSets[i][j];
			int vnIndex = fvnSets[i][j];
			glNormal3f(vnSets[vnIndex][0], vnSets[vnIndex][1], vnSets[vnIndex][2]);
			glVertex3f(vSets[vIndex][0], vSets[vIndex][1], vSets[vIndex][2]);
		}
	}

	glEnd();
	glPopAttrib();
}
