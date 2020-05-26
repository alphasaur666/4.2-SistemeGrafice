#pragma once

#include <GL/glut.h>
#include <Windows.h>

class Engine
{
public:
	Engine(int argc, char** argv, const char* title, const int& windowWidth, const int& windowHeight);
	virtual ~Engine() {};
	virtual void Run();
	static Engine* GetCurrentInstance();
	static const char* GetWindowTitle();
	static int GetWindowID();
	static int GetWindowWidth();
	static int GetWindowHeight();
protected:
	static Engine* current;
	static const char* windowTitle;
	static int windowID;
	static int windowWidth;
	static int windowHeight;
	static int time;
	static void InitFunc();
	static void DrawFunc();
	static void IdleFunc();
	static void ResizeFunc(int _width, int _height);
	static void KeyDownFunc(unsigned char key, int x, int y);
	static void KeyUpFunc(unsigned char key, int x, int y);
	static void SpecialKeyDownFunc(int key, int x, int y);
	static void SpecialKeyUpFunc(int key, int x, int y);
	static void MouseFunc(int button, int state, int x, int y);
	static void MouseMotionFunc(int x, int y);
	static void PassiveMouseMotionFunc(int x, int y);
	virtual void Initialise() = 0;
	virtual void Draw() = 0;
	virtual void Reshape(int w, int h) = 0;
	virtual void Update(const double&) = 0;
	virtual void HandleKey(unsigned char key, int state, int x, int y) = 0;
	virtual void HandleSpecialKey(int key, int state, int x, int y) = 0;
	virtual void HandleMouse(int button, int state, int x, int y) = 0;
	virtual void HandleMouseDrag(int x, int y) = 0;
	virtual void HandleMouseMove(int x, int y) = 0;
	static int CheckGLError();
};
