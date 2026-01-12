# BFS（广度优先搜索）算法 - C++实现

## 概述

广度优先搜索（Breadth-First Search，BFS）是一种用于遍历或搜索树或图的算法。该算法从根节点开始，逐层遍历所有相邻节点，确保在进入下一层之前完全探索当前层的所有节点。

## 算法特性

### 时间复杂度

- **邻接表表示**：O(V + E)，其中V是顶点数，E是边数
- **邻接矩阵表示**：O(V²)

### 空间复杂度

- O(V)，主要用于队列存储

## 核心特点

- **逐层遍历**：先访问离起点最近的节点
- **最短路径**：在未加权图中能找到最短路径
- **队列结构**：使用FIFO队列实现

## 实现方式

### 1. 基础BFS实现

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <limits>
#include <functional>

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
  
    // 添加有向边
    void addDirectedEdge(int u, int v) {
        adj[u].push_back(v);
    }
  
    // 基础BFS实现
    void bfs(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
    
        visited[start] = true;
        q.push(start);
    
        cout << "BFS遍历顺序: ";
    
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";
        
            // 遍历所有邻居
            for (int neighbor : adj[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
  
    // 带层级的BFS（记录每个节点的层级）
    void bfsWithLevels(int start) {
        vector<bool> visited(V, false);
        vector<int> level(V, 0);
        queue<int> q;
    
        visited[start] = true;
        level[start] = 0;
        q.push(start);
    
        cout << "节点层级信息:\n";
        cout << "节点\t层级\n";
    
        while (!q.empty()) {
            int v = q.front();
            q.pop();
        
            cout << v << "\t" << level[v] << endl;
        
            for (int neighbor : adj[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    level[neighbor] = level[v] + 1;
                    q.push(neighbor);
                }
            }
        }
    }
  
    // 查找最短路径（未加权图）
    vector<int> shortestPath(int start, int end) {
        if (start == end) return {start};
    
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);
        queue<int> q;
    
        visited[start] = true;
        q.push(start);
    
        while (!q.empty()) {
            int v = q.front();
            q.pop();
        
            if (v == end) {
                break;
            }
        
            for (int neighbor : adj[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = v;
                    q.push(neighbor);
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
  
    // 计算从起点到所有节点的最短距离
    vector<int> shortestDistances(int start) {
        vector<int> distance(V, -1);
        queue<int> q;
    
        distance[start] = 0;
        q.push(start);
    
        while (!q.empty()) {
            int v = q.front();
            q.pop();
        
            for (int neighbor : adj[v]) {
                if (distance[neighbor] == -1) {
                    distance[neighbor] = distance[v] + 1;
                    q.push(neighbor);
                }
            }
        }
    
        return distance;
    }
  
    // 检查图是否连通
    bool isConnected() {
        if (V == 0) return true;
    
        vector<bool> visited(V, false);
        queue<int> q;
    
        visited[0] = true;
        q.push(0);
    
        while (!q.empty()) {
            int v = q.front();
            q.pop();
        
            for (int neighbor : adj[v]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    
        for (bool v : visited) {
            if (!v) return false;
        }
        return true;
    }
  
    // 寻找连通分量
    vector<vector<int>> connectedComponents() {
        vector<bool> visited(V, false);
        vector<vector<int>> components;
    
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                vector<int> component;
                queue<int> q;
            
                visited[i] = true;
                q.push(i);
            
                while (!q.empty()) {
                    int v = q.front();
                    q.pop();
                    component.push_back(v);
                
                    for (int neighbor : adj[v]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            
                components.push_back(component);
            }
        }
    
        return components;
    }
  
    // 检查图是否为二分图
    bool isBipartite() {
        vector<int> color(V, -1); // -1: 未染色, 0: 红色, 1: 蓝色
        queue<int> q;
    
        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                color[i] = 0;
                q.push(i);
            
                while (!q.empty()) {
                    int v = q.front();
                    q.pop();
                
                    for (int neighbor : adj[v]) {
                        if (color[neighbor] == -1) {
                            color[neighbor] = 1 - color[v];
                            q.push(neighbor);
                        } else if (color[neighbor] == color[v]) {
                            return false;
                        }
                    }
                }
            }
        }
    
        return true;
    }
  
    // 打印图
    void printGraph() {
        cout << "图的邻接表表示:\n";
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            for (int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};
```

### 2. 多源BFS（从多个起点同时开始）

```cpp
class MultiSourceBFS {
private:
    vector<vector<int>> grid;
    int rows, cols;
  
public:
    MultiSourceBFS(vector<vector<int>>& g) : grid(g) {
        rows = grid.size();
        cols = grid[0].size();
    }
  
    // 计算每个位置到最近起点的距离
    vector<vector<int>> multiSourceBFS(vector<pair<int, int>>& sources) {
        vector<vector<int>> distance(rows, vector<int>(cols, -1));
        queue<pair<int, int>> q;
    
        // 将所有起点加入队列
        for (auto& source : sources) {
            int x = source.first;
            int y = source.second;
            distance[x][y] = 0;
            q.push({x, y});
        }
    
        // 方向数组：上、右、下、左
        int dx[4] = {-1, 0, 1, 0};
        int dy[4] = {0, 1, 0, -1};
    
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
        
            for (int i = 0; i < 4; i++) {
                int newX = x + dx[i];
                int newY = y + dy[i];
            
                if (isValid(newX, newY) && distance[newX][newY] == -1) {
                    distance[newX][newY] = distance[x][y] + 1;
                    q.push({newX, newY});
                }
            }
        }
    
        return distance;
    }
  
private:
    bool isValid(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] != -1;
    }
};
```

### 3. 0-1 BFS（适用于边权为0或1的图）

```cpp
class ZeroOneBFS {
private:
    vector<vector<pair<int, int>>> adj; // 邻接表，pair<邻居, 权重>
    int V;
  
public:
    ZeroOneBFS(int vertices) : V(vertices) {
        adj.resize(V);
    }
  
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // 无向图
    }
  
    // 0-1 BFS算法
    vector<int> zeroOneBFS(int start) {
        vector<int> distance(V, INT_MAX);
        deque<int> dq;
    
        distance[start] = 0;
        dq.push_front(start);
    
        while (!dq.empty()) {
            int v = dq.front();
            dq.pop_front();
        
            for (auto& [neighbor, weight] : adj[v]) {
                if (distance[neighbor] > distance[v] + weight) {
                    distance[neighbor] = distance[v] + weight;
                
                    if (weight == 0) {
                        dq.push_front(neighbor);
                    } else {
                        dq.push_back(neighbor);
                    }
                }
            }
        }
    
        return distance;
    }
};
```

## 应用场景实现

### 1. 迷宫最短路径求解

```cpp
class MazeBFS {
private:
    vector<vector<char>> maze;
    int rows, cols;
  
    // 方向数组
    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, 1, 0, -1};
  
public:
    MazeBFS(vector<vector<char>> m) : maze(m) {
        rows = maze.size();
        cols = maze[0].size();
    }
  
    // 寻找最短路径
    vector<pair<int, int>> findShortestPath(pair<int, int> start, pair<int, int> end) {
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
        queue<pair<int, int>> q;
    
        visited[start.first][start.second] = true;
        q.push(start);
    
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
        
            // 到达终点
            if (x == end.first && y == end.second) {
                break;
            }
        
            for (int i = 0; i < 4; i++) {
                int newX = x + dx[i];
                int newY = y + dy[i];
            
                if (isValid(newX, newY) && !visited[newX][newY]) {
                    visited[newX][newY] = true;
                    parent[newX][newY] = {x, y};
                    q.push({newX, newY});
                }
            }
        }
    
        // 重构路径
        vector<pair<int, int>> path;
        if (visited[end.first][end.second]) {
            pair<int, int> current = end;
            while (current != make_pair(-1, -1)) {
                path.push_back(current);
                current = parent[current.first][current.second];
            }
            reverse(path.begin(), path.end());
        }
    
        return path;
    }
  
    // 计算从起点到所有位置的最短距离
    vector<vector<int>> computeAllDistances(pair<int, int> start) {
        vector<vector<int>> distance(rows, vector<int>(cols, -1));
        queue<pair<int, int>> q;
    
        distance[start.first][start.second] = 0;
        q.push(start);
    
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
        
            for (int i = 0; i < 4; i++) {
                int newX = x + dx[i];
                int newY = y + dy[i];
            
                if (isValid(newX, newY) && distance[newX][newY] == -1) {
                    distance[newX][newY] = distance[x][y] + 1;
                    q.push({newX, newY});
                }
            }
        }
    
        return distance;
    }
  
private:
    bool isValid(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] != '#';
    }
};
```

### 2. 单词接龙问题

```cpp
class WordLadder {
public:
    // 寻找单词接龙的最短转换序列
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
    
