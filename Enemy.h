#pragma once
#include "graphics.h"
#include "gameobject.h"
#include "config.h"

class Enemy : public GameObject, public Collidable
{
	float speed;
	float pos_x , pos_y ;
	float size;
	float rotation;
	graphics::Brush brush;
	bool active = true;
	
public:
	void update() override;
	void draw() override;
	void init() override;
	bool isActive()
	{
		return active;
	}
	float getEenemySize() { return size; }
	Enemy(const class Game& mygame);
	~Enemy();
	Disk getCollisionHull() const override;
	Disk getStartHull() const override;
};