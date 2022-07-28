#pragma once

#include <sdl/SDL.h>
#include <vector>
#include <headers/Application.h>
#include <headers/list.h>

enum class State {
    Obstacle,
    Open,
    Closed,
    Start,
    End
};


class Node
{
    private:
        int height;
        int width;


        State currentState;
        

        SDL_Rect rect;
        SDL_Surface *surf;

        bool checkState(Node* cell);


        
    public:
        int hcost;
        int gcost;
        int fcost();
        int posX;
        int posY;

        Node* previous;
        
        
        List neighbours;


        Node();
        ~Node();    

        void init(int width, int height, int x, int y);
        void update();
        void draw();

        bool isClicked(int x, int y);
        void setState(int state = 0);
        void GetNeighbours(Node** grid, int xDiv, int yDiv, int cols, int rows);

};

