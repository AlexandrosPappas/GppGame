#pragma once

#include "player.h"
#include "Enemy.h"
#include "graphics.h"
#include <vector>

class Game {
	typedef enum{STATUS_START, STATUS_PLAYING, STATUS_END, STATUS_WIN} status_t; 
	
	Player * player = nullptr;
	bool player_initialized = false;

	Enemy* enemy = nullptr;
	bool enemy_initialized = false;


	//void checkPlayer();
	//void spawnPlayer();
	void spawnEnemy();
	void checkEnemies();
	bool checkCollision();
	
	
	status_t status = STATUS_START;

	unsigned int window_width = WINDOW_WIDTH, 
				 window_height = WINDOW_HEIGHT;

	double enemiesLost = 0;
	float numOfCollisions = 0;

	void updateStartScreen();
	void updatePlayingScreen();
	void updateLoseScreen();
	void updateWinScreen();
	void drawStartScreen();
	void drawPlayingScreen();
	void drawLoseScreen();
	void drawWinScreen();

public:
	void update();
	void draw();
	void init();
	unsigned int getWindowWdth() { return window_width; }
	unsigned int getWindowHeight() { return window_height; }
	float window2canvasX(float x);
	float window2canvasY(float y);
	void setWindowDimensions(unsigned int w, unsigned int h) { window_width = w; window_height = h; }
	Game(); //constructor
	~Game(); //destuctor
};