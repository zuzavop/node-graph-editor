#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "texture.h"

const float SCALE_FACTOR = 1;
const float BIG_FONT_SCALE = 0.7;
const float SMALL_FONT_SCALE = 0.3;
const float FONT_SCALE = 0.5;

class BitmapFont {
public:
  BitmapFont();
  ~BitmapFont(){};

  bool buildFont(std::string path, SDL_Window *window, SDL_Renderer *renderer);
  void renderText(int x, int y, std::string text, SDL_Renderer *renderer,
                  float scale_factor = SCALE_FACTOR, int width = 0,
                  int height = 0);
  int getWordWidth(const std::string &word);
  int getWordHeight(const std::string &word);

private:
  Texture _fontTexture;
  SDL_Rect _chars[256];
  int _newLine, _space;
};

#endif
