#include "menu.h"

MenuBar::MenuBar(SDL_Renderer* r) {
    renderer = r;
    //TTF_Init();
    //font = TTF_OpenFont("arial.ttf", 20);
    textColor = {0, 0, 0, 255};
    fileButtonRect = {10, 10, 80, 30};
    fileButtonSelected = false;
}


MenuBar::~MenuBar() {
    //TTF_CloseFont(font);
    //TTF_Quit();
}


void MenuBar::handleInput(SDL_Event event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x = event.button.x;
        int y = event.button.y;
        if (x >= fileButtonRect.x && x <= fileButtonRect.x + fileButtonRect.w && y >= fileButtonRect.y && y <= fileButtonRect.y + fileButtonRect.h) {
            fileButtonSelected = true;
        } else {
            fileButtonSelected = false;
        }
    }
}

void MenuBar::draw() {
    //SDL_Surface* textSurface = TTF_RenderText_Solid(font, "File", textColor);
    //SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    //SDL_Rect textRect = {fileButtonRect.x + 10, fileButtonRect.y + 5, textSurface->w, textSurface->h};
    //SDL_Rect buttonRect = {fileButtonRect.x, fileButtonRect.y, textSurface->w + 20, textSurface->h + 10};
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    //SDL_RenderFillRect(renderer, &buttonRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //SDL_RenderDrawRect(renderer, &buttonRect);
    if (fileButtonSelected) {
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
        //SDL_RenderFillRect(renderer, &buttonRect);
    }
    //SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    //SDL_FreeSurface(textSurface);
    //SDL_DestroyTexture(textTexture);
}
