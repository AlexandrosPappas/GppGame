#include "player.h"
#include "graphics.h"
#include "config.h"
#include "Game.h"

Player::Player(const Game & mygame)
	: GameObject(mygame)
{	
}


void Player::update()
{
	if (graphics::getKeyState(graphics::SCANCODE_A)) 
	{
		pos_x -= speed * graphics::getDeltaTime() / 5.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D)) 
	{
		pos_x += speed * graphics::getDeltaTime() / 5.0f;

	}
	if (graphics::getKeyState(graphics::SCANCODE_W)) 
	{
		pos_y -= speed * graphics::getDeltaTime() / 5.0f;

	}
	if (graphics::getKeyState(graphics::SCANCODE_S)) 
	{
		pos_y += speed * graphics::getDeltaTime() / 5.0f;

	}

	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
	if (pos_y < 0) pos_y = 0;
	if (pos_y > CANVAS_HEIGHT) pos_y = CANVAS_HEIGHT;
}

void Player::draw()
{

	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "player.png";
	br.outline_opacity = 0.0f;

	graphics::drawRect(pos_x, pos_y, player_size, player_size, br);
	br.outline_opacity = 0.0f;

	
}


void Player::init()
{

}

void Player::getBigger()
{
	player_size += 2.0f;
}

void Player::reset()
{
	player_size = startSize;
	pos_x = CANVAS_WIDTH / 2;
	pos_y = CANVAS_HEIGHT / 2;
	getCollisionHull() = getStartHull();
}

Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 25.0f;
	return disk;
}

Disk Player::getStartHull() const
{
	Disk disk1;
	disk1.cx = pos_x;
	disk1.cy = pos_y;
	disk1.radius = 25.0f;
	return disk1;
}




