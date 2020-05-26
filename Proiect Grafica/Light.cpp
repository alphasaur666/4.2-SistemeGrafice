#include "Light.h"

// Get the point of Camera, and texture1 (Moon), texture2 (Sun)
Light::Light(Camera* pCamera, string textureName1, string textureName2)
{
	static GLfloat position[] =
	{
		0.0f, -100.0f, 0.0f, 1.0f,
	};
	_position = position;

	static GLfloat ambient[] =
	{
		0.1f, 0.1f, 0.1f, 1.0f,
	};
	_ambient = ambient;

	static GLfloat diffuse[] =
	{
		0.8f, 0.8f, 0.8f, 1.0f,
	};
	_diffuse = diffuse;

	static GLfloat specular[] =
	{
		0.8f, 0.8f, 0.8f, 1.0f,
	};
	_specular = specular;

	m_pCamera = pCamera;
	lightState = 0;

	texID1 = Scene::GetTexture(textureName1);
	texID2 = Scene::GetTexture(textureName2);
}

Light::~Light()
{
}

void Light::Display()
{
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);

	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	BillBoard();

	glDisable(GL_COLOR_MATERIAL);

	// Enable Texturing
	glEnable(GL_TEXTURE_2D);

	// Tell openGL which texture buffer to use
	if (lightState == 0) {
		glBindTexture(GL_TEXTURE_2D, texID2);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, texID1);
	}

	glBegin(GL_QUADS);
	float temp = 50.0f;
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(temp, temp, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-temp, temp, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-temp, -temp, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(temp, -temp, 0.0f);
	glEnd();

	glEnable(GL_COLOR_MATERIAL);

	// Bind to the blank buffer to stop ourselves accidentaly using the wrong texture in the next draw call
	glBindTexture(GL_TEXTURE_2D, NULL);

	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);

	glPopAttrib();
	glPopMatrix();

	glEnable(GL_LIGHTING);

	// Set the light
	glLightfv(GL_LIGHT1, GL_POSITION, &_position[_LIGHT_0]);
	glLightfv(GL_LIGHT1, GL_AMBIENT, &_ambient[_LIGHT_0]);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, &_diffuse[_LIGHT_0]);
	glLightfv(GL_LIGHT1, GL_SPECULAR, &_specular[_LIGHT_0]);

	static GLfloat spot_direction[] = { 0.0f, -1.0f, 0.0f };
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 50.0f);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, static_cast<GLfloat*>(spot_direction));
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0f);

	// Switch the light according to light state
	if (lightState == 0) {
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
	}

	glPopMatrix();
}

// Press E to switch the day
void Light::HandleKey(unsigned char key, int state, int mX, int mY)
{
	// If key pressed down
	if (state == 1) {
		switch (key) {
		case 'E':
		case 'e':
			lightState = (lightState + 1) % 2;
			break;
		}
	}
}

// Billboard using on the Texture (Sun and Moon)
void Light::BillBoard()
{
	float camX, camY, camZ, angleCosine;
	float objToCamProj[3];
	float lookAt[3];
	float upAux[3];
	float objToCam[3];

	m_pCamera->GetEyePosition(camX, camY, camZ);

	objToCamProj[0] = camX - pos[0];
	objToCamProj[1] = 0;
	objToCamProj[2] = camZ - pos[2];

	lookAt[0] = 0;
	lookAt[1] = 0;
	lookAt[2] = 1;

	norm(objToCamProj);
	cross(lookAt, objToCamProj, upAux);
	dot(lookAt, objToCamProj, angleCosine);

	if ((angleCosine < 0.99990) && (angleCosine > -0.9999)) {
		glRotatef(acos(angleCosine) * 180 / M_PI, upAux[0], upAux[1], upAux[2]);
	}

	objToCam[0] = camX - pos[0];
	objToCam[1] = camY - pos[1];
	objToCam[2] = camZ - pos[2];
	norm(objToCam);
	dot(objToCamProj, objToCam, angleCosine);

	if ((angleCosine < 0.99990) && (angleCosine > -0.9999)) {
		if (objToCam[1] < 0) {
			glRotatef(acos(angleCosine) * 180 / M_PI, 1, 0, 0);
		}
		else {
			glRotatef(acos(angleCosine) * 180 / M_PI, -1, 0, 0);
		}
	}
}
