#pragma once

#include <headers/node.h>

class Heap
{
    public:
        //keep track of the current index and size 
        //of the heap
        int size;

        //heap will be a dynamically allocated array
        //of node pointers
        Node** heap;


        //default constructor takes in a size for the 
        //array
        Heap(int capacity = 15);
        ~Heap();

        void Add(Node* toAdd, int state = 0);
        Node* Peek();
        Node* Poll();

        void Draw();

        bool includes(Node* toCompare);

    private:
        int capacity;

        int getLeftChildIndex(int parentIndex);
        int getRightChildIndex(int parentIndex);
        int getParentIndex(int childIndex);

        bool hasLeftChild(int index);
        bool hasRightChild(int index);
        bool hasParent(int index);

        int leftChild(int index);
        int rightChild(int index);
        int parent(int index);

        bool swap(int index_one, int index_two);
        bool checkCapacity();
        void heapSortUp();
        void heapSortDown();

};