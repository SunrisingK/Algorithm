#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

/* 朴素 Dijkstra 算法拓展: 打印出最短路径 */

// 将朴素 Dijkstra 算法封装成一个类, 可以返回最短路径长度, 还有打印最短路径
class NaiveDijkstra {
private:
    int n;
    bool pathExists;
    bool computed;
    int lastStart;
    int lastEnd;
    vector<int> parent;         // 父顶点数组可以作为路径数组
    vector<int> minDist;
    vector<bool> visited;
    vector<vector<int>> grid;

public:
    NaiveDijkstra(vector<vector<int>> grid): grid(grid) {
        this->n = grid.size() - 1;
        this->pathExists = false;
    }

private:
    void shortestPath(int start, int end) {
        // 如果已经计算过相同的起点终点, 直接返回
        if (computed && lastStart == start && lastEnd == end) return;

        parent.resize(n + 1, -1);
        minDist.resize(n + 1, INT_MAX);
        visited.resize(n + 1);

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
            if (cur == -1) {
                pathExists = false;
                break;
            }

            // Dijkstra算法第 2 步: 把找到的顶点标记为已访问
            visited[cur] = true;

            // Dijkstra算法第3步: 更新起点到剩余未被访问过的顶点的距离
            for (int v = 1; v <= n; ++v) {
                if (!visited[v] && grid[cur][v] != INT_MAX && minDist[cur] + grid[cur][v] < minDist[v]) {
                    minDist [v] = minDist[cur] + grid[cur][v];
                    parent[v] = cur;
                }
            }
        }
        pathExists = minDist[end] != INT_MAX;
        computed = true;
        lastStart = start;
        lastEnd = end;
    }

    // 重构路径的辅助函数
    vector<int> reconstructPath(int start, int end) {
        vector<int> path;
        if (!pathExists) return path;
        
        // 从终点反向追踪到起点
        for (int v = end; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        
        // 反转路径
        reverse(path.begin(), path.end());
        
        // 检查路径是否完整（从起点开始）
        if (path.empty() || path[0] != start) {
            pathExists = false;
            return {};
        }
        
        return path;
    }

public:
    void printShortestPath(int start, int end) {
        shortestPath(start, end);
        if (pathExists) {
            cout << "起点" << start << "到终点" << end << "存在最短路径: ";
            vector<int> path = reconstructPath(start, end);
            for (size_t i = 0; i < path.size(); ++i) {
                if (i > 0) cout << " -> ";
                cout << path[i];
            }
            cout << "\n路径长度: " << minDist[end] << endl;
        }
        else {
            cout << "起点" << start << "到终点" << end << "不存在路径";
        }
    }

    // 获取最短路径长度
    int getShortestDistance(int start, int end) {
        shortestPath(start, end);
        return pathExists ? minDist[end] : -1;
    }

    // 额外的工具方法：只获取路径不打印
    vector<int> getShortestPath(int start, int end) {
        shortestPath(start, end);
        return reconstructPath(start, end);
    }

    // 检查路径是否存在
    bool hasPath(int start, int end) {
        shortestPath(start, end);
        return pathExists;
    }
};

int main(int argc, char const* argv[]) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n + 1, vector<int>(n + 1, INT_MAX));
    while (m--) {
        int a, b, val;
        cin >> a >> b >> val;
        // 有向边 a->b
        grid[a][b] = val;
    }

    int start = 1;  // 起点
    int end = n;    // 终点

    NaiveDijkstra* naiveDij = new NaiveDijkstra(grid);
    naiveDij->printShortestPath(start, end);

    delete naiveDij;

    return 0;
}