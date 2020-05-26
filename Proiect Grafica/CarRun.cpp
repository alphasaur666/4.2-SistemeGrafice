#include "CarRun.h"

// Car run on the road
CarRun::CarRun(string filename) : ObjLoader(filename)
{
	_runtime = 0.0;
	speedMax = 4.5f;
	speed = speedMax;
	acceleration = 0.3f;
	rotation[1] = 90.0;
}

CarRun::~CarRun()
{
}

void CarRun::Display()
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

void CarRun::Draw()
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
		case 1: // Orange
			glColor3ub(255, 140, 0);
			break;
		case 2: // White
			glColor3ub(255, 255, 255);
			break;
		case 3: // Light
			glColor3ub(255, 255, 0);
			break;
		case 4: // Sliver
			glColor3ub(169, 169, 169);
			break;
		case 5: // Black
			glColor3ub(0, 0, 0);
			break;
		case 6: // Window
			glColor3ub(175, 238, 238);
			break;
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
}

void CarRun::Update(const double& deltaTime)
{
	_runtime += deltaTime;
	int timeTemp = (int)_runtime % 30; // 0-19 green ----- 20-21 yellow ----- 22-27 red ----- 28-29 yellow
	pos[0] += speed;

	// Stop the car
	if ((((pos[0] > -450.0) && (pos[0] < -310.0) && (speed > 0)) || ((pos[0] > 670.0) && (pos[0] < 810.0) && (speed < 0))) && (timeTemp > 19)) {
		speed -= acceleration;

		if (((speed < 0) && (acceleration > 0)) || ((speed > 0) && (acceleration < 0))) {
			speed = 0;
		}
	}

	// Start the car
	if ((timeTemp < 20) && (abs(speed) < speedMax)) {
		speed += acceleration;

		if (abs(speed) > speedMax) {
			speed = speedMax * (speed / abs(speed));
		}
	}

	// Reposition the car
	if (pos[0] > 1200.0) {
		pos[0] = 1200.0;
		pos[2] += 150.0;
		rotation[1] *= -1;
		speed *= -1;
		acceleration *= -1;
	}

	if (pos[0] < -1200.0) {
		pos[0] = -1200.0;
		pos[2] -= 150.0;
		rotation[1] *= -1;
		speed *= -1;
		acceleration *= -1;
	}
}
