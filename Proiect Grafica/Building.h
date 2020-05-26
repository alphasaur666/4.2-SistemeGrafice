#pragma once

#include "ObjLoader.h"

class Building : public ObjLoader
{
public:
	Building(string filename, string textureName);
	~Building() {};
	void Display();
private:
	void Draw();
	void DrawTexture();
	int texID;
};
