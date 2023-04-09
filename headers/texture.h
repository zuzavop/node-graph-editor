#ifndef TEXTURE_H
#define TEXTURE_H

#ifndef _MSC_VER
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

#include <iostream>
#include <string>
#include <string_view>

const int PADDING = 10;

class Texture {
public:
  Texture();
  ~Texture();

  bool loadPixelsFromFile(std::string path, SDL_Window *window);
  bool loadFromPixels(SDL_Renderer *renderer);

  void render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip = nullptr,
              double angle = 0.0, SDL_Point *center = nullptr,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

  int getWidth();
  int getHeight();
  Uint32 getPixel32(Uint32 x, Uint32 y);

private:
  SDL_Texture *m_texture;
  SDL_Surface *m_surfacePixels;

  int m_width;
  int m_height;

  void free();
  Uint32 getPitch32();
};

#endif
