#include <headers/node.h>
#include <headers/Application.h>
#include <iostream>



Node:: Node()
{
   height = 0; 
   width = 0;
   posX = 0;
   posY = 0;

   rect.x = rect.y = rect.h = rect.w = 0;

   surf = nullptr;

   gcost = 0;
   hcost = 0;

   previous = nullptr;
}


Node:: ~Node()
{

}

int Node::fcost()
{
    return this->hcost + this->gcost;
}

void Node:: init(int width, int height, int x, int y)
{
    this -> height = height;
    this -> width = width;
    this -> posX = x;
    this -> posY = y;

    //create rect
    rect.x = posX;
    rect.y = posY;
    rect.h = this -> height;
    rect.w = this -> width;

    //create the surface
    surf = SDL_CreateRGBSurface(0, this -> width, this -> height, 32, 0, 0, 0, 0);

    //all nodes are initialised to closed state
    currentState = State::Closed;



}


void Node::draw()
{
    switch (currentState)
    {
        //set color to white for unsearched
        case State::Closed:
            SDL_SetRenderDrawColor(Application::renderer, 0, 0, 0, 0);
            SDL_RenderDrawRect(Application::renderer, &rect);
            break;

        //set color to green for open
        case State::Open:
            SDL_SetRenderDrawColor(Application::renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(Application::renderer, &rect);
            break;

        //set color to blue for start
        case State::Start:
            SDL_SetRenderDrawColor(Application::renderer, 0, 0, 255, 255);
            SDL_RenderFillRect(Application::renderer, &rect);
            break;

        //set color to black for an obstacle
        case State::Obstacle:
            SDL_SetRenderDrawColor(Application::renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(Application::renderer, &rect);
            break;

        case State::End:
            SDL_SetRenderDrawColor(Application::renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(Application::renderer, &rect);
            break;
    }

    
}

bool Node::isClicked(int x, int y)
{

    //if the click collides with the node
    //change the node to an obstacle
    if (x >= posX && x <= posX + width)
    {
        if (y >= posY && y <= posY + height)
        {
            currentState = State::Obstacle;

            return true;
        }
    } 

    return false;
}

void Node::setState(int state)
{
    //what state is this node {1 = start, 2 = end, 3 = open, 0 = closed}

    switch (state)
    {
        case 0:
            currentState = State::Closed;
            break;
        
        case 1:
            currentState = State::Start;
            break;

        case 2:
            currentState = State::End;
            break;

        case 3:
            currentState = State::Open;
            break;
    }

}

void Node:: GetNeighbours(Node** grid, int xDiv, int yDiv, int cols, int rows)
{

    //clear the current list of neighbours
    neighbours.RemoveAll();

    int j = posX / xDiv;
    int i = posY / yDiv;

    //checks for the diagonals of the grid
    bool yHigh {false};
    bool xHigh {false};
    bool xLow {false};
    bool yLow {false};

    //check if not on top edge
    if (i > 0)
    {
        if (checkState(&grid[i - 1][j]))
        {
            neighbours.Push(&grid[i - 1][j]);
            yHigh = true;
        }
    }

    //check against the left edge
    if (j > 0)
    {
        if (checkState(&grid[i][j - 1]))
        {
            neighbours.Push(&grid[i][j - 1]);
            xHigh = true;
        }
    }

    //bottom edge
    if (i < rows - 1)
    {
        if (checkState(&grid[i + 1][j]))
        {
            neighbours.Push(&grid[i + 1][j]);
            yLow = true;
        }
    }

    //right edge
    if (j < rows - 1)
    {
        if (checkState(&grid[i][j + 1]))
        {
            neighbours.Push(&grid[i][j + 1]);
            xLow = true;
        }
    }

    /*
     * if diagonals want to be added they are below
     */

    //check the top row
    if (yHigh)
    {
        //top left diagonal
        if (xHigh && checkState(&grid[i - 1][j - 1]))
            neighbours.Push(&grid[i - 1][j - 1]);
        //top right diagonal
        if (xLow && checkState(&grid[i - 1][j + 1]))
            neighbours.Push(&grid[i - 1][j + 1]);
    }

    //against the bottom row
    if (yLow)
    {
        //bottom left diagonal
        if (xHigh && checkState(&grid[i + 1][j - 1]))
            neighbours.Push(&grid[i + 1][j - 1]);
        //bottom right diagonal
        if (xLow && checkState(&grid[i + 1][j + 1]))
            neighbours.Push(&grid[i + 1][j + 1]);
    }
        

}

bool Node::checkState(Node* cell)
{
    //return false if the cell is an obstacle
    if (cell->currentState == State::Obstacle)
        return false;
    
    return true;
}

