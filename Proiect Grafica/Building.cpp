#include "Building.h"

// Read object namem and texture
Building::Building(string filename, string textName) : ObjLoader(filename)
{
	texID = Scene::GetTexture(textName);
}

void Building::Display()
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

void Building::Draw()
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
		case 1: // Wall
			glColor3ub(117, 117, 117);
			break;
		case 2: // Window
			glColor3ub(87, 176, 210);
			break;
		case 3: // Blue
			glColor3ub(0, 84, 128);
			break;
		case 4: // Logo
			break;
		case 5: // Yellow
			glColor3ub(251, 192, 45);
			break;
		case 6: // Black
			glColor3ub(33, 33, 33);
			break;
		}

		// Texture
		if (mtlNow == 4) {
			continue;
		}

		// Use Triangles to draw
		for (int j = 0; j < 3; j++) {
			int vIndex = fvSets[i][j];
			int vnIndex = fvnSets[i][j];
			glNormal3f(vnSets[vnIndex][0], vnSets[vnIndex][1], vnSets[vnIndex][2]);
			glVertex3f(vSets[vIndex][0], vSets[vIndex][1], vSets[vIndex][2]);
		}
	}

	glEnd();
	glPopAttrib();
	DrawTexture();
}

void Building::DrawTexture()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_COLOR_MATERIAL);

	// Enable Texturing
	glEnable(GL_TEXTURE_2D);

	// Tell openGL which texture buffer to use
	glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(vSets[65][0], vSets[65][1], vSets[65][2]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(vSets[64][0], vSets[64][1], vSets[64][2]);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(vSets[181][0], vSets[181][1], vSets[182][2]);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(vSets[182][0], vSets[182][1], vSets[182][2]);
	glEnd();
	glEnable(GL_COLOR_MATERIAL);

	// Bind to the blank buffer to stop ourselves accidentaly using the wrong texture in the next draw call
	glBindTexture(GL_TEXTURE_2D, NULL);

	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);

	glPopAttrib();
	glPopMatrix();
}
