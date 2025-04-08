#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"
#include "logic.h"

using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    graphics.start();
    waitUntilKeyPressed();

    Tictactoe game;
    game.init();
    graphics.render(game);

    bool quit = false;
    SDL_Event e;
    while (! quit) {
        SDL_PollEvent(&e);
        if (e.type == SDL_QUIT) {
            quit = true;
        }

        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            game.move(x, y);
            graphics.render(game);

            if(game.k == true) {
                SDL_Delay(500);
                game.move1(x, y);
                game.k = false;
                graphics.render(game);
            }
        }
    }

    graphics.quit();
    return 0;
}
