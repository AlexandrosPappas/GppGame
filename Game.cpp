#include "Game.h"
#include "graphics.h"
#include "config.h"
#include "Enemy.h"
#include "player.h"
#include "util.h"


void Game::spawnEnemy()
{
	if (!enemy_initialized && graphics::getGlobalTime() > 11000)
	{
		if (!enemy)
		{
			enemy = new Enemy(*this);
		}
	}	
}

void Game::checkEnemies()
{
	if (enemy && !enemy->isActive())
	{
		delete enemy;
		enemy = nullptr;
		enemiesLost++;
	}
}





bool Game::checkCollision()
{
	if (!player || !enemy) {
		return false;
	}
	
	Disk d1 = player->getCollisionHull();

	Disk d2 = enemy->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;
	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		
		player->getBigger();
		return true;
		d1.radius += 1.0f;
	}
	else return false;
}



void Game::updateStartScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) 
	{
		status = STATUS_PLAYING;
	}
}

void Game::updatePlayingScreen()
{
	if (!player_initialized && graphics::getGlobalTime() > 0300)
	{
		player = new Player(*this);
		player_initialized = true;
	}

	checkEnemies();
	spawnEnemy();

	if (player)
		player->update();

	if (enemy)
		enemy->update();

	if (checkCollision()) {


		if (player->getSize() > enemy->getEenemySize()) {

			graphics::playSound(std::string(ASSET_PATH) + "Bigger.wav", 0.5f, false);
			player->getBigger();
			delete enemy;
			enemy = nullptr;
			numOfCollisions++;
		}

		else {
			delete enemy;
			enemy = nullptr;
			status = STATUS_END;
		}
		if (enemiesLost < 40) {
			if (numOfCollisions >= 15) {
				status = STATUS_WIN;
			}
		}
		else {
			delete enemy;
			enemy = nullptr;
			status = STATUS_END;
		}

	}

}

void Game::updateLoseScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		player->reset();
		enemiesLost = 0;
		numOfCollisions = 0;
		status = STATUS_START;
	}
}
void Game::updateWinScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		player->reset();
		enemiesLost = 0;
		numOfCollisions = 0;
		status = STATUS_START;
	}
}
void Game::drawStartScreen()
{
	graphics::Brush br1;
	br1.texture = std::string(ASSET_PATH) + "start.png";
	br1.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br1);
	graphics::Brush br;
	char info[50];
	sprintf_s(info, "Press ENTER to start");
	graphics::drawText(370, 200, 30, info, br);
	sprintf_s(info, "Rules are simple: ");
	graphics::drawText(250, 300, 30, info, br);
	sprintf_s(info, "1) if you eat 15 enemies you win ");
	graphics::drawText(250, 350, 30, info, br);
	sprintf_s(info, "2) if you crush with bigger enemy you lose ");
	graphics::drawText(250, 400, 30, info, br);
	sprintf_s(info, "3) if you let 40 enemies pass you lose.Good luck!");
	graphics::drawText(250, 450, 30, info, br);

	
}

void Game::drawPlayingScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "backround.png";
	br.outline_opacity = 0.0f;

	//draw backround
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	graphics::Brush br2;
	char info[50];
	sprintf_s(info, "enemies passed %1.0f", enemiesLost);
	graphics::drawText(30, 30, 30, info, br2);

	graphics::Brush br3;
	char info2[50];
	sprintf_s(info2, "winned fights %1.0f", numOfCollisions);
	graphics::drawText(700, 30, 30, info2, br3);


	//draw player
	if (player)
		player->draw();

	//draw enemies
	
	if (enemy)
		enemy->draw();
}

void Game::drawLoseScreen()
{
	//graphics::playSound(std::string(ASSET_PATH) + "Lose.wav", 0.2f, false);
	graphics::Brush br2;
	br2.texture = std::string(ASSET_PATH) + "lose.png";
	br2.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br2);
	graphics::Brush br;
	char info[50];
	sprintf_s(info, "GAME OVER");
	graphics::drawText(430, CANVAS_HEIGHT / 2, 30, info, br);
	sprintf_s(info, "PRESS ENTER TO GET VENGEANCE");
	graphics::drawText(300, 100, 30, info, br);
}

void Game::drawWinScreen()
{
	graphics::playSound(std::string(ASSET_PATH) + "Win.wav", 0.3f, false);
	graphics::Brush br2;
	br2.texture = std::string(ASSET_PATH) + "win.png";
	br2.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br2);
	graphics::Brush br;
	char info[50];
	sprintf_s(info, "YOU WON");
	graphics::drawText(460, CANVAS_HEIGHT / 2, 30, info, br);
	

}

void Game::update()
{

	if (status == STATUS_START) {
		updateStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		updatePlayingScreen();
	}
	else if (status == STATUS_WIN) {
			updateWinScreen();
		}
	else {
		updateLoseScreen();
		}
}

void Game::draw()
{
	if (status == STATUS_START) {
		drawStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		drawPlayingScreen();
	}
	else if(status == STATUS_END)
	{
		drawLoseScreen();

	}
	else {
		drawWinScreen();
	}
}

void Game::init()
{
    graphics::playMusic(std::string(ASSET_PATH) + "theme.mp3", 0.5f, true, 5000);

	graphics::setFont(std::string(ASSET_PATH) + "Kids Monday.otf");
}

float Game::window2canvasX(float x)
{
	return x * CANVAS_WIDTH / (float)window_width;
}

float Game::window2canvasY(float y)
{
	return y * CANVAS_HEIGHT / (float)window_height;
}

Game::Game()
{

}

Game::~Game()
{
	if (player)
	{
		delete player;
	}
}
