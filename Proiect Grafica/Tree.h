#pragma once

#include "ObjLoader.h"

class Tree : public ObjLoader
{
public:
	Tree(string filename);
	~Tree() {};
	void Display();
private:
	void Draw();
};
