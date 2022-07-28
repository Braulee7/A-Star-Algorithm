#pragma once

class Node;


struct ListNode 
{
    Node *data;
    ListNode* next;
};

class List
{
    public:
        ListNode* head;

        List();
        ~List();

        void Push(Node* data);
        void RemoveAll();
        int Length();

        Node* operator[](int i);
};