#ifndef CLASS_TEXT
#define CLASS_TEXT

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

class Text {
    private:
        SDL_Texture* texture;
        int x, y;
        int w, h;
    public:
        Text();
        void free();
        int getWidth();
        int getHeight();
        SDL_Texture* getTexture();
        void setPosition(int _x, int _y);
        void loadFromText(SDL_Renderer* gRenderer, TTF_Font* gFont, string text, SDL_Color color);
        void render(SDL_Renderer* gRenderer);
};

#endif