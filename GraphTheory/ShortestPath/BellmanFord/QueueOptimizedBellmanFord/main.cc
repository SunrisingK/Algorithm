#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int out;
    int val;
};

int queueOptimizedBellmanFord(int start, int end, vector<list<Edge>>& grid) {
    int n = grid.size() - 1;
    vector<int> minDist(1 + n, INT_MAX);
    vector<bool> isInQueue(1 + n);          // 记录是否在队列中

    minDist[start] = 0;
    queue<int> que;     // 存放计算过的顶点
    que.push(start);

    while (!que.empty()) {
        int vertex = que.front(); que.pop();
        // 顶点出队, isInQueue[vertex] = false; 不能忘记
        isInQueue[vertex] = false;

        // 出队的顶点 vertex 是计算过的, 松弛以 vertex 为入点的边
        for (Edge& edge: grid[vertex]) {
            int out = edge.out;
            int val = edge.val;
            if (minDist[vertex] + val < minDist[out]) {
                minDist[out] = minDist[vertex] + val;
                // out 已经计算过了, 如果不在队列中则需要入队
                // if () 条件判断可以避免重复入队
                if (!isInQueue[out]) {
                    que.push(out);
                    isInQueue[out] = true;
                }
            }
        }
    }

    return minDist[end];
}

int main(int argc, char const* argv[]) {
    int n, m;
    cin >> n >> m;

    vector<list<Edge>> grid(1 + n);     // 使用邻接表存储图, 邻接表得指定大小并初始化
    while (m--) {
        int a, b;
        int val;
        cin >> a >> b >> val;
        grid[a].push_back({b, val}); 
    }

    int start = 1;
    int end = n;

    int shortestDist = queueOptimizedBellmanFord(start, end, grid);
    string s = (shortestDist == INT_MAX ? "unconnected" : to_string(shortestDist));
    cout << s;

    return 0;
}