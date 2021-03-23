#ifndef CLASS_WINDOW
#define CLASS_WINDOW

#include <SDL.h>
#include <string>

using namespace std;

class Window
{
    public:
        Window();
        bool init(string title, int w, int h);
        void close();
        SDL_Renderer* createRenderer();
        void handleEvent(SDL_Event& e, SDL_Renderer* gRenderer);
        void free();
        int getWidth();
        int getHeight();
        void setFullscreen();
        bool hasMouseFocus();
        bool hasKeyboardFocus();
        bool is_Minimized();
    private:
        SDL_Window* window;
        int width;
        int height;
        bool isMouseFocus;
        bool isKeyboardFocus;
        bool isFullScreen;
        bool isMinimized;
};

#endif