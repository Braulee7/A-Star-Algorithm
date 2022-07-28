#include <headers/Astar.h>
#include <math.h>
#include <iostream>
#include <headers/Application.h>


Astar::Astar(Node* start, Node* end)
{
    start->setState(1);
    OpenSet.Add(start, 1);


    while (OpenSet.size != 0)
    {
        Node* current = OpenSet.Poll();

        if (current == end)
        {
            end->setState(1);
            ReconstructPath(current);
            std::cout << "Found the end" << std::endl;
            return;
        }
        
        ClosedSet.Add(current, 3);
        
        for (int i = 0; i < current->neighbours.Length(); i++)
        {
            //if it's not in the closed set
            if (!ClosedSet.includes(current->neighbours[i]))
            {    
                //get a temporary g cost we will compare later
                //if it's already in the open set
                int tempG = current->neighbours[i]->gcost + 10;
                
                if (OpenSet.includes(current->neighbours[i]))
                {
                    //compare the temporary g cost to the current
                    //g cost
                    if (tempG < current->neighbours[i]->gcost)
                    {
                        //record the path and update the g cost
                        cameFrom.Add(current->neighbours[i], 2);
                        current->neighbours[i]->gcost = tempG;
                        std::cout << "added to the cameFrom list\n";
                    }
                } else 
                    {
                        //calculate the h and g cost
                        current->neighbours[i]->gcost = tempG;
                        current->neighbours[i]->hcost = Heuristic(current->neighbours[i], end);

                        //add the current node to the open set
                        OpenSet.Add(current->neighbours[i], 3);

                        //add which node it came from
                        current->neighbours[i]->previous = current;
                    }


            }  
            
            //update the computers visited nodes as it goes on
            Application::draw();
        }
    }

    //path is not accesible
    std::cout << "Could not find a path to the end\n";
}

int Astar::Heuristic(Node* current, Node* end)
{
    //uses the raw distance by calculating with 
    //the distance formula
    int total = 0;
    
    int insideX = pow((end->posX - current->posX), 2);
    int insideY = pow((end->posY - current->posY), 2);

    total = sqrt(insideX + insideY);

    return total;
}

void Astar::ReconstructPath(Node* cell)
{
    //recursive base case
    if (cell->previous == nullptr)
    {
        cell->setState(1);
        return;
    }

    //change the state to start
    //to visually change the path to blue
    cell->setState(1);
    ReconstructPath(cell->previous);
}