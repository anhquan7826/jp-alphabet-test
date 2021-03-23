#ifndef STATIC_TEXT_BUTTON
#define STATIC_TEXT_BUTTON

#include <SDL.h>
#include "class_text.hpp"
#include "enum_ButtonState.hpp"

using namespace std;

class StaticTextButton {
    private:
        SDL_Rect rect;
      /*  SDL_Texture* text;
        SDL_Rect text_pos; */
        ButtonState state; 
        Text text;
    public:
        StaticTextButton();
        void setText(SDL_Renderer* gRenderer, TTF_Font* gFont, string _text, SDL_Color color);
        void setDimension(int _x, int _y, int _w, int _h);
        void handleEvent(SDL_Event* e);
        void render(SDL_Renderer* gRenderer);
        ButtonState getState();
};

#endif