#pragma once

#include <GL/glut.h>
#include <Windows.h>

#include "Input.h"

class Camera : public Input
{
public:
	Camera();
	virtual ~Camera() {};
	void GetEyePosition(float& x, float& y, float& z) const;
	void GetViewDirection(float& x, float& y, float& z) const;
	void GetForwardVector(float& x, float& y, float& z) const;
	void GetRightVector(float& x, float& y, float& z) const;
	void GetUpVector(float& x, float& y, float& z) const;
	virtual void Update(const double& deltaTime);
	virtual void Reset();
	virtual void SetViewport();
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y) {};
	void HandleMouse(int button, int state, int x, int y);
	void HandleMouseDrag(int x, int y);
	void HandleMouseMove(int x, int y) {};
	virtual void SetupCamera();
private:
	float eyePosition[3];
	float vd[3];
	float forward[3];
	float right[3];
	float up[3];
	int wKey, sKey, aKey, dKey, rKey, fKey;
	int windowWidth, windowHeight;
	int currentButton;
	GLint mouseX, mouseY;
	int timeState;
};
