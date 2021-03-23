#include "class_texture.hpp"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

Texture::Texture() {
    texture == NULL;
    w = 0;
    h = 0;
}
void Texture::free() {
    texture = NULL;
    w = 0;
    h = 0;
}
int Texture::getWidth() {
    return w;
}
int Texture::getHeight() {
    return h;
}
void Texture::setPosition(int _x, int _y) {
    x = _x;
    y = _y;
}
void Texture::setDimension(int _w, int _h) {
    w = _w;
    h = _h;
}
bool Texture::loadFromFile(SDL_Renderer* gRenderer, string path, int isKeyColor) {
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
        SDL_FreeSurface(loadedSurface);
    }
    return true;
}
void Texture::render(SDL_Renderer* gRenderer, SDL_Rect* clip) {
    SDL_Rect renderPos = {x, y, w, h};
    if (clip != NULL) {
        renderPos.w = clip->w;
        renderPos.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, texture, clip, &renderPos);
}
bool Texture::isTextureNULL() {
    return (texture != NULL);
}