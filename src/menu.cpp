#include "menu.h"

void MenuBar::init() {

}

void MenuBar::handleEvent(SDL_Event event) {
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    int x = event.button.x;
    int y = event.button.y;
    // if (x >= fileButtonRect.x && x <= fileButtonRect.x + fileButtonRect.w &&
    // y >= fileButtonRect.y && y <= fileButtonRect.y + fileButtonRect.h) {
    // fileButtonSelected = true;
    //} else {
    // fileButtonSelected = false;
    //}
  }
}

void MenuBar::draw(SDL_Renderer *renderer) {
  // create the menu items
  std::string menuItems[4] = {"Save", "Load", "Export", "Layout"};
  SDL_Rect menuRects[4];
  int menuWidth = 0;
  for (int i = 0; i < 4; i++) {
    // create a texture for the menu item
    int wordHeight = 10;
    int wordWidth = 10;
    
    int x = menuWidth;
    int y = 0;
    int w = wordWidth;
    int h = wordHeight;
    menuRects[i] = {x, y, w, h};

    menuWidth += wordWidth;
  }
}
