#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>

class Texture
{
public:
	Texture(void) {};
	~Texture(void);
	int GetTexture(std::string fileName);
private:
	std::map<int, std::string> textures;
};
