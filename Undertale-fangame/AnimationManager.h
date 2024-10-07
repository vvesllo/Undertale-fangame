#pragma once

#include "Animation.h"

class AnimationManager
{
private:
	std::map<int, Animation*> m_animations;

public:
	AnimationManager();

	void add(int name, Animation* animation);
	Animation* get(int name);
};

