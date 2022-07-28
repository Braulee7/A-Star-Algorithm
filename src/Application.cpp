#include <headers/Application.h>
#include <iostream>
#include <headers/Astar.h>

SDL_Renderer * Application::renderer = nullptr;
int Application::cols = 0;
int Application::rows = 0;
Node** Application::grid = nullptr;

Application:: Application()
{
    window = nullptr;
    screenHeight = 0;
    screenWidth = 0;
    running = true;
    stateNum = 0;
}

Application:: ~Application()
{
    SDL_DestroyRenderer(Application::renderer);
    SDL_DestroyWindow(window);

    for (int i = 0; i < Application::cols; i++)
    {
        delete [] Application::grid [i];
    }

    delete [] Application::grid;
}

void Application::init(const char* title, int width, int height, Uint32 flags)
{
    //initialise everything
    SDL_Init(SDL_INIT_EVERYTHING);

    screenHeight = height;
    screenWidth = width;

    //create the window and renderer
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
    Application::renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(Application::renderer, 255, 255, 255, 255);

    //* * * * * * *create the grid of nodes * * * * * *
    Application::cols = screenWidth / 20;
    Application::rows = screenHeight / 20;

    Application::grid = new Node* [Application::cols];

    for (int i = 0; i < Application::rows; i++)
    {
        Application::grid[i] = new Node [Application::rows];
    }

    for (int i = 0; i < Application::rows; i++)
    {
        for (int j = 0; j < Application::cols; j++)
        {
            Application::grid[i][j].init(screenWidth / Application::cols, screenHeight / Application::rows, j * (screenWidth / Application::cols), i * (screenHeight / Application::rows));
        }
    }

    //* * * * * * * * * * * * * * * * * * * * * * * *

    //visually show the start and endpoints of the program
    Application::grid[0][0].setState(1);
    Application::grid[rows - 1][cols - 1].setState(1);
    
}

void Application:: run()
{
    //initialise and start the loop
    init("A* simulation", 800, 800, SDL_WINDOW_SHOWN);
    Applicationloop();
}

void Application:: Applicationloop()
{
    //create a cap of frames
    const int FPS = 32;
    const int frame_delay = 1000/FPS;

    Uint32 framestart;
    int frameTime;

    int count = 0;

    while (running)
    {
        framestart = SDL_GetTicks();
        handleEvents();
        update();

        frameTime = SDL_GetTicks() - framestart;

        if (frame_delay > frameTime)
        {
            SDL_Delay(frame_delay - frameTime);
        }
    }
}


void Application::update()
{
    //draw all the cells onto the screen
    draw();
}

void Application::draw()
{


    SDL_RenderClear(Application::renderer);
    
    //draw each cell in the grid
    for (int i = 0; i < Application::cols; i++)
    {
        for (int j = 0; j < Application::rows; j++)
        {
            Application::grid[i][j].draw();
        }
    }

    //return the render color to white
    SDL_SetRenderDrawColor(Application::renderer, 255, 255, 255, 255);

    SDL_RenderPresent(Application::renderer);
}

void Application::handleEvents()
{
    SDL_PollEvent(&event);

    //check if the user has quit
    switch (event.type)
    {
        case SDL_QUIT:
            running = false;
            break;
        
        default:
            break;
    }

    //check for keyboard input
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_SPACE:
                //update the state number    
                ++stateNum;

                switch (stateNum)
                {

                    case 1://start the algorithm
                    {   
                        //get all the neighbours of the cells
                        for (int i = 0; i < Application::rows; i++)
                        {
                            for (int j = 0; j < Application::cols; j++)
                            {
                                Application::grid[i][j].GetNeighbours(Application::grid, screenWidth / Application::cols, screenHeight / Application::rows, Application::cols, Application::rows);
                            }
                        }

                        //begin the algorithm
                        Astar pathFinding(&Application::grid[0][0], &Application::grid[rows - 1][cols - 1]);

                        break;
                    }

                    case 2:
                    {
                        //restart the program
                        for (int i = 0; i < Application::rows; i++)
                        {
                            for (int j = 0; j < Application::cols; j++)
                            {
                                Application::grid[i][j].setState();
                            }
                        }
                        stateNum = 0;
                    }

                    default:
                        break;
                }


        }
    }

    //check for mouse input
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        switch (event.button.button)
        {
            case SDL_BUTTON_LEFT:

                int x, y;
                
                //get the position of the mouse
                SDL_GetMouseState(&x, &y);

                //check each cell individually to see if it was clicked
                for (int i = 0; i < Application::cols; i++)
                {
                    for (int j = 0; j < Application::rows; j++)
                    {
                        //once cliced break out the loop
                        if (Application::grid[i][j].isClicked(x, y))
                            break;
                    }
                }
        }
    }

}