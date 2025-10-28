#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int naiveDijkstra(int n, int start, int end, vector<vector<int>>& grid) {
    // 默认起点为 1 号顶点
    vector<int> minDist(n + 1, INT_MAX);
    vector<bool> visited(n + 1);
    
    minDist[start] = 0;
    // 遍历所有顶点, 遍历 minDist[] 数组
    for (int i = 1; i <= n; ++i) {
        // Dijkstra算法第1步: 选择一个未被访问过且到起点最近的顶点
        int minVal = INT_MAX;
        int cur = -1;
        for (int v = 1; v <= n; ++v) {
            if (!visited[v] && minDist[v] < minVal) {
                cur = v;
                minVal = minDist[v];
            }
        }

        // 如果找不到可用的顶点，说明剩下的顶点都不可达
        if (cur == -1) break;

        // Dijkstra算法第 2 步: 把找到的顶点标记为已访问
        visited[cur] = true;

        // Dijkstra算法第3步: 更新起点到剩余未被访问过的顶点的距离
        for (int v = 1; v <= n; ++v) {
            if (!visited[v] && grid[cur][v] != INT_MAX && minDist[cur] + grid[cur][v] < minDist[v]) {
                minDist [v] = minDist[cur] + grid[cur][v];
            }
        }
    }
    
    return minDist[end] == INT_MAX ? -1 : minDist[end];
}

int main(int argc, char const* argv[]) {
    int n, m;       // 顶点数 边数
    cin >> n >> m;
    vector<vector<int>> grid(n + 1, vector<int>(n + 1, INT_MAX));
    while (m--) {
        int a, b, val;
        cin >> a >> b >> val;
        grid[a][b] = val;
    }
    
    int start = 1;  // 默认起点为 1 号顶点
    int end = n;    // 终点

    cout << naiveDijkstra(n, start, end, grid);
    
    return 0;
}