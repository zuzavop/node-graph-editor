#include "text.h"

BitmapFont::BitmapFont() {
  mNewLine = 0;
  mSpace = 0;
}

bool BitmapFont::buildFont(std::string path, SDL_Window *window,
                           SDL_Renderer *renderer) {
  // load bitmap image
  bool success = true;
  if (!mFontTexture.loadPixelsFromFile(path, window)) {
    printf("Unable to load bitmap font surface!\n");
    success = false;
  } else {
    Uint32 bgColor = mFontTexture.getPixel32(0, 0);

    int cellW = mFontTexture.getWidth() / 16;
    int cellH = mFontTexture.getHeight() / 16;

    int top = cellH;
    int baseA = cellH;

    int currentChar = 0;

    for (int rows = 0; rows < 16; ++rows) {
      for (int cols = 0; cols < 16; ++cols) {
        mChars[currentChar].x = cellW * cols;
        mChars[currentChar].y = cellH * rows;

        mChars[currentChar].w = cellW;
        mChars[currentChar].h = cellH;

        // find left side
        for (int pCol = 0; pCol < cellW; ++pCol) {
          for (int pRow = 0; pRow < cellH; ++pRow) {
            int pX = (cellW * cols) + pCol;
            int pY = (cellH * rows) + pRow;

            // if a non colorkey pixel is found
            if (mFontTexture.getPixel32(pX, pY) != bgColor) {
              mChars[currentChar].x = pX;

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
            if (mFontTexture.getPixel32(pX, pY) != bgColor) {
              mChars[currentChar].w = (pX - mChars[currentChar].x) + 1;

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
            if (mFontTexture.getPixel32(pX, pY) != bgColor) {
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
            if (mFontTexture.getPixel32(pX, pY) != bgColor) {
              baseA = pRow;

              pCol = cellW;
              pRow = -1;
            }
          }
        }

        ++currentChar;
      }
    }

    mSpace = cellW / 2;

    mNewLine = baseA - top;

    for (int i = 0; i < 256; ++i) {
      mChars[i].y += top;
      mChars[i].h -= top;
    }

    if (!mFontTexture.loadFromPixels(renderer)) {
      printf("Unable to create font texture!\n");
      success = false;
    }
  }

  return success;
}

void BitmapFont::renderText(int x, int y, std::string text,
                            SDL_Renderer *renderer) {
  // if the font has been built
  if (mFontTexture.getWidth() > 0) {
    int curX = x, curY = y;
    for (int i = 0; i < text.length(); ++i) {
      if (text[i] == ' ') {
        curX += mSpace;
      }
      else if (text[i] == '\n') {
        curY += mNewLine;

        curX = x;
      } else {
        // get the ASCII value of the character
        int ascii = (unsigned char)text[i];

        mFontTexture.render(curX, curY, renderer, &mChars[ascii]);

        curX += mChars[ascii].w + 1;
      }
    }
  }
}
