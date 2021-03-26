#include <iostream>
#include <string>
#include <fstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "class_timer.hpp"
#include "class_button.hpp"
#include "class_static_text_button.hpp"
#include "class_texture.hpp"
#include "class_text.hpp"
#include "enum_ButtonState.hpp"
#include "random_numbers.hpp"

using namespace std;

const int WINDOW_WIDTH = 300;
const int WINDOW_HEIGHT = 400;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;

enum Option {
    MAIN_MENU,
    HIRAGANA,
    KATAKANA
};
enum Romaji {
    a,      i,      u,      e,      o, 
    ka,     ki,     ku,     ke,     ko, 
    sa,     shi,    su,     se,     so, 
    ta,     chi,    tsu,    te,     to, 
    na,     ni,     nu,     ne,     no,
    ha,     hi,     fu,     he,     ho,
    ma,     mi,     mu,     me,     mo,
    ra,     ri,     ru,     re,     ro,
    ya,             yu,             yo,
    wa,                             wo,
                    n
};

ifstream file;
string romaji[46];

Texture japanese[2];
SDL_Rect char_clip[46];

StaticTextButton button_hiragana;
StaticTextButton button_katakana;
StaticTextButton button_quit;

StaticTextButton answer[46];

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
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        }
    }
    return true;
}
bool loadMedia() {
    file.open("data/romaji.txt");
    if (!file) {
        return false;
    }
    for (int i=0; i<46; i++) {
        file >> romaji[i];
    }

    gFont = TTF_OpenFont("data/segoeui.ttf", 16);
    if (gFont == NULL) {
        return false;
    } else {
        button_hiragana.setText(gRenderer, gFont, "Hiragana", {0, 0, 0});
        button_katakana.setText(gRenderer, gFont, "Katakana", {0, 0, 0});
        button_quit.setText(gRenderer, gFont, "Quit", {0, 0, 0});
    }

    for (int i=0; i<46; i++) {
        answer[i].setText(gRenderer, gFont, romaji[i], {0, 0, 0});
    }

    if (!japanese[HIRAGANA].loadFromFile(gRenderer, "data/hiragana.png", 0)) {
        return false;
    }
    if (!japanese[KATAKANA].loadFromFile(gRenderer, "data/katakana.png", 0)) {
        return false;
    }
    int index_x = 0, index_y = 0;
    // damn photoshop is hard to use
    for (int i=0; i<35; i++) {
        char_clip[i] = {index_x, index_y, japanese[HIRAGANA].getWidth()/11, japanese[HIRAGANA].getHeight()/5};
        index_y += (japanese[HIRAGANA].getHeight()/5);
        if (index_y == japanese[HIRAGANA].getHeight()) {
            index_y = 0;
            index_x += japanese[HIRAGANA].getWidth()/11;
        }
    }
    index_x = 8*(japanese[HIRAGANA].getWidth()/11);
    index_y = 0;
    for (int i=35; i<40; i++) {
        char_clip[i] = {index_x, index_y, japanese[HIRAGANA].getWidth()/11, japanese[HIRAGANA].getHeight()/5};
        index_y += japanese[HIRAGANA].getHeight()/5;
    }
    char_clip[40] = {7*(japanese[HIRAGANA].getWidth()/11), 0, japanese[HIRAGANA].getWidth()/11, japanese[HIRAGANA].getHeight()/5};
    char_clip[41] = {7*(japanese[HIRAGANA].getWidth()/11), 2*(japanese[HIRAGANA].getHeight()/5), japanese[HIRAGANA].getWidth()/11, japanese[HIRAGANA].getHeight()/5};
    char_clip[42] = {7*(japanese[HIRAGANA].getWidth()/11), 4*(japanese[HIRAGANA].getHeight()/5), japanese[HIRAGANA].getWidth()/11, japanese[HIRAGANA].getHeight()/5};
    char_clip[43] = {9*(japanese[HIRAGANA].getWidth()/11), 0, japanese[HIRAGANA].getWidth()/11, japanese[HIRAGANA].getHeight()/5};
    char_clip[44] = {9*(japanese[HIRAGANA].getWidth()/11), 4*(japanese[HIRAGANA].getHeight()/5), japanese[HIRAGANA].getWidth()/11, japanese[HIRAGANA].getHeight()/5};
    char_clip[45] = {10*(japanese[HIRAGANA].getWidth()/11), 0, japanese[HIRAGANA].getWidth()/11, japanese[HIRAGANA].getHeight()/5};
    return true;
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

        int letter = 0;
        int speed = 10;
        int i_speed = 0;
        
        int answer_correct;
        int answer_wrong[3];
        random_numbers(46, answer_correct, answer_wrong[0], answer_wrong[1], answer_wrong[2]);

        while (!quit) {
            int real_answer = rand()%46+1;
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else {
                    if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                            case SDLK_ESCAPE:
                                MODE = MAIN_MENU;
                                break;
                        }
                    }
                }
                button_hiragana.handleEvent(&e);
                button_katakana.handleEvent(&e);
                button_quit.handleEvent(&e);

                for (int i=0; i<46; i++) {
                    answer[i].handleEvent(&e);
                }
            }
            switch (MODE) {
                case MAIN_MENU: {
                    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                    SDL_RenderClear(gRenderer);

                    button_hiragana.setDimension(WINDOW_WIDTH/4, WINDOW_HEIGHT/8, WINDOW_WIDTH/2, WINDOW_HEIGHT/8);
                    button_katakana.setDimension(WINDOW_WIDTH/4, WINDOW_HEIGHT/8*3, WINDOW_WIDTH/2, WINDOW_HEIGHT/8);
                    button_quit.setDimension(WINDOW_WIDTH/4, WINDOW_HEIGHT/4*3, WINDOW_WIDTH/2, WINDOW_HEIGHT/8);
                    
                    button_hiragana.render(gRenderer);
                    button_katakana.render(gRenderer);
                    button_quit.render(gRenderer);

                    if (button_hiragana.getState() == BUTTON_MOUSE_UP) {
                        MODE = HIRAGANA;
                        break;
                    }
                    if (button_katakana.getState() == BUTTON_MOUSE_UP) {
                        MODE = KATAKANA;
                        break;
                    }
                    if (button_quit.getState() == BUTTON_MOUSE_UP) {
                        quit = true;
                        break;
                    }

                    SDL_RenderPresent(gRenderer);
                    break;
                }
                case HIRAGANA: case KATAKANA: {
                    bool ifAnswerWrong = false;
                    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                    SDL_RenderClear(gRenderer);

                    answer[answer_correct].setDimension(30, 240, 105, 50);
                    answer[answer_wrong[0]].setDimension(30, 320, 105, 50);
                    answer[answer_wrong[1]].setDimension(165, 240, 105, 50);
                    answer[answer_wrong[2]].setDimension(165, 320, 105, 50);

                    answer[answer_correct].render(gRenderer);
                    answer[answer_wrong[0]].render(gRenderer);
                    answer[answer_wrong[1]].render(gRenderer);
                    answer[answer_wrong[2]].render(gRenderer);

                    japanese[MODE].setPosition(120, 80);
                    japanese[MODE].render(gRenderer, &char_clip[answer_correct]);

                    if (answer[answer_correct].getState() == BUTTON_MOUSE_UP) {
                        random_numbers(46, answer_correct, answer_wrong[0], answer_wrong[1], answer_wrong[2]);
                    }

                    SDL_RenderPresent(gRenderer);
                    break;
                }
            }
        }
    }
    close();
    return 0;
}