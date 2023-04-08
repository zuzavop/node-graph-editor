#include "texture.h"

Texture::Texture() {
  m_texture = NULL;
  m_width = 0;
  m_height = 0;

  m_surfacePixels = NULL;
}

Texture::~Texture() { free(); }

bool Texture::loadPixelsFromFile(std::string path, SDL_Window *window) {
  free();

  SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
  if (!loadedSurface) {
    std::cerr << "Unable to load image " << path.c_str()
              << "! SDL_image Error: " << SDL_GetError() << std::endl;
  } else {
    // convert surface to display format
    m_surfacePixels = SDL_ConvertSurfaceFormat(
        loadedSurface, SDL_GetWindowPixelFormat(window), 0);
    if (!m_surfacePixels) {
      std::cerr
          << "Unable to convert loaded surface to display format! SDL Error: "
          << SDL_GetError() << std::endl;
    } else {
      m_width = m_surfacePixels->w;
      m_height = m_surfacePixels->h;
    }

    // get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  return m_surfacePixels != NULL;
}

bool Texture::loadFromPixels(SDL_Renderer *renderer) {
  if (m_surfacePixels == NULL) {
    std::cerr << "No pixels loaded!" << std::endl;
  } else {
    SDL_SetColorKey(m_surfacePixels, SDL_TRUE,
                    SDL_MapRGB(m_surfacePixels->format, 0, 0xFF, 0xFF));

    m_texture = SDL_CreateTextureFromSurface(renderer, m_surfacePixels);
    if (m_texture == NULL) {
      std::cerr << "Unable to create texture from loaded pixels! SDL Error: "
                << SDL_GetError() << std::endl;
    } else {
      m_width = m_surfacePixels->w;
      m_height = m_surfacePixels->h;
    }

    // get rid of old loaded surface
    SDL_FreeSurface(m_surfacePixels);
    m_surfacePixels = NULL;
  }

  return m_texture != NULL;
}

void Texture::free() {
  if (m_texture != NULL) {
    SDL_DestroyTexture(m_texture);
    m_texture = NULL;
    m_width = 0;
    m_height = 0;
  }

  if (m_surfacePixels != NULL) {
    SDL_FreeSurface(m_surfacePixels);
    m_surfacePixels = NULL;
  }
}

void Texture::render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip,
                     double angle, SDL_Point *center, SDL_RendererFlip flip) {
  SDL_Rect renderQuad = {x, y, m_width, m_height};

  if (clip != NULL) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  SDL_RenderCopyEx(renderer, m_texture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth() { return m_width; }

int Texture::getHeight() { return m_height; }

Uint32 Texture::getPixel32(Uint32 x, Uint32 y) {
  Uint32 *pixels = static_cast<Uint32 *>(m_surfacePixels->pixels);

  return pixels[(y * getPitch32()) + x];
}

Uint32 Texture::getPitch32() {
  Uint32 pitch = 0;

  if (m_surfacePixels != NULL) {
    pitch = m_surfacePixels->pitch / 4;
  }

  return pitch;
}
