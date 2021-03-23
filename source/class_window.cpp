#include "class_window.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <SDL.h>

using namespace std;

Window::Window() {
    window = NULL;
    isMouseFocus = false;
    isKeyboardFocus = false;
    isFullScreen = false;
    isMinimized = false;
    width = 0;
    height = 0;
}
bool Window::init(string title, int w, int h) {
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        return false;
    } else {
        isMouseFocus = true;
        isKeyboardFocus = true;
        width = w;
        height = h;
    }
    return true;
}
void Window::close() {
    SDL_DestroyWindow(window);
    window == NULL;
}
SDL_Renderer* Window::createRenderer() {
    return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}
void Window::handleEvent(SDL_Event& e, SDL_Renderer* gRenderer) {
    if (gRenderer == NULL) {cout << "gRenderer is NULL" << endl;}
    if (e.type == SDL_WINDOWEVENT) {
    //    bool updateCaption = false;
        switch (e.window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                width = e.window.data1;
                height = e.window.data2;
                SDL_RenderPresent(gRenderer);
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                SDL_RenderPresent(gRenderer);
                break;
            case SDL_WINDOWEVENT_ENTER:
                isMouseFocus = true;
            //    updateCaption = true;
                break;
            case SDL_WINDOWEVENT_LEAVE:
                isMouseFocus = false;
            //    updateCaption = true;
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                isKeyboardFocus = true;
            //    updateCaption = true;
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                isKeyboardFocus = false;
            //    updateCaption = true;
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                isMinimized = true;
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                isMinimized = false;
                break;
            case SDL_WINDOWEVENT_RESTORED:
                isMinimized = false;
                break;
        }
    /*  if (updateCaption) {
            stringstream caption;
            caption << "SDL Tutorial - MouseFocus:" << ((isMouseFocus) ? "On" : "Off") << " KeyboardFocus:" << ((isKeyboardFocus) ? "On" : "Off");
            SDL_SetWindowTitle(window, caption.str().c_str());
        } */
    }
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F11) {
        if (isFullScreen) {
            SDL_SetWindowFullscreen(window, SDL_FALSE);
            isFullScreen = false;
        } else {
            SDL_SetWindowFullscreen(window, SDL_TRUE);
            isFullScreen = true;
            isMinimized = false;
        }
    }
}
int Window::getWidth() {
    return width;
}
int Window::getHeight() {
    return height;
}
void Window::setFullscreen() {
    if (isFullScreen) {
        SDL_SetWindowFullscreen(window, SDL_FALSE);
        isFullScreen = false;
    } else {
        SDL_SetWindowFullscreen(window, SDL_TRUE);
        isFullScreen = true;
        isMinimized = false;
    }
}
bool Window::hasMouseFocus() {
    return isMouseFocus;
}
bool Window::hasKeyboardFocus() {
    return isKeyboardFocus;
}
bool Window::is_Minimized() {
    return isMinimized;
}