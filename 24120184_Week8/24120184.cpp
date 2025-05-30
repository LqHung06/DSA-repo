#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

const int INF = 1e9;

vector<vector<int>> convertMatrixToList(const string& filename);

vector<vector<int>> convertListToMatrix(const string& filename);

bool isDirected(const vector<vector<int>> adjMatrix);

int countVertices(const vector<vector<int>>& adjMatrix);

int countEdges(const vector<vector<int>>& adjMatrix);

bool isCompleteGraph(const vector<vector<int>>& adjMatrix);

bool isBipartite(const std::vector<std::vector<int>>& adjMatrix);

bool isCompleteBipartite(const vector<vector<int>>& adjMatrix);

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix);

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix);

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix);

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix);

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start);

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start);

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix);

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix);

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix);

vector<vector<int>> convertMatrixToList(const string& filename)
{
    ifstream fIn(filename);
    vector<vector<int>> List;
    if (!fIn.is_open())
    {
        cout << "Cannot open inputfie" << endl;
    }
    int n;
    fIn >> n;
    vector<int> num = { 9 };
    List.push_back(num);
    for (int i = 0; i < n ;i++)
    {   
        vector<int> ListInLine;
        vector<int> save;
        int cnt = 0;
        for (int j = 0; j < n ;j++)
        {   
            int t;
            fIn >> t;
            if (t != 0)
            {
                cnt++;
                save.push_back(j);
            }
        }
        ListInLine.push_back(cnt);
        for (int t : save)
        {
            ListInLine.push_back(t);
        }
        List.push_back(ListInLine);
    }
    fIn.close();    
    return List;
}

vector<vector<int>> convertListToMatrix(const string& filename)
{   
    ifstream fIn(filename);
    vector<vector<int>> Matrix;
    if (!fIn.is_open())
    {
        cout << "Cannot open inputfie" << endl;
    }
    int n;
    fIn >> n;
    vector<int> num = { 9 };
    Matrix.push_back(num);
    for (int i = 0; i < n ;i++)
    {
        vector<int> LineInMatrix;
        vector<int> temp;
        int numInLine; fIn >> numInLine;
        while (numInLine > 0)
        {
            numInLine--;
            int t; fIn >> t;
            temp.push_back(t);
        }
        int z = 0;
        for (int j = 0; j < n ;j++)
        {
            if (!temp.empty() && j == temp[z])
            {   
                LineInMatrix.push_back(1);
                z++;
            }
            else
            {
                LineInMatrix.push_back(0);
            }
        }
        Matrix.push_back(LineInMatrix);
    }
    fIn.close();
    return Matrix;
}

bool isDirected(const vector<vector<int>> adjMatrix)
{   
    int n = adjMatrix.size();  
    for (int i = 0 ; i < n ;i++)
    {   
        int n1 = adjMatrix[i].size();
        for (int j = 0; j < n1 ;j++)
        {
            if (adjMatrix[i][j] != adjMatrix[j][i])
            {
                return true;
            }
        }
    }
    return false;
}

int countVertices(const vector<vector<int>>& adjMatrix)
{
    return adjMatrix.size();
}

int countEdges(const vector<vector<int>>& adjMatrix)
{
    int cnt = 0;
    int n = adjMatrix.size();
    for (int i = 0 ; i < n ;i++)
    {   
        int n1 = adjMatrix[i].size();
        for (int j = 0; j < n1 ;j++)
        {   
            if (adjMatrix[i][j] == 1)
                cnt++;
        }
    }
    return cnt;
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix)
{
    vector<int> result;
    int n = adjMatrix.size();
    for (int i = 0 ; i < n ;i++)
    {   
        int n1 = adjMatrix[i].size();
        bool check = false;
        for (int j = 0; j < n1 ;j++)
        {
            if (adjMatrix[i][j] == 1 || adjMatrix[j][i] == 1)
            {
                check = true;
            }
        }
        if (check == false)
        {
            result.push_back(i);
        }
    }
    return result;
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();  
    for (int i = 0 ; i < n ;i++)
    {   
        int n1 = adjMatrix[i].size();
        for (int j = 0; j < n1 ;j++)
        {   
            if (i == j) continue;
            if (adjMatrix[i][j] != 1)
            {
                return false;
            }
            if (adjMatrix[i][j] != adjMatrix[j][i])
            {
                return false;
            }
        }
    }
    return true;
}

