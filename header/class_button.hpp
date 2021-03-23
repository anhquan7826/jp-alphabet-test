#ifndef CLASS_BUTTON
#define CLASS_BUTTON

#include <SDL.h>
#include <string>
#include "enum_ButtonState.hpp"

using namespace std;

class Button {
    private:
        SDL_Texture* texture;
        SDL_Rect state_clip[4];
        ButtonState state;
        int x, y;
        int w, h;
    public:
        Button();
        void free();
        int getWidth();
        int getHeight();
        ButtonState getState();
        void setPosition(int _x, int _y);
        bool loadFromFile(SDL_Renderer* gRenderer, string path, int isKeyColor);
        void handleEvent(SDL_Event* e);
        void render(SDL_Renderer* gRenderer);
};

#endif