#ifndef TEXT_H
#define TEXT_H

#include "texture.h"
#include "colors.h"

const float SCALE_FACTOR = 1;
const float BIG_FONT_SCALE = 0.7;
const float NORMAL_FONT_SCALE = 0.6;
const float SMALL_FONT_SCALE = 0.3;
const float FONT_SCALE = 0.5;

const int FONT_WIDTH = 16;
const int FONT_HEIGHT = 8;
const int FONT_CHARS = 256;

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
  SDL_Rect m_chars[FONT_CHARS];
  int m_newLine, m_space;

  void findLeftSide(const Texture& texture, Uint32 bgColor, int x, int y, int cellWidth, int cellHeight, int* left);
  void findRightSide(const Texture& texture, Uint32 bgColor, int x, int y, int cellWidth, int cellHeight, int* right, int startX);
  void findTop(const Texture& texture, Uint32 bgColor, int x, int y, int cellWidth, int cellHeight, int* left);
  void findBottom(const Texture& texture, Uint32 bgColor, int x, int y, int cellWidth, int cellHeight, int* left);
};

#endif
