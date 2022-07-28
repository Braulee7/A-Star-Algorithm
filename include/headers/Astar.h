#pragma once

#include <headers/heap.h>

class Astar
{
    public:
        
        Astar(Node* start, Node* end);
        
    private:
        Heap cameFrom;
        void ReconstructPath(Node* cell);
        Heap OpenSet;
        Heap ClosedSet;
        int Heuristic(Node* current, Node* end);
};