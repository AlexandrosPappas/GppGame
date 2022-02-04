#include "graphics.h"
#include "Game.h"
#include "config.h"

// The custom callback function that the library calls 
// to check for and set the current application state.

void resize(int w, int h)
{
    Game* game = reinterpret_cast<Game*> (graphics::getUserData());
    game->setWindowDimensions((unsigned int)w, (unsigned int)h);
}

void update(float ms)
{
    Game * game = reinterpret_cast<Game *> (graphics::getUserData()); // epeidh to getUserData einai void pointer prepei na parei ena cast gia na ginei enas allos pointer sygkekrimenos
    game->update();
}

// The window content drawing function.
void draw()
{
    Game* game = reinterpret_cast<Game*> (graphics::getUserData()); // epeidh to getUserData einai void pointer prepei na parei ena cast gia na ginei enas allos pointer sygkekrimenos
    game->draw();
}

int main()
{
    Game mygame;

    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hunting?");

    graphics::setUserData(&mygame);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
    
    mygame.init();

    graphics::startMessageLoop();

    return 0;
}