#include "Tree.h"

Tree::Tree(string filename) : ObjLoader(filename)
{
}

void Tree::Display()
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

void Tree::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);

	int mtlNow = 1;

	for (int i = 0; i < (int)fvSets.size(); i++) {
		if (i == mtlNum[mtlNow]) {
			mtlNow++;
		}

		// Set the color
		switch (mtlNow) {
		case 1: // Green
			glColor3ub(46, 125, 50);
			break;
		case 2: // Brown
			glColor3ub(62, 39, 35);
			break;
		default:
			break;
		}

		// Using Triangls to draw
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
