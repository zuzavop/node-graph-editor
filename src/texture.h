#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

class Texture {
public:
  Texture();
  ~Texture();

  bool loadFromFile(std::string path, SDL_Window *window,
                    SDL_Renderer *renderer);
  bool loadPixelsFromFile(std::string path, SDL_Window *window);
  bool loadFromPixels(SDL_Renderer *renderer);

#if defined(SDL_TTF_MAJOR_VERSION)
  bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

  void free();

  void setColor(Uint8 red, Uint8 green, Uint8 blue);
  void setBlendMode(SDL_BlendMode blending);
  void setAlpha(Uint8 alpha);

  void render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip = NULL,
              double angle = 0.0, SDL_Point *center = NULL,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

  int getWidth();
  int getHeight();
  Uint32 *getPixels32();
  Uint32 getPixel32(Uint32 x, Uint32 y);
  Uint32 getPitch32();

private:
  SDL_Texture *mTexture;
  SDL_Surface *mSurfacePixels;

  int mWidth;
  int mHeight;
};

#endif