bool isBipartite(const std::vector<std::vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();  
    vector<int> temp1, temp2;
    for (int i = 0 ; i < n ;i++)
    {   
        int n1 = adjMatrix[i].size();
        for (int j = 0; j < n1 ;j++)
        {   
            if (adjMatrix[i][j] == 1)
            {
                if (temp1.empty() && temp2.empty())
                {
                    temp1.push_back(i);
                    temp2.push_back(j);
                }
                else
                {   
                    bool check1 = false;
                    bool check2 = false;
                    for (int t1 = 0; t1 < temp1.size() ;t1++)
                    {
                        if (i == temp1[t1])
                        {
                            check1 = true;
                        }
                        if (j == temp1[t1])
                        {
                            check2 = true;
                        }
                    }
                    bool check3 = false;
                    bool check4 = false;
                    for (int t2 = 0; t2 < temp2.size() ;t2++)
                    {
                        if (i == temp2[t2])
                        {
                            check3 = true;
                        }
                        if (j == temp2[t2])
                        {
                            check4 = true;
                        }
                    }
                    if ((check1 == true && check2 == true) || (check3 == true && check4 == true))
                    {
                        return false;
                    }
                    else if (check1 == false && check2 == false && check3 == false && check4 == false)
                    {
                        temp1.push_back(i);
                        temp2.push_back(j);
                    }
                    else if (check1 == true || check2 == true)
                    {   
                        if (check1 == true)
                            temp2.push_back(j);
                        else
                            temp2.push_back(i);
                    }
                    else if (check3 == true || check4 == true)
                    {
                        if (check3 == true)
                            temp1.push_back(j);
                        else
                            temp1.push_back(i);
                    }
                }
            }
        }
    }
    return true;
}

