#pragma once

class Animation
{
public:
	Animation(void) {}
	virtual ~Animation(void) {}
	virtual void Update(const double& deltaTime) = 0;
};
