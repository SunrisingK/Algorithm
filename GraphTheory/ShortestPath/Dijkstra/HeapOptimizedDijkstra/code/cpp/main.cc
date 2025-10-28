#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits>
using namespace std;

// 有向边数据结构
struct Edge {
    int out;    // 有向边的出点
    int val;    // 边的权重
};

// 实现自定义比较器类型
class mycompare {
public:
    // 重载函数调用运算符()
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
        return lhs.second > rhs.second;
    }
};

int heapDijkstra(int start, int end, vector<list<Edge>>& grid) {
    int n = grid.size() - 1;
    vector<int> minDist(1 + n, INT_MAX);
    vector<bool> visited(1 + n);
    // 堆优化版的Dijkstra算法仍然使用 minDist[] 数组和 visited[] 数组
    // 对比朴素Dijkstra算法, 区别在于堆优化版遍历的是边, 朴素版遍历的是顶点

    // 小顶堆中存放的是从起点到某个顶点点的当前已知最短距离
    priority_queue<pair<int, int>, vector<pair<int, int>>, mycompare> que;

    // 起点到起点作为初始状态, 作为初始边
    minDist[start] = 0;
    que.push({start, 0});
    while(!que.empty()) {
        // <顶点, 最短距离>
        pair<int, int> p = que.top();
        que.pop();

        // Dijkstra算法第 1 步: 选择一个未被访问过且到起点最近的顶点
        if (visited[p.first]) continue;

        // Dijkstra算法第 2 步: 把找到的顶点标记为已访问
        int cur = p.first;
        visited[cur] = true;

        // 如果当前节点就是终点，可以提前结束
        if (cur == end) break;

        // Dijkstra算法第 3 步: 更新起点到剩余未被访问过的顶点的距离, 只更新与 cur 相连的
        for (Edge& edge: grid[cur]) {
            int v = edge.out;
            if (!visited[v] && minDist[cur] + edge.val < minDist[v]) {
                minDist[v] = minDist[cur] + edge.val;
                que.push({v, minDist[v]});
            }
        }
    }
    return minDist[end] == INT_MAX ? -1: minDist[end];    
}

int main(int argc, char const* argv[]) {
    int n, m;   // 顶点数 边数
    cin >> n >> m;

    // C++中的 list 表示双向链表
    vector<list<Edge>> grid(1 + n);     // 邻接表存储图
    while (m--) {
        int a, b, val;
        cin >> a >> b >> val;
        // 有向边 a -> b, 权重为val
        grid[a].push_back({b, val});      // list操作 push_back() 在链表尾部插入元素
    }

    int start = 1;
    int end = n;
    cout << heapDijkstra(start, end, grid);

    return 0;
}