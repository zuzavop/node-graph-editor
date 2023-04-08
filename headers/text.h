#ifndef TEXT_H
#define TEXT_H

#include "texture.h"

const float SCALE_FACTOR = 1;
const float BIG_FONT_SCALE = 0.7;
const float NORMAL_FONT_SCALE = 0.6;
const float SMALL_FONT_SCALE = 0.3;
const float FONT_SCALE = 0.5;

class BitmapFont {
public:
  BitmapFont();
  ~BitmapFont(){};

  bool buildFont(std::string path, SDL_Window *window, SDL_Renderer *renderer);
  void renderText(int x, int y, std::string_view text, SDL_Renderer *renderer,
                  float scale_factor = SCALE_FACTOR, int width = 0,
                  int height = 0);
  int getWordWidth(std::string_view word);
  int getWordHeight(std::string_view word);

private:
  Texture m_fontTexture;
  SDL_Rect m_chars[256];
  int m_newLine, m_space;
};

#endif
