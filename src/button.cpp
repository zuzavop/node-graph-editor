#include "button.h"

Button::Button(Command& f) : function(f)
{
    mPosition.x = 0;
    mPosition.y = 0;

    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button::setPosition( int x, int y )
{
    mPosition.x = x;
    mPosition.y = y;
}

void Button::handleEvent( SDL_Event* e )
{
    // any mouse event happened
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        // mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );

	// check if mouse is in button
        bool inside = true;
        if(x < mPosition.x || x > mPosition.x + BUTTON_WIDTH || y < mPosition.y|| y > mPosition.y + BUTTON_HEIGHT)
        {
            inside = false;
        }

	// mouse is outside button
        if( !inside )
        {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }

        // mouse is inside button
        else
        {
            // set mouse over sprite
            switch(e->type)
            {
                case SDL_MOUSEMOTION:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
            
                case SDL_MOUSEBUTTONDOWN:
		    function.execute();
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;
                
                case SDL_MOUSEBUTTONUP:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }
}

void Button::render(SDL_Rect* clip, SDL_Renderer* renderer, SDL_Texture* texture)
{
    // set rendering space and render to screen
    SDL_Rect renderQuad = { mPosition.x, mPosition.y, 0, 0 };

    // set clip rendering dimensions
    if( clip != NULL )
    {
	renderQuad.w = clip->w;
	renderQuad.h = clip->h;
    }

     //Render to screen
     SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}
