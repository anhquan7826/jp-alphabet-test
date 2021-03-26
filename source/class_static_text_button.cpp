#include "class_static_text_button.hpp"
#include "class_text.hpp"

#include <SDL.h>
#include <iostream>

using namespace std;

StaticTextButton::StaticTextButton() {
    rect = {0, 0, 0, 0};
}
void StaticTextButton::setText(SDL_Renderer* gRenderer, TTF_Font* gFont, string _text, SDL_Color color) {
    text.loadFromText(gRenderer, gFont, _text, color);
}

void StaticTextButton::setDimension(int _x, int _y, int _w, int _h) {
    rect = {_x, _y, _w, _h};
    text.setPosition(_x+rect.w/2-text.getWidth()/2, _y+rect.h/2-text.getHeight()/2);
}

void StaticTextButton::handleEvent(SDL_Event* e) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    bool inside = true;
    if ((mouseX < rect.x) || (mouseX > rect.x+rect.w)) {
        inside = false;
    }
    if ((mouseY < rect.y) || (mouseY > rect.y+rect.h)) {
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

ButtonState StaticTextButton::getState() {
    return state;
}

void StaticTextButton::setState(ButtonState _state) {
    state = _state;
}

void StaticTextButton::render(SDL_Renderer* gRenderer) {
    switch (state) {
        case BUTTON_MOUSE_OUT:
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(gRenderer, &rect);
            text.render(gRenderer);
            break;
        case BUTTON_MOUSE_HOVER:
            SDL_SetRenderDrawColor(gRenderer, 150, 150, 150, 255);
            SDL_RenderFillRect(gRenderer, &rect);
            text.render(gRenderer);
            break;
        case BUTTON_MOUSE_DOWN:
            SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 255);
            SDL_RenderFillRect(gRenderer, &rect);
            text.render(gRenderer);
            break;
        case BUTTON_MOUSE_UP:
            SDL_SetRenderDrawColor(gRenderer, 150, 150, 150, 255);
            SDL_RenderFillRect(gRenderer, &rect);
            text.render(gRenderer);
            break;
    }
}