        if (wordSet.find(endWord) == wordSet.end()) {
            return 0;
        }
    
        queue<string> q;
        q.push(beginWord);
        int level = 1;
    
        while (!q.empty()) {
            int size = q.size();
        
            for (int i = 0; i < size; i++) {
                string current = q.front();
                q.pop();
            
                if (current == endWord) {
                    return level;
                }
            
                // 生成所有可能的变换
                for (int j = 0; j < current.length(); j++) {
                    char original = current[j];
                
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == original) continue;
                    
                        current[j] = c;
                        if (wordSet.find(current) != wordSet.end()) {
                            q.push(current);
                            wordSet.erase(current); // 避免重复访问
                        }
                    }
                
                    current[j] = original;
                }
            }
        
            level++;
        }
    
        return 0;
    }
};
```

### 3. 腐烂的橘子问题

```cpp
class RottingOranges {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
    
        queue<pair<int, int>> q;
        int freshCount = 0;
    
        // 初始化队列，统计新鲜橘子数量
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                } else if (grid[i][j] == 1) {
                    freshCount++;
                }
            }
        }
    
        if (freshCount == 0) return 0;
    
        int minutes = 0;
        int dx[4] = {-1, 0, 1, 0};
        int dy[4] = {0, 1, 0, -1};
    
        while (!q.empty()) {
            int size = q.size();
            bool infected = false;
        
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();
            
                for (int j = 0; j < 4; j++) {
                    int newX = x + dx[j];
                    int newY = y + dy[j];
                
                    if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && 
                        grid[newX][newY] == 1) {
                        grid[newX][newY] = 2;
                        q.push({newX, newY});
                        freshCount--;
                        infected = true;
                    }
                }
            }
        
            if (infected) {
                minutes++;
            }
        }
    
        return freshCount == 0 ? minutes : -1;
    }
};
```

## 测试用例

```cpp
void testBFS() {
    cout << "========== 测试用例1：基本BFS ==========" << endl;
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(4, 5);
  
    g.printGraph();
    cout << endl;
  
    g.bfs(0);
    cout << endl;
  
    g.bfsWithLevels(0);
    cout << endl;
  
    cout << "========== 测试用例2：最短路径 ==========" << endl;
    vector<int> path = g.shortestPath(0, 5);
    cout << "从0到5的最短路径: ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;
  
    vector<int> distances = g.shortestDistances(0);
    cout << "从0到所有节点的距离:\n";
    for (int i = 0; i < distances.size(); i++) {
        cout << "到节点" << i << "的距离: " << distances[i] << endl;
    }
  
    cout << "\n========== 测试用例3：连通性检查 ==========" << endl;
    cout << "图是否连通: " << (g.isConnected() ? "是" : "否") << endl;
  
    cout << "\n========== 测试用例4：二分图检测 ==========" << endl;
    cout << "图是否为二分图: " << (g.isBipartite() ? "是" : "否") << endl;
  
    cout << "\n========== 测试用例5：连通分量 ==========" << endl;
    Graph g2(7);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(1, 2);
    g2.addEdge(3, 4);
    g2.addEdge(5, 6);
  
    auto components = g2.connectedComponents();
    cout << "连通分量数量: " << components.size() << endl;
    for (int i = 0; i < components.size(); i++) {
        cout << "分量" << i + 1 << ": ";
        for (int node : components[i]) {
            cout << node << " ";
        }
        cout << endl;
    }
  
    cout << "\n========== 测试用例6：迷宫求解 ==========" << endl;
    vector<vector<char>> maze = {
        {'S', '.', '.', '.', '#'},
        {'#', '#', '.', '#', '.'},
        {'.', '.', '.', '.', '.'},
        {'.', '#', '#', '#', '.'},
        {'.', '.', '.', '.', 'E'}
    };
  
    MazeBFS mazeSolver(maze);
    auto mazePath = mazeSolver.findShortestPath({0, 0}, {4, 4});
  
    cout << "最短路径长度: " << mazePath.size() << endl;
    cout << "路径: ";
    for (auto& [x, y] : mazePath) {
        cout << "(" << x << "," << y << ") ";
    }
    cout << endl;
  
    cout << "\n========== 测试用例7：0-1 BFS ==========" << endl;
    ZeroOneBFS zoBFS(5);
    zoBFS.addEdge(0, 1, 0);
    zoBFS.addEdge(0, 2, 1);
    zoBFS.addEdge(1, 2, 1);
    zoBFS.addEdge(1, 3, 0);
    zoBFS.addEdge(2, 4, 0);
    zoBFS.addEdge(3, 4, 1);
  
    vector<int> zoDistances = zoBFS.zeroOneBFS(0);
    cout << "从节点0到所有节点的最短距离:\n";
    for (int i = 0; i < zoDistances.size(); i++) {
        cout << "到节点" << i << "的距离: " << zoDistances[i] << endl;
    }
}

