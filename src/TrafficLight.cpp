#include "TrafficLight.h"
#include "VectorMath.h"

TrafficLight::TrafficLight()
{
	hPole = 130.0f;
	rPole = 3.0f;
	hCuboid = 50.0f;
	wCuboid = 20.0f;
	wConvex = 1.0f;
	state = 0;
	_runtime = 0.0;
}

TrafficLight::~TrafficLight()
{
}

void TrafficLight::Display()
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

void TrafficLight::Draw()
{
	// Draw the pole
	glColor3ub(66, 66, 66);
	DrawCylinder(hPole, rPole);
	glTranslatef(0.0f, hPole, 0.0f);

	// Draw the cuboid
	glColor3ub(33, 33, 33);
	DrawCuboid(wCuboid, wCuboid, hCuboid);

	// Draw the convex
	// Bottom
	glTranslatef(0.0f, 0.0f, wCuboid / 2 + wConvex / 2);
	DrawCuboid(wCuboid, wConvex, wConvex);

	// Left
	glTranslatef(-wCuboid / 2 + wConvex / 2, 0.0f, 0.0f);
	DrawCuboid(wConvex, wConvex, hCuboid);

	// Right
	glTranslatef(wCuboid - wConvex, 0.0f, 0.0f);
	DrawCuboid(wConvex, wConvex, hCuboid);

	// Top
	glTranslatef(-wCuboid / 2 + wConvex / 2, hCuboid - wConvex, 0.0f);
	DrawCuboid(wCuboid, wConvex, wConvex);

	// Draw the lights
	glTranslatef(0.0f, -(hCuboid - wConvex) / 2, 0.0f);

	for (int i = -1; i < 2; i++) {
		glPushAttrib(GL_ALL_ATTRIB_BITS);

		switch (i) {
		case -1: // Green
			if (state == 0) {
				GLfloat LightEmission[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
				glMaterialfv(GL_FRONT, GL_EMISSION, LightEmission);
				glColor4fv(LightEmission);
			}
			else {
				glColor4f(0.0f, 1.0f, 0.0f, 0.1f);
			}
			break;
		case 0: // Yellow
			if (state == 1) {
				GLfloat LightEmission[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
				glMaterialfv(GL_FRONT, GL_EMISSION, LightEmission);
				glColor4fv(LightEmission);
			}
			else {
				glColor4f(1.0f, 1.0f, 0.0f, 0.1f);
			}
			break;
		case 1: // Red
			if (state == 2) {
				GLfloat LightEmission[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
				glMaterialfv(GL_FRONT, GL_EMISSION, LightEmission);
				glColor4fv(LightEmission);
			}
			else {
				glColor4f(1.0f, 0.0f, 0.0f, 0.1f);
			}
			break;
		}

		glPushMatrix();
		glTranslatef(0.0f, i * (hCuboid / 3), 0.0f);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		DrawCylinder(1.0f, 6.0f);
		glPopMatrix();
		glPopAttrib();
	}
}

void TrafficLight::DrawCylinder(float h, float r)
{
	float res = 0.25 * M_PI; // Resolution
	float x = r, z = 0.0f; // Initialise x and z on right of cylinder centre
	float t = 0.0f; // Initialise angle as 0

	do {
		glBegin(GL_QUADS);

		// Set the norm
		float tMid = t + res / 2;
		glNormal3f(cos(tMid), 0.0f, sin(tMid));

		// Create first points
		glVertex3f(x, 0.0f, z); // bottom
		glVertex3f(x, h, z); // top

		// Iterate around circle
		t += res; // Add increment to angle
		x = r * cos(t); // Move x and z around circle
		z = r * sin(t);

		// Close quad
		glVertex3f(x, h, z); // Top
		glVertex3f(x, 0.0f, z); // Bottom
		glEnd(); // End shape
	} while (t <= 2 * M_PI); // For a full circle (360 degrees)

	// Draw the top solid circle
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, h, 0.0f);

	for (float t = 2 * M_PI; t >= 0.0f; t -= res) {
		// Iterate angles of a circle
		// Equation of a circle
		x = r * cos(t); // x = radius * cos(angle);
		z = r * sin(t); // z = radius * sin(angle);
		glVertex3f(x, h, z);
	}

	x = r * cos(2 * M_PI); // x = radius * cos(angle);
	z = r * sin(2 * M_PI); // z = radius * sin(angle);
	glVertex3f(x, h, z);
	glEnd();

	// Draw the bottom solid circle
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 0, 0.0f);

	for (float t = 0.0f; t <= 2 * M_PI; t += res) {
		// Iterate angles of a circle
		// Equation of a circle
		x = r * cos(t); // x = radius * cos(angle);
		z = r * sin(t); // z = radius * sin(angle);
		glVertex3f(x, 0, z);
	}

	x = r * cos(0.0f); // x = radius * cos(angle);
	z = r * sin(0.0f); // z = radius * sin(angle);
	glVertex3f(x, 0, z);
	glEnd();
}

void TrafficLight::DrawCuboid(float l, float w, float h)
{
	// Darw the cuboid
	glBegin(GL_QUADS);

	// Draw the bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(l / 2, 0.0f, -w / 2);
	glVertex3f(l / 2, 0.0f, w / 2);
	glVertex3f(-l / 2, 0.0f, w / 2);
	glVertex3f(-l / 2, 0.0f, -w / 2);

	// Draw the top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(l / 2, h, -w / 2);
	glVertex3f(-l / 2, h, -w / 2);
	glVertex3f(-l / 2, h, w / 2);
	glVertex3f(l / 2, h, w / 2);

	// Draw the front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(l / 2, h, w / 2);
	glVertex3f(-l / 2, h, w / 2);
	glVertex3f(-l / 2, 0.0f, w / 2);
	glVertex3f(l / 2, 0.0f, w / 2);

	// Draw the back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(l / 2, h, -w / 2);
	glVertex3f(l / 2, 0.0f, -w / 2);
	glVertex3f(-l / 2, 0.0f, -w / 2);
	glVertex3f(-l / 2, h, -w / 2);

	// Draw the left
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-l / 2, h, w / 2);
	glVertex3f(-l / 2, h, -w / 2);
	glVertex3f(-l / 2, 0.0f, -w / 2);
	glVertex3f(-l / 2, 0.0f, w / 2);

	// Draw the right
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(l / 2, h, -w / 2);
	glVertex3f(l / 2, h, w / 2);
	glVertex3f(l / 2, 0.0f, w / 2);
	glVertex3f(l / 2, 0.0f, -w / 2);
	glEnd();
}

void TrafficLight::Update(const double& deltaTime)
{
	_runtime += deltaTime;
	int timeTemp = (int)_runtime % 30;

	if (timeTemp < 19) {
		state = 0; // Green
	}
	else if ((timeTemp > 20) && (timeTemp < 28)) {
		state = 2; // Red
	}
	else {
		state = 1; // Yellow
	}
}
