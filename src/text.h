#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "texture.h"

class BitmapFont {
public:
  BitmapFont();
  ~BitmapFont() {};

  bool buildFont(std::string path, SDL_Window *window, SDL_Renderer *renderer);

  void renderText(int x, int y, std::string text, SDL_Renderer *renderer);

private:
  Texture mFontTexture;

  SDL_Rect mChars[256];

  int mNewLine, mSpace;
};

#endif
