#pragma once

#include <sdl/SDL.h>
#include <headers/node.h>

class Node;

class Application 
{
    private:
        SDL_Window* window;
        int screenWidth;
        int screenHeight;

        bool running;

        //for 2d array of nodes
        static int rows;
        static int cols;
        static Node** grid;

        int stateNum;

        void init(const char* title, int width, int height, Uint32 flags);
        void Applicationloop();
        void render();
        void update();
        void handleEvents();

        

    public:
        static SDL_Renderer* renderer;
        SDL_Event event;
        static void draw();
        Application();
        ~Application();
        void run();

};