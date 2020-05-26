#pragma once

#include "DisplayableObject.h"
#include "Input.h"
#include "VectorMath.h"

#include <math.h>
#include <string>

#define _LIGHT_0 0

using namespace std;

class Light : public DisplayableObject, public Input
{
public:
	Light(Camera* pCamera, string textureName1, string textureName2);
	~Light();
	void Display();
	void HandleKey(unsigned char key, int state, int mX, int mY);
private:
	void BillBoard();
	Camera* m_pCamera;
	GLfloat* _ambient, * _diffuse, * _specular, * _position;
	int lightState;
	int texID1, texID2;
};
