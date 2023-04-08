#include "text.h"

BitmapFont::BitmapFont() {
  m_newLine = 0;
  m_space = 0;
}

bool BitmapFont::buildFont(std::string path, SDL_Window *window,
                           SDL_Renderer *renderer) {
  // load bitmap image
  if (!m_fontTexture.loadPixelsFromFile(path, window)) {
    std::cerr << "Unable to load bitmap font surface!" << std::endl;
    return false;
  } else {
    Uint32 bgColor = m_fontTexture.getPixel32(0, 0);

    int cellW = m_fontTexture.getWidth() / 16;
    int cellH = m_fontTexture.getHeight() / 8;

    int top = cellH;
    int baseA = cellH;

    int currentChar = 0;

    for (int rows = 0; rows < 8; ++rows) {
      for (int cols = 0; cols < 16; ++cols) {
        m_chars[currentChar].x = cellW * cols;
        m_chars[currentChar].y = cellH * rows;

        m_chars[currentChar].w = cellW;
        m_chars[currentChar].h = cellH;

        // find left side
        for (int pCol = 0; pCol < cellW; ++pCol) {
          for (int pRow = 0; pRow < cellH; ++pRow) {
            int pX = (cellW * cols) + pCol;
            int pY = (cellH * rows) + pRow;

            // if a non colorkey pixel is found
            if (m_fontTexture.getPixel32(pX, pY) != bgColor) {
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
            if (m_fontTexture.getPixel32(pX, pY) != bgColor) {
              m_chars[currentChar].w = (pX - m_chars[currentChar].x) + 1;

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
            if (m_fontTexture.getPixel32(pX, pY) != bgColor) {
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
            if (m_fontTexture.getPixel32(pX, pY) != bgColor) {
              baseA = pRow;

              pCol = cellW;
              pRow = -1;
            }
          }
        }

        ++currentChar;
      }
    }

    m_space = cellW / 2;

    m_newLine = baseA - top;

    for (int i = 0; i < 256; ++i) {
      m_chars[i].y += top;
      m_chars[i].h -= top;
    }

    if (!m_fontTexture.loadFromPixels(renderer)) {
      std::cerr << "Unable to create font texture!" << std::endl;
      return false;
    }
  }
  return true;
}

void BitmapFont::renderText(int x, int y, std::string_view text,
                            SDL_Renderer *renderer, float scale_factor,
                            int width, int height) {
  x = x * (1 / scale_factor);
  y = y * (1 / scale_factor);
  width = (width == 0 ? getWordWidth(text) : width) + 2;
  height = (height == 0 ? getWordHeight(text) : height) + 2;
  // set the scaling factor
  SDL_RenderSetScale(renderer, scale_factor, scale_factor);
  const SDL_Rect buttonSpace = {x, y, width, height};
  SDL_RenderFillRect(renderer, &buttonSpace);

  // if the font has been built
  if (m_fontTexture.getWidth() > 0) {
    int curX = x + 1, curY = y + 1;
    for (int i = 0; i < text.length(); ++i) {
      if (text[i] == ' ') {
        curX += m_space;
      } else if (text[i] == '\n') {
        curY += m_newLine;

        curX = x;
      } else {
        // get the ASCII value of the character
        int ascii = (unsigned char)text[i];

        m_fontTexture.render(curX, curY, renderer, &m_chars[ascii]);

        curX += m_chars[ascii].w;
      }
    }
  }
  SDL_RenderSetScale(renderer, SCALE_FACTOR, SCALE_FACTOR);
}

int BitmapFont::getWordWidth(std::string_view word) {
  int width = 0;
  // if the font has been built
  if (m_fontTexture.getWidth() > 0) {
    for (int i = 0; i < word.length(); ++i) {
      if (word[i] == ' ') {
        width += m_space;
      } else {
        int ascii = (unsigned char)word[i];
        width += m_chars[ascii].w + 1;
      }
    }
  }
  return width;
}

int BitmapFont::getWordHeight(std::string_view word) {
  int height = 0;
  // if the font has been built
  if (m_fontTexture.getWidth() > 0) {
    // get the ASCII value of the character
    int ascii = (unsigned char)word[0];
    height = m_chars[ascii].h;
    for (int i = 0; i < word.length(); ++i) {
      if (word[i] == '\n') {
        height += m_newLine;
      }
    }
  }
  return height;
}
