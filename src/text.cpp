#include "text.h"

BitmapFont::BitmapFont() : m_chars() {
  m_newLine = 0;
  m_space = 0;
}

void BitmapFont::findLeftSide(const Texture& texture, Uint32 bgColor, int x, int y, int cellWidth, int cellHeight, int* left) {
  for (int pCol = 0; pCol < cellWidth; ++pCol) {
    for (int pRow = 0; pRow < cellHeight; ++pRow) {
      int pixelX = x + pCol;
      int pixelY = y + pRow;

      // if a non colorkey pixel is found
      if (m_fontTexture.getPixel32(pixelX, pixelY) != bgColor) {
        //Set the x offset
        *left = pixelX;

        return;
      }
    }
  }
}
void BitmapFont::findRightSide(const Texture& texture, Uint32 bgColor, int x, int y, int cellWidth, int cellHeight, int* right, int startX) {
  for (int pColW = cellWidth - 1; pColW >= 0; --pColW) {
    for (int pRowW = 0; pRowW < cellHeight; ++pRowW) {
      int pX = x + pColW;
      int pY = y + pRowW;

      // if a non colorkey pixel is found
      if (m_fontTexture.getPixel32(pX, pY) != bgColor) {
        *right = (pX - startX) + 1;

        return;
      }
    }
  }
}
void BitmapFont::findTop(const Texture& texture, Uint32 bgColor, int x, int y, int cellWidth, int cellHeight, int* top) {
  for (int pRow = 0; pRow < cellHeight; ++pRow) {
    for (int pCol = 0; pCol < cellWidth; ++pCol) {
      int pX = x + pCol;
      int pY = y + pRow;

      // if a non colorkey pixel is found
      if (m_fontTexture.getPixel32(pX, pY) != bgColor) {
        if (pRow < *top) {
          *top = pRow;
        }

        return;
      }
    }
  }
}
void BitmapFont::findBottom(const Texture& texture, Uint32 bgColor, int x, int y, int cellWidth, int cellHeight, int* baseA) {
  for (int pRow = cellHeight - 1; pRow >= 0; --pRow) {
    for (int pCol = 0; pCol < cellWidth; ++pCol) {
      int pX = x + pCol;
      int pY = y + pRow;

      // if a non colorkey pixel is found
      if (m_fontTexture.getPixel32(pX, pY) != bgColor) {
        *baseA = pRow;

        return;
      }
    }
  }
}

bool BitmapFont::buildFont(std::string path, SDL_Window *window,
                           SDL_Renderer *renderer) {
  // load bitmap image
  if (!m_fontTexture.loadPixelsFromFile(path, window)) {
    std::cerr << "Unable to load bitmap font surface!" << std::endl;
    return false;
  } 
  
  Uint32 bgColor = m_fontTexture.getPixel32(0, 0);
  int cellW = m_fontTexture.getWidth() / FONT_WIDTH;
  int cellH = m_fontTexture.getHeight() / FONT_HEIGHT;
  int top = cellH;
  int baseA = cellH;
  int currentChar = 0;

  for (int rows = 0; rows < FONT_HEIGHT; ++rows) {
    for (int cols = 0; cols < FONT_WIDTH; ++cols) {
      const int x = cellW * cols;
      const int y = cellH * rows;

      m_chars[currentChar] = { x, y, cellW, cellH };

      // find left side
      findLeftSide(m_fontTexture, bgColor, x, y, cellW, cellH, &m_chars[currentChar].x);

      // find right side
      findRightSide(m_fontTexture, bgColor, x, y, cellW, cellH, &m_chars[currentChar].w, m_chars[currentChar].x);

      // find top
      findTop(m_fontTexture, bgColor, x, y, cellW, cellH, &top);

      // find bottom for A
      if(currentChar == 'A')
      {
        findBottom(m_fontTexture, bgColor, x, y, cellW, cellH, &baseA);
      }

      ++currentChar;
    }
  }

  m_space = cellW / 2;
  m_newLine = baseA - top;

  for (int i = 0; i < FONT_CHARS; ++i) {
    m_chars[i].y += top;
    m_chars[i].h -= top;
  }

  if (!m_fontTexture.loadFromPixels(renderer)) {
    std::cerr << "Unable to create font texture!" << std::endl;
    return false;
  }

  return true;
}

void BitmapFont::renderText(int x, int y, std::string_view text,
                            SDL_Renderer *renderer, double scale_factor,
                            int width, int height) {
  const double inv_scale_factor = 1.0f / scale_factor;
  x = static_cast<int>(x * inv_scale_factor);
  y = static_cast<int>(y * inv_scale_factor);
  width = (width == 0 ? getWordWidth(text) : width) + 2;
  height = (height == 0 ? getWordHeight(text) : height) + 2;

  // set the scaling factor
  SDL_RenderSetScale(renderer, (float)scale_factor, (float)scale_factor);
  const SDL_Rect buttonSpace = {x, y, width, height};
  SDL_RenderFillRect(renderer, &buttonSpace);

  // if the font has been built
  if (m_fontTexture.getWidth() > 0) {
    int curX = x + 1, curY = y + 1;
    for (auto ch : text) {
        if (ch == ' ') {
            curX += m_space;
        } else if (ch == '\n') {
            curY += m_newLine;
            curX = x + 1;
        } else {
            int ascii = static_cast<unsigned char>(ch);

            m_fontTexture.render(curX, curY, renderer, &m_chars[ascii]);
            curX += m_chars[ascii].w + 1;
        }
    }
  }
  SDL_RenderSetScale(renderer, SCALE_FACTOR, SCALE_FACTOR);
}

int BitmapFont::getWordWidth(std::string_view word) {
  int width = 0;
  // if the font has been built
  if (m_fontTexture.getWidth() > 0) {
    for (std::size_t i = 0; i < word.length(); ++i) {
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
    height = m_chars['A'].h;
    size_t numNewlines = std::count(word.begin(), word.end(), '\n');
    height += (int)(numNewlines * m_newLine);
  }
  return height;
}
