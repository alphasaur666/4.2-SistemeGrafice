#include "ObjLoader.h"

#include <fstream>
#include <iostream>

using namespace std;

ObjLoader::ObjLoader(string filename)
{
	Load(filename);
}

void ObjLoader::Load(string filename)
{
	// Open the object file
	string line;
	fstream f;

	f.open(filename, ios::in);

	if (!f.is_open()) {
		printf("Something Went Wrong When Opening Objfiles\n");
	}

	// Read line
	while (!f.eof()) {
		getline(f, line);
		vector<string>para;
		string ans = "";

		// Read word and Add to para
		line.append(" ");
		for (int i = 0; i < (int)line.length(); i++) {
			char ch = line[i];

			if (ch != ' ') {
				ans += ch;
			}
			else {
				para.push_back(ans);
				ans = "";
			}
		}

		if ((para.size() != 4) && (para[0] != "usemtl")) {
			continue;
		}

		if (para[0] == "v") { // Save vector
			vector<float> point;

			for (int i = 1; i < 4; i++) {
				float xyz = (float)atof(para[i].c_str());
				point.push_back(xyz);
			}

			vSets.push_back(point);
		}
		else if (para[0] == "vn") { // Save normal vector
			vector<float> point;

			for (int i = 1; i < 4; i++) {
				float xyz = (float)atof(para[i].c_str());
				point.push_back(xyz);
			}

			vnSets.push_back(point);
		}
		else if (para[0] == "f") { // Save face
			mtlNum[mtlNum[0]]++;
			vector<int> vIndex;
			vector<int> vnIndex;

			for (int i = 1; i < 4; i++) {
				string temp = para[i];
				string ans = "";
				int step = 0;

				for (int j = 0; j < (int)temp.length(); j++) {
					char ch = temp[j];

					if (ch != '/') {
						ans += ch;
					}
					else if (step == 0) { // Save index of vector in the face
						int index = atoi(ans.c_str());
						index--;
						vIndex.push_back(index);
						step++;
						ans = "";
					}
					else if (step == 1) { // Skip the vt (vector texture)
						step++;
						ans = "";
					}

					if ((step == 2) && (j == temp.length() - 1)) { // Save index of normal vector in the face
						int index = atoi(ans.c_str());
						index--;
						vnIndex.push_back(index);
					}
				}
			}

			fvSets.push_back(vIndex);
			fvnSets.push_back(vnIndex);
		}
		else if (para[0] == "usemtl") { // Record the material
			mtlNum[mtlNum[0] + 1] += mtlNum[mtlNum[0]];
			mtlNum[0]++;
		}
	}

	f.close();
}
