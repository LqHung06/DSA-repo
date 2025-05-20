#include <iostream>

using namespace std;

struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};

NODE* createNode(int data)
{
    NODE* newnode = new NODE;
    newnode->key = data;
    newnode->height = 0;
    newnode->p_left = nullptr;
    newnode->p_right = nullptr;
    return newnode;
}

int Height(NODE* node)
{
    if (node == nullptr) return 0;
    return node->height;
}

int GetBalance(NODE* node)
{   
    int left, right;
    if (node == nullptr)
        return 0;
    left = Height(node->p_left);
    right = Height(node->p_right);
    return left - right;
}

void updateHeight(NODE* node) {
    if (node != nullptr)
        node->height = 1 + max(Height(node->p_left), Height(node->p_right));
}

void LeftRotate(NODE* &node)
{
    NODE* node1 = node->p_right;
    NODE* Lnode1 = node->p_left;

    node1->p_left = node;
    node->p_right = Lnode1;

    updateHeight(node);
    updateHeight(node1);

    node = node1;
}

void RightRotate(NODE* &node)
{
    NODE* node1 = node->p_left;
    NODE* Rnode1 = node1->p_right;

    node1->p_right = node;
    node->p_left =Rnode1;

    updateHeight(node);
    updateHeight(node1);

    node = node1;
}

void balance(NODE* &node)
{
    updateHeight(node);
    int x = GetBalance(node);
    if (x > 1)
    {
        if (GetBalance(node->p_left) < 0)
            LeftRotate(node->p_left);
        RightRotate(node);
    }
    else if (x < -1)
    {
        if (GetBalance(node->p_right) > 0)
            RightRotate(node->p_right);
        LeftRotate(node);
    }
}

void Insert(NODE* &pRoot,int x)
{
    if (pRoot == nullptr) {
        pRoot = createNode(x);
        return;
    }

    if (x < pRoot->key)
        Insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        Insert(pRoot->p_right, x);
    else
        return;  

    balance(pRoot);
}

NODE* findMaxLeft(NODE* node)
{
    while (node->p_right != nullptr)
    {
        node = node->p_right;
    }
    return node;
}

void Remove(NODE* &pRoot,int x)
{
    if (pRoot == nullptr) return;
    else if (x > pRoot->key)
    {
        Remove(pRoot->p_right,x);
    }
    else if (x < pRoot->key)
    {
        Remove(pRoot->p_left,x);
    }
    else
    {
        if (pRoot->p_left == nullptr && pRoot->p_right != nullptr)
        {
            NODE* temp = pRoot->p_right;
            delete pRoot;
            pRoot = temp;
        }
        else if (pRoot->p_left != nullptr && pRoot->p_right == nullptr)
        {
            NODE* temp = pRoot->p_left;
            delete pRoot;
            pRoot = temp;
        }
        else if (pRoot->p_left == nullptr && pRoot->p_right == nullptr)
        {
            delete pRoot;
            pRoot = nullptr;
        }
        else
        {
            NODE* maxLeft = findMaxLeft(pRoot->p_left);
            pRoot->key = maxLeft->key;
            Remove(pRoot->p_left, maxLeft->key);
        }
        if (pRoot != nullptr)
        {
            updateHeight(pRoot);
            balance(pRoot);
        }
    }
}

int findMin(NODE* node)
{
    if (node == nullptr) return INT_MAX;
    int leftMin = findMin(node->p_left);
    int rightMin = findMin(node->p_right);

    return min(node->key,min(leftMin,rightMin));
}

int findMax(NODE* node)
{
    if (node == nullptr) return INT_MIN;
    int leftMax = findMax(node->p_left);
    int rightMax = findMax(node->p_right);

    return max(node->key,max(leftMax,rightMax));
}

bool isBST(NODE* pRoot)
{
    if (pRoot == nullptr) return true;
    int maxleft = INT_MIN;
    int minright = INT_MAX;
    if (pRoot->p_left != nullptr)
    {
        maxleft = findMax(pRoot->p_left);
    }
    if (pRoot->p_right != nullptr)
    {
        minright = findMin(pRoot->p_right);
    }
    if (pRoot->key > maxleft && pRoot->key < minright)
    {
        return (isBST(pRoot->p_left) && isBST(pRoot->p_right));
    }
    else
    {
        return false;
    }
    return true;
}

bool isAVL(NODE* pRoot)
{
    if (pRoot == nullptr)
        return true;
    int balance = GetBalance(pRoot);
    if (abs(balance) > 1)
        return false;
    if (!isBST(pRoot))
        return false;
    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}

