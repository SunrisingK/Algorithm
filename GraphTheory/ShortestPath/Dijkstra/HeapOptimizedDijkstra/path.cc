#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

/* 堆优化 Dijkstra 算法拓展: 打印出最短路径 */

// 将堆优化 Dijkstra 算法封装成一个类, 可以返回最短路径长度, 还有打印最短路径
class HeapDijkstra {
public:
    struct Edge {
        int out;
        int val;    
    };
    
private:    
    class mycompare {
    public:
        bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
            return lhs.second > rhs.second;
        }
    };

private:
    int n;
    bool pathExists;
    bool computed;

    vector<int> minDist;
    vector<bool> visited;
    
    vector<int> parent;

    vector<list<Edge>> grid;

    priority_queue<pair<int, int>, vector<pair<int, int>>, mycompare> que;

    int lastStart;
    int lastEnd;

public:
    HeapDijkstra(vector<list<Edge>> grid): grid(grid) {
        this->n = grid.size() - 1;
        this->pathExists = false;
        this->computed = false;
    }

private:
    void shortestPath(int start, int end) {
        // 如果已经计算过相同的起点终点, 直接返回
        if (computed && lastStart == start && lastEnd == end) return;
        
        minDist.resize(1 + n, INT_MAX);
        visited.resize(1 + n);
        parent.resize(1 + n, -1);

        // 小顶堆中存放的是从起点到某个顶点点的当前已知最短距离
        // 起点到起点作为初始状态, 作为初始边
        minDist[start] = 0;
        que.push({start, 0});
        while (!que.empty()) {
            // <已知顶点, 最短距离>
            pair<int, int> p = que.top();
            que.pop();

            // Dijkstra算法第 1 步: 选择一个未被访问过且到起点最近的顶点
            int cur = p.first;
            if (visited[cur]) continue;

            // Dijkstra算法第 2 步: 把找到的顶点标记为已访问
            visited[cur] = true;

            // 如果当前节点就是终点，可以提前结束
            if (cur == end) break;

            // Dijkstra算法第 3 步: 更新起点到剩余未被访问过的顶点的距离, 只更新与 cur 相连的
            for (Edge& edge: grid[cur]) {
                int v = edge.out;
                if (!visited[v] && minDist[cur] + edge.val < minDist[v]) {
                    minDist[v] = minDist[cur] + edge.val;
                    que.push({v, minDist[v]});
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
        if (!pathExists) return {};

        // 从终点反向追踪到起点
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
    int n, m;           // 顶点数 边数
    cin >> n >> m;

    vector<list<HeapDijkstra::Edge>> grid(1 + n);
    while (m--) {
        int a, b, val;
        cin >> a >> b >> val;
        grid[a].push_back({b, val});
    }

    int start = 1;  // 起点
    int end = n;    // 终点

    HeapDijkstra* heapDij = new HeapDijkstra(grid);
    heapDij->printShortestPath(start, end);

    delete heapDij;

    return 0;
}