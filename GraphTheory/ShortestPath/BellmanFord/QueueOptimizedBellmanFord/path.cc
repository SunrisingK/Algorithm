#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

/* 队列优化版 BellmanFord 算法拓展: 打印出最短路径 */

// 将队列优化版 BellmanFord 算法封装成一个类, 可以返回最短路径长度, 还有打印最短路径

class QueueOptimizedBellmanFord {
public:
    struct Edge {
        int out;
        int val;
    };

private:
    int n;
    int lastStart;
    int lastEnd;
    bool pathExists;
    bool computed;
    
    vector<int> minDist;
    vector<bool> isInQueue;
    queue<int> que;
    vector<int> parent;

    vector<list<Edge>> grid;

public:
    QueueOptimizedBellmanFord(vector<list<Edge>>& grid) : grid(grid) {
        this->n = grid.size() - 1;
        this->computed = false;
        this->pathExists = false;
    }

private:
    void shortestPath(int start, int end) {
        // 如果已经计算过相同的起点终点, 直接返回
        if (computed && lastStart == start && lastEnd == end) return;

        minDist.resize(1 + n, INT_MAX);
        parent.resize(1 + n, -1);
        isInQueue.resize(1 + n);    // 存放计算过的顶点

        minDist[start] = 0;
        que.push(start);

        while (!que.empty()) {
            int vertex = que.front(); que.pop();
            // 顶点出队, isInQueue[vertex] = false; 不能忘记
            isInQueue[vertex] = false;

            // 出队的顶点 vertex 是计算过的, 松弛以 vertex 为入点的边
            for (Edge& edge : grid[vertex]) {
                int out = edge.out;
                int val = edge.val;
                // out 已经计算过了, 如果不在队列中则需要入队
                // if () 条件判断可以避免重复入队
                if (minDist[vertex] + val < minDist[out]) {
                    minDist[out] = minDist[vertex] + val;
                    parent[out] = vertex;
                    if (!isInQueue[out]) {
                        que.push(out);
                        isInQueue[out] = true;
                    }
                }
            }
        }
        pathExists = (minDist[end] != INT_MAX);
        computed = true;
        lastStart = start;
        lastEnd = end;
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

    vector<list<QueueOptimizedBellmanFord::Edge>> grid(1 + n);
    while (m--) {
        int a, b, val;
        cin >> a >> b >> val;
        grid[a].push_back({b, val});
    }

    int start = 1;
    int end = n;

    QueueOptimizedBellmanFord* qBF = new QueueOptimizedBellmanFord(grid);
    qBF->printShortestPath(start, end);
    delete qBF;

    return 0;
}