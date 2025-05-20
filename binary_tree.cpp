#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct NODE
{
    int key;
    NODE* p_left;
    NODE* p_right;
};

NODE* createNode(int data)
{
    NODE* newNode = new NODE;
    newNode->key = data;
    newNode->p_left = nullptr;
    newNode->p_right = nullptr;
    return newNode;
}

void PreOrder(NODE* node,vector<int> &result)
{
    if (node != nullptr)
    {
        result.push_back(node->key);
        PreOrder(node->p_left,result);
        PreOrder(node->p_right,result);
    }
}

vector<int> NLR(NODE* pRoot)
{   
    vector<int> result;
    PreOrder(pRoot,result);
    return result;
}

void InOrder(NODE* node,vector<int> &result)
{
    if (node != nullptr)
    {
        InOrder(node->p_left,result);
        result.push_back(node->key);
        InOrder(node->p_right,result);
    }
}

vector<int> LNR(NODE* pRoot)
{
    vector<int> result;
    InOrder(pRoot,result);
    return result;
}

void PostOrder(NODE* node,vector<int> &result)
{
    if (node != nullptr)
    {
        PostOrder(node->p_left,result);
        PostOrder(node->p_right,result);
        result.push_back(node->key);
    }
}

vector<int> LRN(NODE* pRoot)
{
    vector<int> result;
    PostOrder(pRoot,result);
    return result;
}

vector<vector<int>> LevelOrder(NODE* pRoot)
{
    vector<vector<int>> result;
    if (pRoot == nullptr)  return result;
    queue<NODE*> q;

    q.push(pRoot);
    while (!q.empty())
    {
        vector<int> cur;
        int nodeInLevel = q.size();
        for (int i = 0; i < nodeInLevel ;i++)
        {
            NODE* curNode = q.front();
            if (curNode == nullptr) continue;
            cur.push_back(curNode->key);
            if (curNode->p_left != nullptr)
                q.push(curNode->p_left);
            if (curNode->p_right != nullptr)
                q.push(curNode->p_right);
            q.pop();
        }
        result.push_back(cur);
    }
    return result;
}

int countNode(NODE* pRoot)
{
    int cnt = 0;
    if (pRoot == nullptr) return cnt;
    queue<NODE*> q;
    q.push(pRoot);
    while (!q.empty())
    {
        int NodeInLevel = q.size();
        for (int i = 0; i < NodeInLevel ;i++)
        {
            NODE* curNode = q.front();
            if (curNode == nullptr) continue;
            cnt++;
            if (curNode->p_left != nullptr)
                q.push(curNode->p_left);
            if (curNode->p_right != nullptr)
                q.push(curNode->p_right);
            q.pop();
        }
    } 
    return cnt; 
}

int sumNode(NODE* pRoot)
{
    int sum = 0;
    queue<NODE*> q;
    q.push(pRoot);
    while (!q.empty())
    {
        int NodeInLevel = q.size();
        for (int i = 0; i < NodeInLevel ;i++)
        {
            NODE* curNode = q.front();
            if (curNode == nullptr) continue;
            sum += curNode->key;
            if (curNode->p_left != nullptr)
                q.push(curNode->p_left);
            if (curNode->p_right != nullptr)
                q.push(curNode->p_right);
            q.pop();
        }
    }
    return sum;
}

int findHeight(NODE* Node,int value,int &h)
{
    if (Node == nullptr) return -1;
    int findleft = findHeight(Node->p_left,value,h);
    int findright = findHeight(Node->p_right,value,h);
    int temp = max(findleft,findright) + 1;
    if (Node->key == value)
    {
        h = temp;
    }
    return temp;
}

int heightNode(NODE* pRoot, int value)
{    
    int h = -1;
    findHeight(pRoot,value,h);
    return h;
}

void findLevel(NODE* node,NODE* p,int &level,int curlevel)
{   
    if (node == nullptr) return;
    if (p == node) 
    {
        level = curlevel;
    }

    findLevel(node->p_left,p,level,curlevel + 1);
    findLevel(node->p_right,p,level,curlevel + 1);
}

int Level(NODE* pRoot,NODE* p)
{
    int level = -1;
    findLevel(pRoot,p,level,0);
    return level;
}

void count(NODE* node, int &cnt)
{
    if (node == nullptr) return;
    count(node->p_left,cnt);
    count(node->p_right,cnt);
    if (node->p_left == nullptr && node->p_right == nullptr)
    {
        cnt++;
    }
}

int countLeaf(NODE* pRoot)
{
    int cnt = 0;
    count(pRoot,cnt);
    return cnt;
}