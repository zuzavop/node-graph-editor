#include "texture.h"

Texture::Texture() {
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;

  mSurfacePixels = NULL;
}

Texture::~Texture() { free(); }

bool Texture::loadFromFile(std::string path, SDL_Window *window,
                           SDL_Renderer *renderer) {
  // load pixels
  if (!loadPixelsFromFile(path, window)) {
    std::cerr << "Failed to load pixels from " << path.c_str() << std::endl;
  } else {
    // load texture from pixels
    if (!loadFromPixels(renderer)) {
      std::cerr << "Failed to texture from pixels from " << path.c_str()
                << std::endl;
    }
  }

  return mTexture != NULL;
}

bool Texture::loadPixelsFromFile(std::string path, SDL_Window *window) {
  free();

  // load image at specified path
  SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
  if (!loadedSurface) {
    std::cerr << "Unable to load image " << path.c_str()
              << "! SDL_image Error: " << SDL_GetError() << std::endl;
  } else {
    // convert surface to display format
    mSurfacePixels = SDL_ConvertSurfaceFormat(
        loadedSurface, SDL_GetWindowPixelFormat(window), 0);
    if (!mSurfacePixels) {
      std::cerr
          << "Unable to convert loaded surface to display format! SDL Error: "
          << SDL_GetError() << std::endl;
    } else {
      mWidth = mSurfacePixels->w;
      mHeight = mSurfacePixels->h;
    }

    // get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  return mSurfacePixels != NULL;
}

bool Texture::loadFromPixels(SDL_Renderer *renderer) {
  if (mSurfacePixels == NULL) {
    std::cerr << "No pixels loaded!" << std::endl;
  } else {
    SDL_SetColorKey(mSurfacePixels, SDL_TRUE,
                    SDL_MapRGB(mSurfacePixels->format, 0, 0xFF, 0xFF));

    mTexture = SDL_CreateTextureFromSurface(renderer, mSurfacePixels);
    if (mTexture == NULL) {
      std::cerr << "Unable to create texture from loaded pixels! SDL Error: "
                << SDL_GetError() << std::endl;
    } else {
      mWidth = mSurfacePixels->w;
      mHeight = mSurfacePixels->h;
    }

    // get rid of old loaded surface
    SDL_FreeSurface(mSurfacePixels);
    mSurfacePixels = NULL;
  }

  return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool Texture::loadFromRenderedText(std::string textureText,
                                   SDL_Color textColor) {
  free();

  SDL_Surface *textSurface =
      TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
  if (textSurface != NULL) {
    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if (mTexture == NULL) {
      std::cerr << "Unable to create texture from rendered text! SDL Error: "
                << SDL_GetError() << std::endl;
    } else {
      mWidth = textSurface->w;
      mHeight = textSurface->h;
    }

    SDL_FreeSurface(textSurface);
  } else {
    std::cerr << "Unable to render text surface! SDL_ttf Error: "
              << TTF_GetError() << std::endl;
  }

  return mTexture != NULL;
}
#endif

void Texture::free() {
  if (mTexture != NULL) {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }

  if (mSurfacePixels != NULL) {
    SDL_FreeSurface(mSurfacePixels);
    mSurfacePixels = NULL;
  }
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
  SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending) {
  SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture::setAlpha(Uint8 alpha) {
  SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Texture::render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip,
                     double angle, SDL_Point *center, SDL_RendererFlip flip) {
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};

  if (clip != NULL) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth() { return mWidth; }

int Texture::getHeight() { return mHeight; }

Uint32 *Texture::getPixels32() {
  Uint32 *pixels = NULL;

  if (mSurfacePixels != NULL) {
    pixels = static_cast<Uint32 *>(mSurfacePixels->pixels);
  }

  return pixels;
}

Uint32 Texture::getPixel32(Uint32 x, Uint32 y) {
  Uint32 *pixels = static_cast<Uint32 *>(mSurfacePixels->pixels);

  return pixels[(y * getPitch32()) + x];
}

Uint32 Texture::getPitch32() {
  Uint32 pitch = 0;

  if (mSurfacePixels != NULL) {
    pitch = mSurfacePixels->pitch / 4;
  }

  return pitch;
}
