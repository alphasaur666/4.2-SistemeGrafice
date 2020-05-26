#pragma once

class Input
{
public:
	Input(void) {}
	virtual ~Input(void) {}
	virtual void HandleKey(unsigned char key, int state, int x, int y) {};
	virtual void HandleSpecialKey(int key, int state, int x, int y) {};
	virtual void HandleMouse(int button, int state, int x, int y) {};
	virtual void HandleMouseDrag(int x, int y) {};
	virtual void HandleMouseMove(int x, int y) {};
};
