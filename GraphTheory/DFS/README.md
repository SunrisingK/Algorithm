# DFS（深度优先搜索）算法 - C++实现

## 概述

深度优先搜索（Depth-First Search，DFS）是一种用于遍历或搜索树或图的算法。该算法会尽可能深地探索分支，当节点v的所有边都已被探寻过，搜索将回溯到发现节点v的那条边的起始节点。

## 算法特性

### 时间复杂度

- **邻接表表示**：O(V + E)，其中V是顶点数，E是边数
- **邻接矩阵表示**：O(V²)

### 空间复杂度

- O(V)，主要用于递归栈或显式栈

## 实现方式

### 1. 递归实现（推荐用于简单场景）

```cpp
#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <queue>

using namespace std;

class Graph {
private:
    int V; // 顶点数
    vector<vector<int>> adj; // 邻接表
  
public:
    // 构造函数
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }
  
    // 添加边（无向图）
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // 对于有向图，删除此行
    }
  
    // 递归DFS实现
    void DFSRecursive(int start) {
        vector<bool> visited(V, false);
        cout << "递归DFS遍历顺序: ";
        DFSUtil(start, visited);
        cout << endl;
    }
  
    // 递归辅助函数
    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";
  
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }
  
    // 迭代DFS实现（使用栈）
    void DFSIterative(int start) {
        vector<bool> visited(V, false);
        stack<int> s;
  
        s.push(start);
  
        cout << "迭代DFS遍历顺序: ";
  
        while (!s.empty()) {
            int v = s.top();
            s.pop();
      
            if (!visited[v]) {
                visited[v] = true;
                cout << v << " ";
          
                // 逆序压入栈，以保持与递归相同的遍历顺序
                for (auto it = adj[v].rbegin(); it != adj[v].rend(); ++it) {
                    if (!visited[*it]) {
                        s.push(*it);
                    }
                }
            }
        }
        cout << endl;
    }
  
    // 查找从起点到终点的路径
    vector<int> findPath(int start, int end) {
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);
        stack<int> s;
  
        s.push(start);
        visited[start] = true;
  
        while (!s.empty()) {
            int v = s.top();
            s.pop();
      
            if (v == end) {
                break;
            }
      
            for (int neighbor : adj[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = v;
                    s.push(neighbor);
                }
            }
        }
  
        // 重构路径
        vector<int> path;
        if (visited[end]) {
            for (int v = end; v != -1; v = parent[v]) {
                path.push_back(v);
            }
            reverse(path.begin(), path.end());
        }
  
        return path;
    }
  
    // 检测图中是否有环（无向图版本）
    bool hasCycle() {
        vector<bool> visited(V, false);
  
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (hasCycleUtil(i, visited, -1)) {
                    return true;
                }
            }
        }
        return false;
    }
  
    // 环检测辅助函数
    bool hasCycleUtil(int v, vector<bool>& visited, int parent) {
        visited[v] = true;
  
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                if (hasCycleUtil(neighbor, visited, v)) {
                    return true;
                }
            } else if (neighbor != parent) {
                return true;
            }
        }
  
        return false;
    }
  
    // 计算连通分量数量
    int connectedComponents() {
        vector<bool> visited(V, false);
        int count = 0;
  
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                count++;
                DFSUtil(i, visited);
            }
        }
  
        return count;
    }
  
    // 拓扑排序（仅适用于有向无环图）
    vector<int> topologicalSort() {
        vector<int> result;
        vector<bool> visited(V, false);
        stack<int> s;
  
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, s);
            }
        }
  
        while (!s.empty()) {
            result.push_back(s.top());
            s.pop();
        }
  
        return result;
    }
  
    // 拓扑排序辅助函数
    void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& s) {
        visited[v] = true;
  
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                topologicalSortUtil(neighbor, visited, s);
            }
        }
  
        s.push(v);
    }
};
```

### 2. 使用示例

```cpp
// 测试主函数
int main() {
    // 创建图
    Graph g(6);
  
    // 添加边
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(4, 5);
  
    cout << "========== DFS算法演示 ==========" << endl;
  
    // 递归DFS
    g.DFSRecursive(0);
  
    // 迭代DFS
    g.DFSIterative(0);
  
    // 查找路径
    vector<int> path = g.findPath(0, 5);
    if (!path.empty()) {
        cout << "从0到5的路径: ";
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "路径不存在" << endl;
    }
  
    // 检测环
    if (g.hasCycle()) {
        cout << "图中存在环" << endl;
    } else {
        cout << "图中不存在环" << endl;
    }
  
    // 计算连通分量
    int components = g.connectedComponents();
    cout << "连通分量数量: " << components << endl;
  
    return 0;
}
```

## 应用场景实现

### 1. 迷宫求解

```cpp
class MazeSolver {
private:
    vector<vector<char>> maze;
    vector<vector<bool>> visited;
    int rows, cols;
    vector<pair<int, int>> path;
  
    // 方向数组：上、右、下、左
    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, 1, 0, -1};
  
public:
    MazeSolver(vector<vector<char>> m) : maze(m) {
        rows = maze.size();
        cols = maze[0].size();
        visited.resize(rows, vector<bool>(cols, false));
    }
  
    // DFS解决迷宫问题
    bool solveMazeDFS(int x, int y, int endX, int endY) {
        // 检查边界和障碍物
        if (x < 0 || x >= rows || y < 0 || y >= cols || 
            maze[x][y] == '#' || visited[x][y]) {
            return false;
        }
  
        // 标记为已访问
        visited[x][y] = true;
        path.push_back({x, y});
  
        // 到达终点
        if (x == endX && y == endY) {
            return true;
        }
  
        // 向四个方向探索
        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];
      
            if (solveMazeDFS(newX, newY, endX, endY)) {
                return true;
            }
        }
  
        // 回溯
        path.pop_back();
        return false;
    }
  
    vector<pair<int, int>> getPath() {
        return path;
    }
};
```