bool isCompleteBipartite(const std::vector<std::vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();  
    vector<int> temp1, temp2;
    for (int i = 0 ; i < n ;i++)
    {   
        int n1 = adjMatrix[i].size();
        for (int j = 0; j < n1 ;j++)
        {   
            if (adjMatrix[i][j] == 1)
            {
                if (temp1.empty() && temp2.empty())
                {
                    temp1.push_back(i);
                    temp2.push_back(j);
                }
                else
                {   
                    bool check1 = false;
                    bool check2 = false;
                    for (int t1 = 0; t1 < temp1.size() ;t1++)
                    {
                        if (i == temp1[t1])
                        {
                            check1 = true;
                        }
                        if (j == temp1[t1])
                        {
                            check2 = true;
                        }
                    }
                    bool check3 = false;
                    bool check4 = false;
                    for (int t2 = 0; t2 < temp2.size() ;t2++)
                    {
                        if (i == temp2[t2])
                        {
                            check3 = true;
                        }
                        if (j == temp2[t2])
                        {
                            check4 = true;
                        }
                    }
                    if ((check1 == true && check2 == true) || (check3 == true && check4 == true))
                    {
                        return false;
                    }
                    else if (check1 == false && check2 == false && check3 == false && check4 == false)
                    {
                        temp1.push_back(i);
                        temp2.push_back(j);
                    }
                    else if (check1 == true || check2 == true)
                    {   
                        if (check1 == true)
                            temp2.push_back(j);
                        else
                            temp2.push_back(i);
                    }
                    else if (check3 == true || check4 == true)
                    {
                        if (check3 == true)
                            temp1.push_back(j);
                        else
                            temp1.push_back(i);
                    }
                }
            }
        }
    }
    for (int i = 0; i < temp1.size() ;i++)
    {
        for (int j = 0; j < temp2.size() ;j++)
        {
            if (adjMatrix[temp1[i]][temp2[j]] == 0)
            {
                return false;
            }
        }
    }
    for (int i = 0; i < temp2.size() ;i++)
    {
        for (int j = 0; j < temp1.size() ;j++)
        {
            if (adjMatrix[temp2[i]][temp1[j]] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    vector<vector<int>> result(n, vector<int>(n, 0));
    for (int i = 0; i < n ;i++)
    {
        for (int j = 0; j < n ;j++)
        {
            if (adjMatrix[i][j] == 1 || adjMatrix[j][i] == 0)
            {
                result[i][j] = 1;
                result[j][i] = 1;
            }
        }
    }
    return result;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix)
{   
    int n = adjMatrix.size();
    vector<vector<int>> result(n, vector<int>(n,0));
    for (int i = 0; i < n ;i++)
    {
        for (int j = 0; j < n ;j++)
        {
            if (i == j) continue;
            if (adjMatrix[i][j] == 0)
            {
                result[i][j] = 1;
            }
        }
    }
    return result;
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    bool IsDirected = isDirected(adjMatrix);
    vector<vector<int>> graph = adjMatrix;
    vector<int> inDegree(n, 0) ,outDegree(n, 0);
    for (int i = 0; i < n ; i++)
    {
        for (int j = 0; j < n ;j++)
        {
            outDegree[i] += graph[i][j];
            if (IsDirected)
            {
                inDegree[j] += graph[i][j];
            }
            else
            {
                inDegree[i] += graph[i][j];
            }
        }
    }

    for (int i = 0; i < n ;i++)
    {
        if (IsDirected)
        {
            if (inDegree[i] != outDegree[i])
                return {};
        }
        else
        {
            if (inDegree[i] % 2 != 0)
                return {};
        }
    }

    int start = 0;
    while (start < n && outDegree[start] == 0)
        start++;
    if (start == n) return {};

    stack<int> s;
    vector<int> result;
    s.push(start);
    while (!s.empty())
    {
        int temp = s.top();
        bool check = false;
        for (int j = 0; j < n ;j++)
        {
            if (graph[temp][j] > 0)
            {
                s.push(j);
                graph[temp][j]--;
                if (!IsDirected)
                {
                    graph[j][temp]--;
                }
                check = true;
                break;
            }
        }
        if (check == false)
        {
            result.push_back(temp);
            s.pop();
        }
    }
    reverse(result.begin(),result.end());
    return result;
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix,int start)
{
    int n = adjMatrix.size();
    vector<vector<int>> spanningTree(n , vector<int>(n , 0));
    vector<int> visited(n ,0);
    stack<int> s;
    s.push(start);
    visited[start] = 1;
    while (!s.empty())
    {
        int temp = s.top();
        s.pop();
        for (int j = 0; j < n ;j++)
        {
            if (adjMatrix[temp][j] == 1 && visited[j] == 0)
            {   
                spanningTree[temp][j] = 1;
                spanningTree[j][temp] = 1;
                visited[j] = 1;
                s.push(j);
            }
        }
    } 
    return spanningTree; 
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start)
{
    int n = adjMatrix.size();
    vector<vector<int>> spanningTree(n , vector<int>(n));
    vector<int> visited(n, 0);
    queue<int> q;
    q.push(start);
    visited[start] = 1;
    while (!q.empty())
    {
        int temp = q.front();
        q.pop();
        for (int i = 0; i < n ;i++)
        {
            if (adjMatrix[temp][i] == 1 && visited[i] == 0)
            {
                spanningTree[temp][i] = 1;
                spanningTree[i][temp] = 1;
                visited[i] = 1;
                q.push(i);
            }
        }
    }
    return spanningTree;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix)
{
    return adjMatrix[u][v] || adjMatrix[v][u];
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    vector<int> dVertices(n ,INF);
    vector<int> pre(n , -1);
    vector<bool> visited(n, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> p_q;
    p_q.push({0,start});
    dVertices[start] = 0; 
    while (!p_q.empty())
    {
        int i = p_q.top().second;
        p_q.pop();
        if (visited[i] == false)
        {
            visited[i] = true;
            for (int j = 0 ; j < n ;j++)
            {
                int w = adjMatrix[i][j];
                if (w > 0 && dVertices[i] + w < dVertices[j])
                {
                    dVertices[j] = dVertices[i] + w;
                    pre[j] = i;
                    p_q.push({dVertices[j],j});
                }
            }
        }
    }
    if (dVertices[end] == INF) return {};
    vector<int> shortestPath;
    shortestPath.push_back(end);
    int temp = end;
    while (pre[temp] != -1)
    {
        shortestPath.push_back(pre[temp]);
        temp = pre[temp];
    }
    reverse(shortestPath.begin(), shortestPath.end());
    return shortestPath;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix)
{
    vector<pair<int,int>> list;
    int n = adjMatrix.size();
    vector<int> dVertices(n, INF);
    vector<int> pre(n , -1);
    dVertices[start] = 0;
    for (int k = 0 ; k < n - 1 ;k++)
    {
        for (int i = 0; i < n ;i++)
        {
            for (int j = 0; j < n ;j++)
            {
                if (adjMatrix[i][j] != 0 && dVertices[i] != INF && dVertices[i] + adjMatrix[i][j] < dVertices[j])
                {
                    dVertices[j] = dVertices[i] + adjMatrix[i][j];
                    pre[j] = i;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w = adjMatrix[i][j];
            if (w != 0 && dVertices[i] != INF && dVertices[i] + w < dVertices[j]) {
                cout << "Đồ thị chứa chu trình âm" << endl;
                return {};
            }
        }
    }
    
    if (dVertices[end] == INF) return {};
    vector<int> shortestPath;
    shortestPath.push_back(end);
    int temp = end;
    while (pre[temp] != -1)
    {
        shortestPath.push_back(pre[temp]);
        temp = pre[temp];
    }
    reverse(shortestPath.begin(), shortestPath.end());
    return shortestPath;
}