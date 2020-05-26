#pragma once

#include "ObjLoader.h"

class CarStop : public ObjLoader
{
public:
	CarStop(string filename);
	~CarStop() {};
	void Display();
private:
	void Draw();
};
