#include "class_text.hpp"
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

Text::Text() {
    texture = NULL;
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}
void Text::free() {
    texture = NULL;
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}
SDL_Texture* Text::getTexture() {
    return texture;
}
int Text::getWidth() {
    return w;
}
int Text::getHeight() {
    return h;
}
void Text::setPosition(int _x, int _y) {
    x = _x;
    y = _y;
}
void Text::loadFromText(SDL_Renderer* gRenderer, TTF_Font* gFont, string text, SDL_Color color) {
    free();
    SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    w = textSurface->w;
    h = textSurface->h;
    SDL_FreeSurface(textSurface);
}
void Text::render(SDL_Renderer* gRenderer) {
    SDL_Rect renderPos = {x, y, w, h};
    SDL_RenderCopy(gRenderer, texture, NULL, &renderPos);
}