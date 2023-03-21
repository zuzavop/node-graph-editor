#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class MenuBar {
public:
    MenuBar(SDL_Renderer* renderer);
    ~MenuBar();
    void handleInput(SDL_Event event);
    void draw();

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Color textColor;
    SDL_Rect fileButtonRect;
    bool fileButtonSelected;
};
