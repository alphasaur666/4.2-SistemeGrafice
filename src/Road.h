#pragma once

#include "DisplayableObject.h"

class Road : public DisplayableObject
{
public:
	Road(float _height);
	~Road() {};
	void Display();
private:
	void Draw();
	void DrawRectangle(float l, float w, float height);
	void DrawCuboid(float l, float w, float h);
	GLfloat bWidth, bLength;
	GLfloat wWidth, wLength;
	GLfloat height;
	GLfloat zebraWidth, zebraLength;
	GLfloat sidewalkWidth, sidewalkHeight;
};
