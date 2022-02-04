#include "Enemy.h"
#include "graphics.h"
#include "config.h"
#include <random>
#include "util.h"
 

void Enemy::update()
{
	pos_x -= speed * graphics::getDeltaTime();

	if (pos_x < -size)
	{
		active = false;
	}
}

void Enemy::draw()
{ 
	brush.texture = std::string(ASSET_PATH) + "virus.png";
	graphics::drawRect(pos_x, pos_y, size, size, brush);
	brush.outline_opacity = 0.0f;

	graphics::resetPose();	
	

}

void Enemy::init()
{
	speed = 0.3f + 0.8 * rand0to1();
	pos_x = CANVAS_WIDTH;
	pos_y = CANVAS_HEIGHT*rand0to1();;
	size = 30 + 70 * rand0to1();
	brush.outline_opacity = 0.0f;
}

Enemy::Enemy(const Game & mygame)
	: GameObject(mygame)
{
	init();
}

Enemy::~Enemy()
{
}

Disk Enemy::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size*0.45f;
	return disk;
}

Disk Enemy::getStartHull() const {
	return Disk(); 
}