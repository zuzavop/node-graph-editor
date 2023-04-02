#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

//Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;

enum ButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

//The mouse button
class Button
{
    public:
        //Initializes internal variables
        Button();

        //Sets top left position
        void setPosition( int x, int y );

        //Handles mouse event
        void handleEvent( SDL_Event* e );
    
        //Shows button sprite
        void render(SDL_Rect* clip, SDL_Renderer* renderer, SDL_Texture* texture);

    private:
        //Top left position
        SDL_Point mPosition;

        //Currently used global sprite
        ButtonSprite mCurrentSprite;
};

#endif
