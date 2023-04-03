#include "menu.h"

bool MenuBar::init(SDL_Renderer *r) {
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

void MenuBar::draw() {
  int charWidth = fontSurface->w / 16;
  int charHeight = fontSurface->h / 16;

  // create the menu items
  std::string menuItems[4] = {"Save", "Load", "Export", "Layout"};
  SDL_Rect menuRects[4];
  int menuWidth = 0;
  for (int i = 0; i < 4; i++) {
    // create a texture for the menu item
    SDL_Rect charRect = {(i + 1) * charWidth, 4 * charHeight, charWidth,
                         charHeight};
    SDL_Rect itemRect = {menuWidth, 0, charWidth, charHeight};
    SDL_RenderCopy(renderer, fontTexture, &charRect, &itemRect);

    int x = menuWidth;
    int y = 0;
    int w = charWidth;
    int h = charHeight;
    menuRects[i] = {x, y, w, h};

    menuWidth += charWidth;
  }
}
