#include "class_animation.hpp"
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

Animation::Animation(int _frame) {
    texture == NULL;
    frame = _frame;
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}
void Animation::free() {
    texture = NULL;
    x = 0;
    y = 0;
    w = 0;
    h = 0;
    frame_clip.erase(frame_clip.begin(), frame_clip.end());
}
int Animation::getWidth() {
    return w;
}
int Animation::getHeight() {
    return h;
}
void Animation::setPosition(int _x, int _y) {
    x = _x;
    y = _y;
}
void Animation::setDimension(int _w, int _h) {
    w = _w;
    h = _h;
}
bool Animation::loadFromFile(SDL_Renderer* gRenderer, string path, int isKeyColor) {
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
        for (int i=0; i<frame; i++) {
            SDL_Rect tempClip = {(w/frame)*i, 0, w/frame, h};
            frame_clip.push_back(tempClip);
        }
        w /= frame;
        SDL_FreeSurface(loadedSurface);
    }
    return true;
}
void Animation::render(SDL_Renderer* gRenderer, int iFrame) {
    SDL_Rect renderPos = {x, y, w, h};
    SDL_RenderCopy(gRenderer, texture, &frame_clip[iFrame], &renderPos);
}