#pragma once

#include "DisplayableObject.h"

#include <string>
#include <vector>

using namespace std;

class ObjLoader : public DisplayableObject
{
public:
	ObjLoader(string filename);
	~ObjLoader() {};
	void Load(string filename);
	vector<vector<float>> vSets;
	vector<vector<float>> vnSets;
	vector<vector<int>> fvSets;
	vector<vector<int>> fvnSets;
	int mtlNum[10];
};
