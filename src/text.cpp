#include "text.h"

BitmapFont::BitmapFont() {
  _newLine = 0;
  _space = 0;
}

bool BitmapFont::buildFont(std::string path, SDL_Window *window,
                           SDL_Renderer *renderer) {
  // load bitmap image
  bool success = true;
  if (!_fontTexture.loadPixelsFromFile(path, window)) {
    printf("Unable to load bitmap font surface!\n");
    success = false;
  } else {
    Uint32 bgColor = _fontTexture.getPixel32(0, 0);

    int cellW = _fontTexture.getWidth() / 16;
    int cellH = _fontTexture.getHeight() / 8;

    int top = cellH;
    int baseA = cellH;

    int currentChar = 0;

    for (int rows = 0; rows < 8; ++rows) {
      for (int cols = 0; cols < 16; ++cols) {
        _chars[currentChar].x = cellW * cols;
        _chars[currentChar].y = cellH * rows;

        _chars[currentChar].w = cellW;
        _chars[currentChar].h = cellH;

        // find left side
        for (int pCol = 0; pCol < cellW; ++pCol) {
          for (int pRow = 0; pRow < cellH; ++pRow) {
            int pX = (cellW * cols) + pCol;
            int pY = (cellH * rows) + pRow;

            // if a non colorkey pixel is found
            if (_fontTexture.getPixel32(pX, pY) != bgColor) {
              pCol = cellW;
              pRow = cellH;
            }
          }
        }

        // find right side
        for (int pColW = cellW - 1; pColW >= 0; --pColW) {
          for (int pRowW = 0; pRowW < cellH; ++pRowW) {
            int pX = (cellW * cols) + pColW;
            int pY = (cellH * rows) + pRowW;

            // if a non colorkey pixel is found
            if (_fontTexture.getPixel32(pX, pY) != bgColor) {
              _chars[currentChar].w = (pX - _chars[currentChar].x) + 1;

              pColW = -1;
              pRowW = cellH;
            }
          }
        }

        // find top
        for (int pRow = 0; pRow < cellH; ++pRow) {
          for (int pCol = 0; pCol < cellW; ++pCol) {
            int pX = (cellW * cols) + pCol;
            int pY = (cellH * rows) + pRow;

            // if a non colorkey pixel is found
            if (_fontTexture.getPixel32(pX, pY) != bgColor) {
              if (pRow < top) {
                top = pRow;
              }

              pCol = cellW;
              pRow = cellH;
            }
          }
        }

        // find bottom
        for (int pRow = cellH - 1; pRow >= 0; --pRow) {
          for (int pCol = 0; pCol < cellW; ++pCol) {
            int pX = (cellW * cols) + pCol;
            int pY = (cellH * rows) + pRow;

            // if a non colorkey pixel is found
            if (_fontTexture.getPixel32(pX, pY) != bgColor) {
              baseA = pRow;

              pCol = cellW;
              pRow = -1;
            }
          }
        }

        ++currentChar;
      }
    }

    _space = cellW / 2;

    _newLine = baseA - top;

    for (int i = 0; i < 256; ++i) {
      _chars[i].y += top;
      _chars[i].h -= top;
    }

    if (!_fontTexture.loadFromPixels(renderer)) {
      printf("Unable to create font texture!\n");
      success = false;
    }
  }

  return success;
}

void BitmapFont::renderText(int x, int y, std::string text,
                            SDL_Renderer *renderer, float scale_factor,
                            int width, int height) {
  x = x * (1 / scale_factor);
  y = y * (1 / scale_factor);
  width = (width == 0 ? getWordWidth(text) : width) + 2;
  height = (height == 0 ? getWordHeight(text) : height) + 2;
  // Set the scaling factor
  SDL_RenderSetScale(renderer, scale_factor, scale_factor);
  const SDL_Rect buttonSpace = { x, y, width, height };
  SDL_RenderFillRect(renderer, &buttonSpace);

  // if the font has been built
  if (_fontTexture.getWidth() > 0) {
    int curX = x + 1, curY = y + 1;
    for (int i = 0; i < text.length(); ++i) {
      if (text[i] == ' ') {
        curX += _space;
      } else if (text[i] == '\n') {
        curY += _newLine;

        curX = x;
      } else {
        // get the ASCII value of the character
        int ascii = (unsigned char)text[i];

        _fontTexture.render(curX, curY, renderer, &_chars[ascii]);

        curX += _chars[ascii].w;
      }
    }
  }
  SDL_RenderSetScale(renderer, SCALE_FACTOR, SCALE_FACTOR);
}

int BitmapFont::getWordWidth(const std::string &word) {
  int width = 0;
  // if the font has been built
  if (_fontTexture.getWidth() > 0) {
    for (int i = 0; i < word.length(); ++i) {
      if (word[i] == ' ') {
        width += _space;
      } else {
        int ascii = (unsigned char)word[i];
        width += _chars[ascii].w + 1;
      }
    }
  }
  return width;
}

int BitmapFont::getWordHeight(const std::string &word) {
  int height = 0;
  // if the font has been built
  if (_fontTexture.getWidth() > 0) {
    // get the ASCII value of the character
    int ascii = (unsigned char)word[0];
    height = _chars[ascii].h;
    for (int i = 0; i < word.length(); ++i) {
      if (word[i] == '\n') {
        height += _newLine;
      }
    }
  }
  return height;
}
