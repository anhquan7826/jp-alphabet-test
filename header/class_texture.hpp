#ifndef CLASS_TEXTURE
#define CLASS_TEXTURE

#include <SDL.h>
#include <string>

using namespace std;

class Texture {
    private:
        SDL_Texture* texture;
        int x;
        int y;
        int w; 
        int h;
    public:
        Texture();
        void free();
        int getWidth();
        int getHeight();
        void setPosition(int _x, int _y);
        void setDimension(int _w, int _h);
        bool loadFromFile(SDL_Renderer* gRenderer, string path, int isKeyColor);
        void render(SDL_Renderer* gRenderer, SDL_Rect* clip);
        bool isTextureNULL();
};

#endif