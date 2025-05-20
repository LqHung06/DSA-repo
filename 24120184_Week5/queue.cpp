#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct NODE
{
    int key;
    NODE* p_next;
};

struct Queue
{
    NODE* head;
    NODE* tail;
};

Queue* initializeQueue()
{
    Queue *q = new Queue();
    q->head = nullptr;
    q->tail = nullptr;
    return q;
}

NODE *CreateNode(int data)
{
    NODE *newnode = new NODE();
    newnode->key = data;
    newnode->p_next = nullptr;
    return newnode;
}

void enqueue(Queue *&q,int key)
{   
    NODE* newnode = CreateNode(key);
    if (q->head == nullptr)
    {
        q->head = newnode;
        q->tail = newnode;
        return;
    }
    q->tail->p_next = newnode;
    q->tail = newnode;
}

int dequeue(Queue *&q)
{
    if (q->head == nullptr)
    {
        return -1;
    }
    int val = q->head->key;
    if (q->head->p_next == nullptr)
    {   
        NODE* temp = q->head;
        q->head = nullptr;
        q->tail = nullptr;
        delete temp;
        return val;
    }
    NODE* temp = q->head;
    q->head = temp->p_next;
    delete temp;
    return val;
}

int size(Queue *q)
{
    int num = 0;
    NODE* cur = q->head;
    while (cur != nullptr)
    {   
        num++;
        cur = cur->p_next;
    }
    return num;
}

bool isEmpty(Queue *q)
{
    if (q->head == nullptr)
        return true;
    return false;
}

void deleteQueue(Queue *&q)
{
    if (q->head == nullptr)
        return;
    NODE* cur = q->head;
    while (cur != nullptr)
    {   
        NODE* temp = cur;
        cur = cur->p_next;
        delete temp;
    }
    q->head = nullptr;
    q->tail = nullptr;
    delete q;
}

void printQueue(ofstream& out, Queue *q)
{
    if (q->head == nullptr)
    {
        out << "EMPTY" << endl;
        return;
    }
    NODE* cur = q->head;
    while (cur !=  nullptr)
    {   
        out << cur->key << " ";
        cur = cur->p_next;
    }
    out << endl;
}

int main()
{   
    Queue* q;
    ofstream out("output.txt");
    ifstream in("input.txt");
    if (!out.is_open())
    {
        cout << "Khong the mo file output" << endl;
        return 0;
    }
    if (!in.is_open())
    {
        cout << "Khong the mo file input" << endl;
        return 0;
    }
    string temp;
    while (in >> temp)
    {
        if (temp == "init")
        {
            q = initializeQueue();
        }
        else if (temp == "enqueue")
        {
            int value;
            in >> value;
            enqueue(q,value);
        }
        else if (temp == "dequeue")
        {
            dequeue(q);
        }
        printQueue(out,q);
    }
    in.close();
    out.close();
    deleteQueue(q);
    return 0;
}