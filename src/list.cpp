#include <headers/list.h>

List:: List()
{
    head = nullptr;
}

List:: ~List()
{
    RemoveAll();
}

void List:: Push(Node *data)
{
    ListNode* temp = new ListNode;

    temp -> data = data;
    temp -> next = head;

    head = temp;
    
}

int List::Length()
{
    int count {0};
    ListNode* current = head;

    while (current)
    {
        ++count;
        current = current -> next;
    }

    return count;
}

Node* List::operator[](int i)
{
    if (!head)
        return nullptr;
    
    if (i > Length() || i < 0)
    {
        //out of bounds
        return head -> data;
    }

    int count = 0;

    ListNode* current = head;

    while (count != i)
    {
        current = current -> next;
        count++;
    }

    return current -> data;


}

void List::RemoveAll()
{
    while (head)
    {
        ListNode* temp = head -> next;

        delete head;
        
        head = temp;
    }
}