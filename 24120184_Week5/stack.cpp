#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct NODE
{
    int key;
    NODE *p_next;
};

struct Stack
{
    NODE *top;
};

Stack *initalizeStack()
{
    Stack *s = new Stack();
    s->top = nullptr;
    return s;
}

NODE *CreateNode(int data)
{
    NODE *newnode = new NODE();
    newnode->key = data;
    newnode->p_next = nullptr;
    return newnode;
}

void push(Stack *&s, int key)
{
    NODE *newnode = CreateNode(key);
    newnode->p_next = s->top;
    s->top = newnode;
}

int pop(Stack *&s)
{
    if (s->top == nullptr)
    {
        return -1;
    }
    NODE *temp = s->top;
    int save = temp->key;
    s->top = temp->p_next;
    delete temp;
    return save;
}

int size(Stack *s)
{
    int cnt = 0;
    NODE *cur = s->top;
    while (cur != nullptr)
    {
        cnt++;
        cur = cur->p_next;
    }
    return cnt;
}

bool isEmpty(Stack *s)
{
    if (s->top == nullptr)
        return true;
    return false;
}

void deleteStack(Stack *&s)
{
    if (s->top == nullptr)
        return;
    NODE *cur = s->top;
    while (cur != nullptr)
    {
        NODE *temp = cur;
        cur = cur->p_next;
        delete temp;
    }
    s->top = nullptr;
    delete s;
}

void printStack(ofstream &out , Stack* s)
{
    if (isEmpty(s))
    {
        out << "EMPTY";
    }
    else{
        NODE* print = s->top;
        while (print != nullptr)
        {   
            out << print->key << " ";
            print = print->p_next;
        }
    }
    out << endl;
}

int main()
{   
    Stack *s;

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
            s = initalizeStack();
        }
        else if (temp == "push")
        {
            int value;
            in >> value;
            push(s,value);
        }
        else if (temp == "pop")
        {
            if (!isEmpty(s))
                pop(s);   
        }
        printStack(out,s);
    }
    in.close();
    out.close();
    deleteStack(s);
    return 0;
}
