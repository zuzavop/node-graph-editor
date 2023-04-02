#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class MenuBar {
public:
    MenuBar() {};
    ~MenuBar();
    bool init(SDL_Renderer* renderer);
    void handleInput(SDL_Event event);
    void draw();

private:
    SDL_Renderer* renderer;
    bool fileButtonSelected;
    SDL_Surface* fontSurface;
    SDL_Texture* fontTexture;

};

#endif
