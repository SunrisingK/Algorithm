#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

/* 朴素 BellmanFord 算法拓展: 打印出最短路径 */

// 将朴素 BellmanFord 算法封装成一个类, 可以返回最短路径长度, 还有打印最短路径

class NaiveBellmanFord {
public:
    struct Edge {
        int in, out; 
        int val;
    };

private:
    int n;                  // 顶点数量
    bool pathExists;
    bool computed;
    
    vector<int> minDist;
    vector<int> parent;

    vector<Edge> grid;      // 存储带权有向边

    int lastStart;
    int lastEnd;

public:
    NaiveBellmanFord(int n, vector<Edge>& grid): n(n), grid(grid) {
        this->pathExists = false;
        this->computed = false;
    }

private:
    void shortestPath(int start, int end) {
        // 如果已经计算过相同的起点终点, 直接返回
        if (computed && lastStart == start && lastEnd == end) return;

        minDist.resize(1 + n, INT_MAX);
        parent.resize(1 + n, -1);

        // BellmanFord算法里没有 visited[] 数组
        // 因为同一个点会被访问多次进行松弛操作, 而在Dijkstra算法里顶点最多被访问过一次

        // 朴素版BellmanFord算法: 进行n - 1 次松弛操作, 每次操作都要松弛可以到达的顶点作为入点的边 

        minDist[start] = 0;
        // BellmanFord算法步骤: 每次松弛当前已经松弛过的边, 一共松弛 n - 1 次
        for (int i = 1; i < n; ++i) {
            for (Edge& edge: grid) {
                int u = edge.in;
                int v = edge.out;
                int val = edge.val;

                // 每次只松弛计算过的边, 也就是说 minDist[u] != INT_MAX
                // minDist[u] != INT_MAX, 表示顶点 u 可以到达
                // 顶点 u 还是入点, 那么就可以松弛有向边<u, v>

                if (minDist[u] != INT_MAX && minDist[u] + val < minDist[v]) {
                    minDist[v] = minDist[u] + val;
                    parent[v] = u;
                }
            }
        }
        pathExists = (minDist[end] != INT_MAX);
        lastStart = start;
        lastEnd = end;
        computed = true;
    }

    vector<int> reconstructPath(int start, int end) {
        vector<int> path;

        if (!pathExists) return path;

        for (int v = end; v != -1; v = parent[v]) {
            path.push_back(v);
        }

        // 反转路径
        reverse(path.begin(), path.end());

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
    vector<NaiveBellmanFord::Edge> grid;

    while (m--) {
        int in, out;
        int val;
        cin >> in >> out >> val;
        grid.push_back({in, out, val});
    }

    int start = 1;  // 起点
    int end = n;    // 终点

    NaiveBellmanFord* nBF = new NaiveBellmanFord(n, grid);
    nBF->printShortestPath(start, end);

    delete nBF;

    return 0;
}