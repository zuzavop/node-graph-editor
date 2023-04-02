#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

#include "texture.h"

// bitmap font
class BitmapFont
{
    public:
        BitmapFont();
	~BitmapFont();

        // generates the font
        bool buildFont(std::string path, SDL_Window* window, SDL_Renderer* renderer);

        // shows the text
        void renderText(int x, int y, std::string text, SDL_Renderer* renderer);

    private:
	// the font texture
	Texture mFontTexture;

        // the individual characters in the surface
        SDL_Rect mChars[ 256 ];

        // spacing Variables
        int mNewLine, mSpace;
};

#endif
