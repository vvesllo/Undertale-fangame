#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
}

void AnimationManager::add(int name, Animation* animation)
{
    m_animations[name] = animation;
}

Animation* AnimationManager::get(int name)
{
    return m_animations[name];
}
