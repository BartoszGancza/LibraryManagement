//
// Created by Zellos on 17.04.2019.
//

#ifndef LIBRARYMANAGEMENT_WINDOWMANAGER_H
#define LIBRARYMANAGEMENT_WINDOWMANAGER_H

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

using namespace std;

class WindowManager {
private:
    int xsize, ysize, xpos, ypos;
    Uint32 flags;
    const char *title;
    TTF_Font *font = nullptr;
    SDL_Surface *surface = nullptr;
    SDL_Texture *texture = nullptr;
public:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    WindowManager(const char *title, int xpos, int ypos, int xsize, int ysize, Uint32 flag) : title(title), xpos(xpos),
                                                                                              ypos(ypos), xsize(xsize),
                                                                                              ysize(ysize),
                                                                                              flags(flag) {};

    void init() {
        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();
        window = SDL_CreateWindow(title, xpos, ypos, xsize, ysize, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        font = TTF_OpenFont("arial.ttf", 15);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void displayWindow(const string &text) {
        SDL_Color color = {255, 255, 255};
        surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, 400);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);
        SDL_Rect dstrect = {300, 250, texW, texH};
        SDL_RenderCopy(renderer, texture, nullptr, &dstrect);
        SDL_RenderPresent(renderer);
    }

    void freeResources() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
        SDL_Quit();
    }


};

#endif //LIBRARYMANAGEMENT_WINDOWMANAGER_H
