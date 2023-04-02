#include "menu.h"

bool MenuBar::init(SDL_Renderer* r) {
    renderer = r;
    fontSurface = SDL_LoadBMP("../menu_font.bmp");
    if (!fontSurface) {
	    std::cout << "Failed to get font surface: " << SDL_GetError() << std::endl;
	    return false;
    }
    fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
    if (!fontTexture) {
	    std::cout << "Failed to get font texture: " << SDL_GetError() << std::endl;
	    return false;
    }
    return true;
}


MenuBar::~MenuBar() {
    SDL_FreeSurface(fontSurface);
    SDL_DestroyTexture(fontTexture);
}


void MenuBar::handleInput(SDL_Event event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x = event.button.x;
        int y = event.button.y;
        //if (x >= fileButtonRect.x && x <= fileButtonRect.x + fileButtonRect.w && y >= fileButtonRect.y && y <= fileButtonRect.y + fileButtonRect.h) {
            //fileButtonSelected = true;
        //} else {
            //fileButtonSelected = false;
        //}
    }
}

void MenuBar::draw() {
    int charWidth = fontSurface->w / 26;
    int charHeight = fontSurface->h / 16;
    
    // Create the menu items
    std::string menuItems[3] = {"File", "Edit", "Help"};
    SDL_Rect menuRects[3];
    int menuWidth = 0;
    for (int i = 0; i < 3; i++) {
        // Create a texture for the menu item
        SDL_Rect charRect = {(i+1)*charWidth, 4*charHeight, charWidth, charHeight};
        SDL_Rect itemRect = {menuWidth, 0, charWidth, charHeight};
        SDL_RenderCopy(renderer, fontTexture, &charRect, &itemRect);

        // Set the position and dimensions of the menu item
        int x = menuWidth;
        int y = 0;
        int w = charWidth;
        int h = charHeight;
        menuRects[i] = {x, y, w, h};

        // Update the menu width
        menuWidth += charWidth;
    }
}
