#ifndef CLASS_ANIMATION
#define CLASS_ANIMATION

#include <string>
#include <vector>
#include <SDL.h>

using namespace std;

class Animation {
    private:
        SDL_Texture* texture;
        vector<SDL_Rect> frame_clip;
        int frame;
        int x;
        int y;
        int w;
        int h;
    public:
        Animation(int _frame);
        void free();
        int getWidth();
        int getHeight();
        void setPosition(int _x, int _y);
        void setDimension(int _w, int _h);
        bool loadFromFile(SDL_Renderer* gRenderer, string path, int isKeyColor);
        void render(SDL_Renderer* gRenderer, int iFrame);
};

#endif