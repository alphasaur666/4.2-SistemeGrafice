#include "Road.h"

Road::Road(float _height)
{
	height = _height;
	bWidth = 300.0f;
	bLength = 300.0f;
	wWidth = 15.0f;
	wLength = 120.0f;
	zebraWidth = 30.0f;
	zebraLength = 250.0f;
	sidewalkWidth = 100.0f;
	sidewalkHeight = 5.0f;
}

void Road::Display()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rotation[1], 0.f, 1.f, 0.f);
	glRotatef(rotation[0], 1.f, 0.f, 0.f);
	glRotatef(rotation[2], 0.f, 0.f, 1.f);

	Draw();

	glPopAttrib();
	glPopMatrix();
}

void Road::Draw()
{
	// Draw the black part of the road
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float shininess = 128.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, static_cast<GLfloat*>(specular));
	glMaterialf(GL_FRONT, GL_SHININESS, static_cast<GLfloat>(shininess));
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, static_cast<GLfloat*>(diffuse));

	glColor3ub(25, 25, 25);
	DrawRectangle(8 * bLength, bWidth, height);
	glPushMatrix();
	glTranslatef(bLength, 0.0f, (GLfloat)(1.5 * bWidth));
	DrawRectangle(2 * bLength, 2 * bWidth, height);
	glPopMatrix();

	for (int i = -4; i < 4; i++) {
		glPushMatrix();
		GLfloat pos = i * bLength + bLength / 2;
		glTranslatef(pos, 0.0f, 0.0f);

		if (i == -1) {
			// Draw the zebra crossing
			glColor3f(1.0f, 1.0f, 1.0f);

			for (int j = -5; j < 5; j += 2) {
				glPushMatrix();
				GLfloat tempPos = j * zebraWidth + zebraWidth;
				glTranslatef(0.0f, 0.0f, tempPos);
				DrawRectangle(zebraLength, zebraWidth, height + 1);
				glPopMatrix();
			}
		}
		else if (i == 0 || i == 1) {
			// Do nothing
		}
		else if (i == 2) {
			// Draw the stop line
			glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			DrawRectangle(wLength, wWidth, height + 1);
			glTranslatef(-wLength / 2 - zebraWidth / 2, 0.0f, bWidth / 4 - wWidth / 4);
			DrawRectangle(zebraWidth, bWidth / 2 + wWidth / 2, height + 1);
			glPopMatrix();
		}
		else {
			// Draw the white line
			glColor3f(1.0f, 1.0f, 1.0f);
			DrawRectangle(wLength, wWidth, height + 1);
		}

		glPopMatrix();
	}

	// Draw the parking area
	glPushMatrix();
	glTranslatef(bLength, 0.0f, (GLfloat)(2.5 * bLength - zebraLength / 2));

	for (int i = -1; i < 2; i++) {
		glPushMatrix();
		glTranslatef(-bLength * i / 2, 0.0f, 0.0f);
		DrawRectangle(wWidth, zebraLength, height + 1);
		glPopMatrix();
	}

	glPopMatrix();

	// Draw the sidewalk
	glPushMatrix();
	glTranslatef(0.0f, height, -bWidth / 2 - sidewalkWidth / 2);
	glColor3f(0.5f, 0.5f, 0.5f);
	DrawCuboid(8 * bLength, sidewalkWidth, sidewalkHeight);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2 * bLength, height, (GLfloat)(1.5 * bWidth + sidewalkWidth / 2));
	glColor3f(0.5f, 0.5f, 0.5f);
	DrawCuboid(4 * bLength, sidewalkWidth + 2 * bWidth, sidewalkHeight);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(bLength, height, (GLfloat)(2.5 * bWidth + sidewalkWidth / 2));
	glColor3f(0.5f, 0.5f, 0.5f);
	DrawCuboid(2 * bLength, sidewalkWidth, sidewalkHeight);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3 * bLength, height, (GLfloat)(1.5 * bWidth + sidewalkWidth / 2));
	glColor3f(0.5f, 0.5f, 0.5f);
	DrawCuboid(2 * bLength, 2 * bWidth + sidewalkWidth, sidewalkHeight);
	glPopMatrix();

	// Draw the graassland
	glPushMatrix();
	glTranslatef(-3 * bLength - sidewalkWidth / 2, height, (GLfloat)(1.5 * bWidth + sidewalkWidth));
	glColor3ub(34, 139, 34);
	DrawRectangle(2 * bLength - sidewalkWidth, 2 * bLength, sidewalkHeight + 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3 * bLength + sidewalkWidth / 2, height, 2 * bWidth + sidewalkWidth / 2);
	glColor3ub(34, 139, 34);
	DrawRectangle(2 * bLength - sidewalkWidth, bLength + sidewalkWidth, sidewalkHeight + 1);
	glPopMatrix();
}

void Road::DrawRectangle(float l, float w, float _height)
{
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(l / 2, _height, -w / 2);
	glVertex3f(-l / 2, _height, -w / 2);
	glVertex3f(-l / 2, _height, w / 2);
	glVertex3f(l / 2, _height, w / 2);
	glEnd();
}

void Road::DrawCuboid(float l, float w, float h)
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
