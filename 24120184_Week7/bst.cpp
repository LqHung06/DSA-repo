#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct NODE
{
    int key;
    NODE* p_left;
    NODE* p_right;
};

void search(NODE* node,int x,NODE* &save)
{   
    if (node == nullptr) return;
    if (node->key == x)
    {
        save = node;
        return;
    }
    search(node->p_left,x,save);
    search(node->p_right,x,save);
}

NODE* Search(NODE* pRoot, int x)
{
    NODE* save;
    search(pRoot,x,save);
    return save;
}

NODE* createNode(int data)
{
    NODE* newNode = new NODE;
    newNode->key = data;
    newNode->p_left = nullptr;
    newNode->p_right = nullptr;
    return newNode;
}

void Insert(NODE* &pRoot, int x)
{   
    if (pRoot == nullptr)  
    {
        pRoot = createNode(x);
        return;
    }
    NODE* newnode = createNode(x);
    if (pRoot->key > x)
    {   
        Insert(pRoot->p_left,x);
    }
    else if (pRoot->key < x)
    {   
        Insert(pRoot->p_right,x);
    }
    else
    {
        return;
    }
}

void Remove(NODE* &pRoot,int x)
{   
    if (pRoot == nullptr) return;
    if (x < pRoot->key)
        Remove(pRoot->p_left ,x);
    else if (x > pRoot->key)
        Remove(pRoot->p_right,x);
    else
    {
        if (pRoot->p_left == nullptr && pRoot->p_right == nullptr)
        {
            delete pRoot;
            pRoot = nullptr;
        }
        else if (pRoot->p_left == nullptr && pRoot->p_right != nullptr)
        {
            NODE* cur = pRoot;
            pRoot = pRoot->p_right;
            delete cur;
        }
        else if (pRoot->p_left != nullptr && pRoot->p_right == nullptr)
        {
            NODE* cur = pRoot;
            pRoot = pRoot->p_left;
            delete cur;
        }
        else if (pRoot->p_left != nullptr && pRoot->p_right != nullptr)
        {
            NODE* cur = pRoot->p_left;
            while (cur->p_right != nullptr)
            {
                cur = cur->p_right;
            }
            pRoot->key = cur->key;
            Remove(pRoot->p_left, cur->key);
        }
    }
}

NODE* createTree(int a[],int n)
{
    NODE* pRoot = createNode(a[0]);
    for (int i = 1; i < n ;i++)
    {
        Insert(pRoot,a[i]);
    }
    return pRoot;
}

void removeTree(NODE* &pRoot)
{   
    if (pRoot->p_left != nullptr)
        removeTree(pRoot->p_left);
    if (pRoot->p_right != nullptr)
        removeTree(pRoot->p_right);
    if (pRoot->p_left == nullptr && pRoot->p_right == nullptr)
    {
        NODE* cur = pRoot;
        pRoot = nullptr;
        delete cur;
        return;
    }
}

int Height(NODE* pRoot)
{
    if (pRoot == nullptr) return 0;
    int heightLeft = Height(pRoot->p_left);
    int heightRight = Height(pRoot->p_right);
    return max(heightLeft , heightRight) + 1;
}

int countLess(NODE* pRoot, int x)
{
    if (pRoot == nullptr) return 0;
    if (pRoot->key < x)
    {
        return countLess(pRoot->p_left,x) + countLess(pRoot->p_right,x) + 1;
    }
    else
    {
        return countLess(pRoot->p_left,x);
    }
}

int countGreater(NODE* pRoot, int x)
{
    if (pRoot == nullptr) return 0;
    if (pRoot->key > x)
    {
        return countGreater(pRoot->p_left,x) + countGreater(pRoot->p_right,x) + 1;
    }
    else
    {
        return countGreater(pRoot->p_right,x);
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

bool isFullNODE(NODE* pRoot)
{
    if (pRoot == nullptr) return true;
    if (pRoot->p_left == nullptr && pRoot->p_right != nullptr)
    {
        return false;
    }
    if (pRoot->p_left != nullptr && pRoot->p_right == nullptr)
    {
        return false;
    }
    return (isFullNODE(pRoot->p_left) && isFullNODE(pRoot->p_right));
}

bool isFullBST(NODE* pRoot)
{
    return (isFullNODE(pRoot) && isBST(pRoot));
}
