#include <iostream>
#include <vector>
#include <climits>
#include <string>
using namespace std;

struct Edge {
    int in, out;
    int val;
};

int naiveBellmanford(int start, int end, int n, vector<Edge>& grid) {
    vector<int> minDist(1 + n, INT_MAX);

    // BellmanFord算法里没有 visited[] 数组
    // 因为同一个点会被访问多次进行松弛操作, 而在Dijkstra算法里顶点最多被访问过一次

    // 朴素版BellmanFord算法: 进行n - 1 次松弛操作, 每次操作都要松弛可以到达的顶点作为入点的边 
    minDist[start] = 0;
    // 进行 n - 1 次松弛操作
    for (int i = 1; i < n; ++i) {
        // 每一次松弛操作都是对边的操作
        for (Edge& edge: grid) {
            int u = edge.in;
            int v = edge.out;
            int val = edge.val;

            // 每次只松弛计算过的边, 也就是说 minDist[u] != INT_MAX
            // minDist[u] != INT_MAX, 表示顶点 u 可以到达
            // 顶点 u 还是入点, 那么就可以松弛有向边<u, v>
            
            if (minDist[u] != INT_MAX && minDist[u] + val < minDist[v]) {
                minDist[v] = minDist[u] + val;
            }
        }
    }
    return minDist[end];
}

int main(int argc, char const* argv[]) {
    int n, m;
    cin >> n >> m;
    
    vector<Edge> grid;  // 仅存储有向带权边
    while (m--) {
        int a, b, val;
        cin >> a >> b >> val;
        // 有向边 <a, b> = val;
        grid.push_back({a, b, val});
    }

    int start = 1;
    int end = n; 

    int shortestDist = naiveBellmanford(start, end, n, grid);
    string s = (shortestDist == INT_MAX ? "unconnected" : to_string(shortestDist));
    cout << s;

    return 0;
} 