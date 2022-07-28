#include <headers/heap.h>
#include <iostream>


Heap::Heap(int capacity)
{
    this->capacity = capacity;
    //start index at 0
    size = 0;

    //dynamically allocate the heap
    heap = new Node* [capacity];
}

Heap::~Heap()
{
    capacity = 0;
    size = 0;

    delete [] heap;
}

int Heap::getLeftChildIndex(int parentIndex)
{
    return 2 * parentIndex + 1;
}

int Heap::getRightChildIndex(int parentIndex)
{
    return 2 * parentIndex + 2;
}

int Heap::getParentIndex(int childIndex)
{
    return (childIndex - 1) / 2;
}

bool Heap::hasLeftChild(int index)
{
    return getLeftChildIndex(index) < size;
}

bool Heap::hasRightChild(int index)
{
    return getRightChildIndex(index) < size;
}

bool Heap::hasParent(int index)
{
    return getParentIndex(index) >= 0;
}

int Heap::leftChild(int index)
{
    return heap[getLeftChildIndex(index)]->fcost();
}

int Heap::rightChild(int index)
{
    return heap[getRightChildIndex(index)]->fcost();
}

int Heap::parent(int index)
{
    return heap[getParentIndex(index)]->fcost();
}

void Heap::Add(Node* toAdd, int state)
{
    checkCapacity();

    toAdd->setState(state);

    heap[size] = toAdd;
    size++;

    //std::cout << toAdd->fcost() << std::endl;

    heapSortUp();
}

Node* Heap::Peek()
{
    if (size == 0)
        return nullptr;

    //returns the top item
    return heap[0];
}

Node* Heap::Poll()
{
    if (size == 0)
        return nullptr;
    
    Node* item = heap[0];

    heap[0] = heap[size - 1];
    size--;
    heapSortDown();
    return item;
}

bool Heap::checkCapacity()
{
    if (size == capacity)
    {
        Node** temp = new Node*[capacity * 2];

        for (int i = 0; i < capacity; i++)
        {
            temp [i] = heap[i];
        }

        capacity = capacity * 2;
        delete [] heap;

        heap = temp;
        return true;
    }

    return false;
}

void Heap::heapSortDown()
{
    int index = 0;
    while (hasLeftChild(index))
    {
        int smallerChild = getLeftChildIndex(index);
        if (hasRightChild(index) && rightChild(index) < leftChild(index))
        {
            smallerChild = getRightChildIndex(index);
        }

        if (heap[index]->fcost() > heap[smallerChild]->fcost())
        {
            swap(index, smallerChild);
            index = smallerChild;
        } else 
            break;
    }
}

void Heap::heapSortUp()
{
    int index = size - 1;

    while (hasParent(index) && parent(index) > heap[index]->fcost())
    {
        swap(getParentIndex(index), index);
        index = getParentIndex(index);
    }
}

bool Heap::swap(int index_one, int index_two)
{
    Node* temp = heap[index_one];

    heap[index_one] = heap[index_two];

    heap[index_two] = temp;

    return true;
}

bool Heap::includes(Node* toCompare)
{
    for (int i = 0; i < size; i++)
    {
        if (heap[i] == toCompare)
            return true;
    }

    return false;
}

void Heap::Draw()
{
    if (size == 0)
    {
        return;
    }

    for (int i = 0; i < size; i++)
    {
        heap[i]->draw();
    }
}

