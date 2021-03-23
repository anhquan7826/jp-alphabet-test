#include "class_button.hpp"
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

Button::Button() {
    texture = NULL;
    state = BUTTON_MOUSE_OUT;
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}
void Button::free() {
    texture = NULL;
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}
int Button::getWidth() {
    return w;
}
int Button::getHeight() {
    return h;
}
ButtonState Button::getState() {
    return state;
}
void Button::setPosition(int _x, int _y) {
    x = _x; 
    y = _y;
}
bool Button::loadFromFile(SDL_Renderer* gRenderer, string path, int isKeyColor) {
    free();
    SDL_Surface* loadedSurface = NULL;
    loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        return false;
    } else {
        if (isKeyColor != 0) {
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));
        }
        texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        w = loadedSurface->w;
        h = loadedSurface->h;
        for (int i=0; i<4; i++) {
            state_clip[i] = {(w/4)*i, 0, w/4, h};
        }
        w /= 4;
        SDL_FreeSurface(loadedSurface);
    }
    return true;
}
void Button::handleEvent(SDL_Event* e) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    bool inside = true;
    if ((mouseX < x) || (mouseX > x+w)) {
        inside = false;
    }
    if ((mouseY < y) || (mouseY > y+h)) {
        inside = false;
    }
    if (!inside) {
        state = BUTTON_MOUSE_OUT;
    } else {
        switch (e->type) {
            case SDL_MOUSEMOTION: {
                state = BUTTON_MOUSE_HOVER;
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                state = BUTTON_MOUSE_DOWN;
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                state = BUTTON_MOUSE_UP;
                break;
            }
        }
    }
}
void Button::render(SDL_Renderer* gRenderer) {
    SDL_Rect renderPos = {x, y, w, h};
    SDL_RenderCopy(gRenderer, texture, &state_clip[state], &renderPos);
}