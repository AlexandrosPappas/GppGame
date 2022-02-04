#pragma once
#include "gameobject.h"
#include "config.h"
#include "util.h"


class Player : public GameObject, public Collidable
{
	float speed = 2.0f;
	float pos_x = CANVAS_HEIGHT / 2;
	float pos_y = CANVAS_HEIGHT/2;
	float player_size = 43;
	float startSize = 43;
	bool active = true;

public:
	Player(const class Game& mygame); 
	void update() override;
	void draw() override;
	void init() override;
	bool isActive()
	{
		return active;
	}
	void getBigger();
	void reset();
	float getSize() { return player_size; }
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	Disk getCollisionHull() const override;
	Disk getStartHull() const override;
};