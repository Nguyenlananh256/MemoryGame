#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "logic.h"

struct Graphics {
    SDL_Renderer *renderer;
	SDL_Window *window;
    SDL_Texture *background, *memory, *win;
	SDL_Texture *cellEmpty, *cell1, *cell2, *cell3, *cell4, *cell5, *cell6, *cell7, *cell8;

    void init() {
        initSDL();
        background = loadTexture("img//background.png");
        memory = loadTexture("img//memory.png");
        win = loadTexture("img//win.png");
        cellEmpty = loadTexture("img//0.png");
        cell1 = loadTexture("img//1.png");
        cell2 = loadTexture("img//2.png");
        cell3 = loadTexture("img//3.png");
        cell4 = loadTexture("img//4.png");
        cell5 = loadTexture("img//5.png");
        cell6 = loadTexture("img//6.png");
        cell7 = loadTexture("img//7.png");
        cell8 = loadTexture("img//8.png");
    }

    void start() {
        prepareScene(background);
        renderTexture(memory, 0, 300);
        presentScene();
    }

    void render(const Tictactoe &game) {
        prepareScene(background);

        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++) {
                int x = BOARD_X + j * CELL_SIZE;
                int y = BOARD_Y + i * CELL_SIZE;
                switch (game.board[i][j]) {
                    case 0: renderTexture(cellEmpty, x, y); break;
                    case 1: renderTexture(cell1, x, y); break;
                    case 2: renderTexture(cell2, x, y); break;
                    case 3: renderTexture(cell3, x, y); break;
                    case 4: renderTexture(cell4, x, y); break;
                    case 5: renderTexture(cell5, x, y); break;
                    case 6: renderTexture(cell6, x, y); break;
                    case 7: renderTexture(cell7, x, y); break;
                    case 8: renderTexture(cell8, x, y); break;
                    default: break;
                };
            };

        presentScene();
    }

    void isWin() {
        prepareScene(background);
        renderTexture(win, 200, 300);
        presentScene();
    }

	void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }

	void initSDL() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        //full screen
        //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
        if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
        //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
        //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

	void prepareScene(SDL_Texture * background)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy( renderer, background, NULL, NULL);
    }

    void prepareScene()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture *loadTexture(const char *filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = src->w;
        dest.h = src->h;

        SDL_RenderCopy(renderer, texture, src, &dest);
    }

    void quit()
    {
        SDL_DestroyTexture(background);
        background = nullptr;
        SDL_DestroyTexture(memory);
        memory = nullptr;
        SDL_DestroyTexture(win);
        win = nullptr;
        SDL_DestroyTexture(cellEmpty);
        cellEmpty = nullptr;
        SDL_DestroyTexture(cell1);
        cell1 = nullptr;
        SDL_DestroyTexture(cell2);
        cell2 = nullptr;
        SDL_DestroyTexture(cell3);
        cell3 = nullptr;
        SDL_DestroyTexture(cell4);
        cell4 = nullptr;
        SDL_DestroyTexture(cell5);
        cell5 = nullptr;
        SDL_DestroyTexture(cell6);
        cell6 = nullptr;
        SDL_DestroyTexture(cell7);
        cell7 = nullptr;
        SDL_DestroyTexture(cell8);
        cell8 = nullptr;

        IMG_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

#endif // _GRAPHICS__H