int main() {
    testBFS();
    return 0;
}
```

## 编译与运行

### 编译命令（使用g++）

```bash
g++ -std=c++17 bfs_algorithm.cpp -o bfs
./bfs
```

### 编译选项说明

- `-std=c++17`：使用C++17标准
- `-O2`：优化级别（可选）
- `-Wall`：显示所有警告（推荐）

## 性能优化技巧

### 1. 内存优化

```cpp
// 使用vector<bool>替代vector<int>存储访问状态
vector<bool> visited(V, false);

// 使用静态数组替代vector（当V较小时）
bool visited[MAX_V] = {false};
```

### 2. 队列优化

```cpp
// 使用deque实现双端队列
#include <deque>
deque<int> dq;

// 预先分配队列空间
queue<int> q;
q.reserve(V); // 虽然不是标准queue的方法，但可自己实现
```

### 3. 使用位运算压缩状态

```cpp
// 对于状态空间较小的情况
bitset<MAX_V> visited;
visited.set(start);
```

## BFS与DFS比较

| 特性       | BFS                | DFS              |
| ---------- | ------------------ | ---------------- |
| 数据结构   | 队列               | 栈               |
| 遍历顺序   | 层级遍历           | 深度优先         |
| 空间复杂度 | O(V)               | O(V)             |
| 最短路径   | 保证（未加权图）   | 不保证           |
| 适用场景   | 最短路径、层级分析 | 拓扑排序、环检测 |

## 常见问题解答

### Q1: BFS为什么能找到最短路径？

BFS按层级遍历，当第一次访问到目标节点时，经过的层级数就是最短路径长度。

### Q2: BFS能否处理加权图？

标准BFS不能直接处理加权图，但可以使用变体如0-1 BFS（边权为0或1）或Dijkstra算法。

### Q3: 如何记录BFS的路径？

使用parent数组记录每个节点的前驱节点，然后从终点回溯到起点。

### Q4: BFS的时间复杂度是多少？

对于邻接表：O(V + E)，对于邻接矩阵：O(V²)。

## 扩展应用

### 1. 社交网络分析

- 查找两人之间的最短连接路径
- 计算关系的度数

### 2. 网络爬虫

- 按层级抓取网页
- 控制爬取深度

### 3. 游戏AI

- 寻找最短路径（如迷宫、棋类游戏）
- 状态空间搜索

### 4. 图像处理

- 区域填充（洪水填充算法）
- 连通区域标记

## 进阶话题

### 1. 双向BFS

从起点和终点同时开始BFS，当两个搜索相遇时结束。

### 2. A*算法

结合BFS和启发式函数，用于路径规划。

### 3. 并行BFS

使用多线程或GPU加速BFS计算。

## 参考资源

1. **《算法导论》** - Thomas H. Cormen
2. **《算法》** - Robert Sedgewick
3. **LeetCode BFS相关题目**：
   - 127. 单词接龙
   - 200. 岛屿数量
   - 994. 腐烂的橘子
   - 433. 最小基因变化
