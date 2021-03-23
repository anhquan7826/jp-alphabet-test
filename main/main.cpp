#include <iostream>
#include <string>
#include <fstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "class_button.hpp"
#include "class_static_text_button.hpp"
#include "class_texture.hpp"
#include "class_text.hpp"
#include "enum_ButtonState.hpp"

using namespace std;

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 800;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;

enum Option {
    MAIN_MENU,
    HIRAGANA,
    KATAKANA
};
enum Romaji {
    a, i, u, e, o, 
    ka, ki, ku, ke, ko, 
    sa, shi, su, se, so, 
    ta, chi, tsu, te, to, 
    na, ni, nu, ne, no,
    ha, hi, fu, he, ho,
    ma, mi, mu, me, mo,
    ra, ri, ru, re, ro,
    ya, yu, yo,
    wa, wo,
    n
};

ifstream file;
string romaji[46];

Texture hiragana;
Texture katakana;

SDL_Rect char_clip[46];

bool Init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return false;
    } 
    else if (!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) {
        return false;
    }
    else if (TTF_Init() == -1) {
        return false;
    }
    else {
        gWindow = SDL_CreateWindow("Japanese Alphabet Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            return false;
        } else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                return false;
            }
        }
    }
    return true;
}
bool loadMedia() {
    if (!hiragana.loadFromFile(gRenderer, "data/hiragana.png", 0)) {
        return false;
    }
    if (!katakana.loadFromFile(gRenderer, "data/katakana.png", 0)) {
        return false;
    }
    int index_x = 0, index_y = 0;
    // damn photoshop is hard to use
    for (int i=0; i<35; i++) {
        char_clip[i] = {index_x, index_y, hiragana.getWidth()/11, hiragana.getHeight()/5};
        index_y += (hiragana.getHeight()/5);
        if (index_y == hiragana.getHeight()) {
            index_y = 0;
            index_x += hiragana.getWidth()/11;
        }
    }
    index_x = 8*(hiragana.getWidth()/11);
    index_y = 0;
    for (int i=35; i<40; i++) {
        char_clip[i] = {index_x, index_y, hiragana.getWidth()/11, hiragana.getHeight()/5};
        index_y += hiragana.getHeight()/5;
    }
    char_clip[40] = {7*(hiragana.getWidth()/11), 0, hiragana.getWidth()/11, hiragana.getHeight()/5};
    char_clip[41] = {7*(hiragana.getWidth()/11), 2*(hiragana.getHeight()/5), hiragana.getWidth()/11, hiragana.getHeight()/5};
    char_clip[42] = {7*(hiragana.getWidth()/11), 4*(hiragana.getHeight()/5), hiragana.getWidth()/11, hiragana.getHeight()/5};
    char_clip[43] = {9*(hiragana.getWidth()/11), 0, hiragana.getWidth()/11, hiragana.getHeight()/5};
    char_clip[44] = {9*(hiragana.getWidth()/11), 4*(hiragana.getHeight()/5), hiragana.getWidth()/11, hiragana.getHeight()/5};
    char_clip[45] = {10*(hiragana.getWidth()/11), 0, hiragana.getWidth()/11, hiragana.getHeight()/5};
}
void close() {
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    TTF_CloseFont(gFont);
    gFont = NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    srand(time(0));
    if (!Init()) {
        return false;
    } else if (!loadMedia()) {
        return false;
    } else {
        SDL_Event e;
        bool quit = false;
        Option MODE = MAIN_MENU;
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }
            switch (MODE) {
                case MAIN_MENU: {

                    break;
                }
                case HIRAGANA: case KATAKANA: {

                    break;
                }
            }
        }
    }
}