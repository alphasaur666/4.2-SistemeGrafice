#include "Billboard.h"

// Read the Object name and Texture name
Billboard::Billboard(string filename, string textName) : ObjLoader(filename)
{
	texID = Scene::GetTexture(textName);
	_runtime = 0.0f;
	spread = 0.0f;
}

void Billboard::Display()
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

	// Draw the Billboard
	Draw();

	glPopAttrib();
	glPopMatrix();
}

void Billboard::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glBegin(GL_TRIANGLES);

	int mtlNow = 1;

	for (int i = 0; i < (int)fvSets.size(); i++) {
		// Change the Material
		if (i == mtlNum[mtlNow]) {
			mtlNow++;
		}

		// Set the color
		switch (mtlNow) {
		case 1: // Dark
			glColor3ub(50, 50, 50);
			break;
		case 2: // Light
			glColor3ub(169, 169, 169);
			break;
		case 3: // White
			glColor3ub(255, 255, 255);
			break;
		case 4: // Post (Texture)
			break;
		}

		if (mtlNow == 4) {
			continue;
		}

		// Using Triangles to draw
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

void Billboard::DrawTexture()
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
	glTexCoord2f(1.0f, spread);
	glVertex3f(vSets[23][0], vSets[23][1], vSets[23][2]);
	glTexCoord2f(1.0f, spread + 0.5f);
	glVertex3f(vSets[20][0], vSets[20][1], vSets[20][2]);
	glTexCoord2f(0.0f, spread + 0.5f);
	glVertex3f(vSets[64][0], vSets[64][1], vSets[64][2]);
	glTexCoord2f(0.0f, spread);
	glVertex3f(vSets[67][0], vSets[67][1], vSets[67][2]);
	glEnd();
	glEnable(GL_COLOR_MATERIAL);

	// Bind to the blank buffer to stop ourselves accidentaly using the wrong texture in the next draw call
	glBindTexture(GL_TEXTURE_2D, NULL);

	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);

	glPopAttrib();
	glPopMatrix();
}

// Update the post
void Billboard::Update(const double& deltaTime)
{
	_runtime += deltaTime;
	int timeTemp = (int)_runtime % 6;

	// Going up
	if ((timeTemp == 2) && (spread < 0.5f)) {
		spread += 0.01f;
	}

	// Going down
	if ((timeTemp == 5) && (spread > 0.0f)) {
		spread -= 0.01f;
	}
}
