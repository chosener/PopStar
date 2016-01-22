#ifndef _STAR_PARTICLE_H_
#define _STAR_PARTICLE_H_
#include "GlobalEnum.h"
#include "cocos2d.h"
using namespace cocos2d;
void showStarParticleEffect(int color,Point position,Node* node);
void showStarParticleStar(int color,Point position,Node* node);
Color4F getColor4F(int color);
#endif