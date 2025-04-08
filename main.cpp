#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"
#include "logic.h"

using namespace std;

void waitUntilKeyPressed(bool &quit)
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 && e.type == SDL_KEYDOWN )
            return;
        if ( SDL_PollEvent(&e) != 0 && e.type == SDL_QUIT ){
            quit = true;
            return;
        }
        SDL_Delay(100);
    }
}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    bool quit = false;

    graphics.start();
    waitUntilKeyPressed(quit);

    //bool quit = false;
    while(!quit) {
        Tictactoe game;
        game.init();
        graphics.render(game);

        bool isEnd = false;
        SDL_Event e;

        while (!isEnd) {
            SDL_PollEvent(&e);
            if (e.type == SDL_QUIT) {
                quit = true;
                isEnd = true;
                break;
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
                    if(game.number==PAIR) {
                        graphics.isWin();
                        waitUntilKeyPressed(quit);
                        isEnd = true;
                    }
                }
            }
        }
        SDL_Delay(10);
    }

    graphics.quit();
    return 0;
}
