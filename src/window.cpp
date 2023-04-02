#include "window.h"

bool Window::init() {
    // set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
	    std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    // create a window
    window = SDL_CreateWindow("Graph Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window) {
	std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    } else {
	mMouseFocus = true;
	mKeyboardFocus = true;
	mWidth = 800;
	mHeight = 600;
    }

    // create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
	std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}