### 2. 岛屿数量问题

```cpp
class IslandCounter {
private:
    vector<vector<int>> grid;
    int rows, cols;
  
public:
    IslandCounter(vector<vector<int>> g) : grid(g) {
        rows = grid.size();
        cols = grid[0].size();
    }
  
    // 计算岛屿数量
    int countIslands() {
        int count = 0;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
  
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    count++;
                    dfsIsland(i, j, visited);
                }
            }
        }
  
        return count;
    }
  
private:
    void dfsIsland(int x, int y, vector<vector<bool>>& visited) {
        if (x < 0 || x >= rows || y < 0 || y >= cols || 
            grid[x][y] == 0 || visited[x][y]) {
            return;
        }
  
        visited[x][y] = true;
  
        // 四个方向
        dfsIsland(x + 1, y, visited);
        dfsIsland(x - 1, y, visited);
        dfsIsland(x, y + 1, visited);
        dfsIsland(x, y - 1, visited);
  
        // 八个方向（包含对角线）
        // dfsIsland(x + 1, y + 1, visited);
        // dfsIsland(x + 1, y - 1, visited);
        // dfsIsland(x - 1, y + 1, visited);
        // dfsIsland(x - 1, y - 1, visited);
    }
};
```

## 高级实现

### 1. 带时间戳的DFS

```cpp
class TimestampDFS {
private:
    vector<vector<int>> adj;
    int V;
    vector<int> discoveryTime;
    vector<int> finishTime;
    int time;
  
public:
    TimestampDFS(int vertices) : V(vertices) {
        adj.resize(V);
        discoveryTime.resize(V, 0);
        finishTime.resize(V, 0);
        time = 0;
    }
  
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
  
    void execute() {
        vector<bool> visited(V, false);
  
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs(i, visited);
            }
        }
  
        printTimestamps();
    }
  
private:
    void dfs(int v, vector<bool>& visited) {
        visited[v] = true;
        discoveryTime[v] = ++time;
  
        cout << "发现节点 " << v << " 在时间 " << time << endl;
  
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited);
            }
        }
  
        finishTime[v] = ++time;
        cout << "完成节点 " << v << " 在时间 " << time << endl;
    }
  
    void printTimestamps() {
        cout << "\n节点时间戳:" << endl;
        cout << "节点\t发现时间\t完成时间" << endl;
        for (int i = 0; i < V; i++) {
            cout << i << "\t" << discoveryTime[i] << "\t\t" << finishTime[i] << endl;
        }
    }
};
```

### 2. 迭代加深深度优先搜索（IDDFS）

```cpp
class IDDFS {
private:
    vector<vector<int>> adj;
    int V;
  
public:
    IDDFS(int vertices) : V(vertices) {
        adj.resize(V);
    }
  
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
  
    // IDDFS主函数
    bool iddfs(int start, int target, int maxDepth) {
        for (int depth = 0; depth <= maxDepth; depth++) {
            vector<bool> visited(V, false);
            if (dls(start, target, depth, visited)) {
                cout << "在深度 " << depth << " 找到目标" << endl;
                return true;
            }
        }
        return false;
    }
  
private:
    // 深度受限搜索
    bool dls(int current, int target, int depth, vector<bool>& visited) {
        if (depth == 0 && current == target) {
            return true;
        }
  
        if (depth > 0) {
            visited[current] = true;
      
            for (int neighbor : adj[current]) {
                if (!visited[neighbor]) {
                    if (dls(neighbor, target, depth - 1, visited)) {
                        return true;
                    }
                }
            }
        }
  
        return false;
    }
};
```

## 测试用例

```cpp
// 测试函数
void testDFS() {
    cout << "========== 测试用例1：基本图 ==========" << endl;
    Graph g1(6);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 3);
    g1.addEdge(1, 4);
    g1.addEdge(2, 5);
    g1.addEdge(4, 5);
  
    g1.DFSRecursive(0);
    g1.DFSIterative(0);
  
    cout << "\n========== 测试用例2：岛屿数量 ==========" << endl;
    vector<vector<int>> grid = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1}
    };
  
    IslandCounter ic(grid);
    cout << "岛屿数量: " << ic.countIslands() << endl;
  
    cout << "\n========== 测试用例3：带时间戳的DFS ==========" << endl;
    TimestampDFS tdfs(6);
    tdfs.addEdge(0, 1);
    tdfs.addEdge(0, 2);
    tdfs.addEdge(1, 3);
    tdfs.addEdge(1, 4);
    tdfs.addEdge(2, 5);
    tdfs.addEdge(4, 5);
    tdfs.execute();
  
    cout << "\n========== 测试用例4：IDDFS ==========" << endl;
    IDDFS iddfs(7);
    iddfs.addEdge(0, 1);
    iddfs.addEdge(0, 2);
    iddfs.addEdge(1, 3);
    iddfs.addEdge(1, 4);
    iddfs.addEdge(2, 5);
    iddfs.addEdge(5, 6);
  
    bool found = iddfs.iddfs(0, 6, 4);
    if (found) {
        cout << "找到目标节点" << endl;
    } else {
        cout << "在指定深度内未找到目标节点" << endl;
    }
}

int main() {
    testDFS();
    return 0;
}
```
