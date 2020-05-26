#pragma once

#include "Engine.h"
#include "Texture.h"
#include "Camera.h"

#include <vector>

class DisplayableObject;

class Scene : public Engine
{
public:
	Scene(int argc, char** argv, const char* title, const int& windowWidth, const int& windowHeight);
	virtual ~Scene();
	static int GetWindowWidth();
	static int GetWindowHeight();
	static int GetTexture(std::string fileName);
	static Camera* GetCamera() {
		return &camera;
	}
protected:
	virtual void Initialise() = 0;
	void Draw();
	void Reshape(int w, int h);
	virtual void Projection();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);
	void HandleMouse(int button, int state, int x, int y);
	void HandleMouseDrag(int x, int y);
	void HandleMouseMove(int x, int y);
	void AddObjectToScene(DisplayableObject* obj);
private:
	static Camera camera;
	static Texture texture;
	std::vector<DisplayableObject*> objects;
};
