#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

class TrafficLight : public DisplayableObject, public Animation
{
public:
	TrafficLight();
	~TrafficLight();
	void Display();
	void Update(const double& deltaTime);
private:
	void Draw();
	void DrawCylinder(float h, float r);
	void DrawCuboid(float l, float w, float h);
	GLfloat hPole, rPole, wCuboid, hCuboid, wConvex;
	int state;
	double _runtime;
};
