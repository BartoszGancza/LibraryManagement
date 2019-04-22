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
    int xsize, ysize, xpos, ypos, imgW, imgH;
    Uint32 flags;
    const char *title;
    TTF_Font *font = nullptr;
    SDL_Surface *surface = nullptr;
    SDL_Texture *texture = nullptr;
    SDL_Color textColor = {255, 255, 255, 255};
public:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    WindowManager(const char *title, int xpos, int ypos, int xsize, int ysize, Uint32 flag) : title(title), xpos(xpos),
                                                                                              ypos(ypos), xsize(xsize),
                                                                                              ysize(ysize),
                                                                                              flags(flag) {};

    // Necessary initialization for SDL, also creates a window and renderer
    void init() {
        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();
        window = SDL_CreateWindow(title, xpos, ypos, xsize, ysize, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        font = TTF_OpenFont("arial.ttf", 25);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void freeResources() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_DestroyTexture(texture);
        SDL_Quit();
    }

    string grabInput(const string &prompt) {
        bool quit = false;
        SDL_Event e;
        string collectInput;

        SDL_RenderClear(renderer);

        renderTextTexture(prompt);

        SDL_StartTextInput();
        //While collecting input
        while (!quit) {
            //render text if any changes occurred
            bool renderText = false;

            //Event loop
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_KEYDOWN) {
                    //Handle backspace
                    if (e.key.keysym.sym == SDLK_BACKSPACE && collectInput.length() > 0) {
                        //delete character
                        collectInput.pop_back();
                        renderText = true;
                    } else if (e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN) {
                        quit = true;
                    }
                }
                    //Text input event (letters, symbols, numbers)
                else if (e.type == SDL_TEXTINPUT) {
                    collectInput += e.text.text;
                    renderText = true;
                }
            }
            //Rerender text if needed
            if (renderText) {
                //Text is not empty
                if (!collectInput.empty()) {
                    renderTextTexture(prompt + collectInput);
                } else {
                    //Render the prompt message if no input
                    renderTextTexture(prompt);
                }
            }
        }
        SDL_StopTextInput();
        //Send collected input to the outside variable
        return collectInput;
    }

    int trackMouse(const vector<SDL_Rect> &menuPositions = vector<SDL_Rect>()) {
        bool quit = false;
        SDL_Event e;
        int x, y, selected = 0;

        //While tracking mouse
        while (!quit) {
            //Event loop
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    // When left button clicked
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&x, &y);
                        // Check if the cursor is over any of the menu elements
                        for (auto it = menuPositions.begin(); it != menuPositions.end(); ++it) {
                            if ((x >= (*it).x && x <= (*it).x + (*it).w) && (y >= (*it).y && y <= (*it).y + (*it).h)) {
                                // Calculate the element index in the array (array of coordinates directly corresponds to menu elements)
                                selected = distance(menuPositions.begin(), it);
                                quit = true;
                            }
                        }
                    }
                } else if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        return -1;
                    }
                }
            }
        }
        // Return the selected menu element's index
        return selected;
    }

    vector<SDL_Rect> renderMenu(vector<string> &menuElements, const string &prompt = "") {
        SDL_RenderClear(renderer);

        int size = menuElements.size(), promptYOffset = 0;

        SDL_Surface *mainSurface = SDL_GetWindowSurface(window);
        SDL_FillRect(mainSurface, NULL, 0x000000);

        SDL_Surface *promptSurface;
        SDL_Rect promptdstrect;

        vector<SDL_Surface *> menuSurfaces(size);
        vector<SDL_Rect> dstrect(size);

        if (!empty(prompt)) {
            promptSurface = TTF_RenderText_Blended_Wrapped(font, prompt.c_str(), textColor, xsize);
            promptdstrect = {0, 0, promptSurface->w, promptSurface->h};
            SDL_BlitSurface(promptSurface, nullptr, mainSurface, &promptdstrect);
            promptYOffset = promptSurface->h + 15;
            SDL_FreeSurface(promptSurface);
        }

        for (int i = 0; i < size; i++) {
            // Create a surface with the menu element text
            menuSurfaces[i] = TTF_RenderText_Blended_Wrapped(font, menuElements[i].c_str(), textColor, xsize);
            // Position each menu element properly in space (one under the other)
            if (0 == i) {
                /* SDL_Rect {x, y, width, height} - width and height are pulled directly from the surface dimensions,
                x is 0 (left side of the window) and y is calculated*/
                dstrect[i] = {0, promptYOffset, menuSurfaces[i]->w, menuSurfaces[i]->h};
            } else {
                dstrect[i] = {0, dstrect[i - 1].y + menuSurfaces[i - 1]->h, menuSurfaces[i]->w, menuSurfaces[i]->h};
            }
            // Add newly created menu element to the main surface
            SDL_BlitSurface(menuSurfaces[i], nullptr, mainSurface, &dstrect[i]);
        }
        // Render the main surface with all elements on screen
        SDL_UpdateWindowSurface(window);
        // Free all used surfaces
        for (auto surf : menuSurfaces) {
            SDL_FreeSurface(surf);
        }
        // Return a vector of coordinates for each menu element for mouse click tracking
        return dstrect;
    }

    void renderTextTexture(const string &text) {
        SDL_RenderClear(renderer);
        surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), textColor, xsize);
        // If surface couldn't be created
        if (surface == nullptr) {
            cerr << "Unable to render surface! Error: " << TTF_GetError() << endl;
        } else {
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            // If texture couldn't be created from the surface
            if (texture == nullptr) {
                cerr << "Unable to create texture! Error: " << SDL_GetError() << endl;
            } else {
                // Grab the surface sizes to properly render text on screen
                imgW = surface->w;
                imgH = surface->h;
            }
            SDL_Rect dstrect = {0, 0, imgW, imgH};
            SDL_RenderCopy(renderer, texture, nullptr, &dstrect);
            SDL_RenderPresent(renderer);
            // Clean resources
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
    }

};

#endif //LIBRARYMANAGEMENT_WINDOWMANAGER_H
