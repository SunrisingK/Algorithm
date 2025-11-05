#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <queue>
using namespace std;


class TopologicalSortKahn {
private:
    int n;
    bool hasCycle;          // 图中是否有环
    bool computed;
    queue<int> que;
    vector<int> sequence;   // 排序后的序列
public:
    vector<int> inDegree;

    TopologicalSortKahn(int n) : n(n) {
        inDegree.resize(n);
        this->hasCycle = false;
        this->computed = false;
    }
private:
    void topologicalSort(unordered_map<int, vector<int>>& grid) {
        // 多源BFS, 入度为 0 的顶点入队
        for (int i = 0; i < n; ++i) {
            if (inDegree[i] == 0) {
                que.push(i);
            }
        }

        while (!que.empty()) {
            int u = que.front(); que.pop();
            sequence.push_back(u);
            // 更新入度数组, 只更新与 u 相连的顶点
            vector<int> vertices = grid[u];
            for (int v: vertices) {
                --inDegree[v];
                // 一旦入度变成 0 就加入队列
                if (inDegree[v] == 0) {
                    que.push(v);
                }
            }
        }
        computed = true;
        hasCycle = (sequence.size() < n);
    }

public:
    void printTopologicalSortSequence(unordered_map<int, vector<int>>& grid) {
        if (!computed) topologicalSort(grid);

        if (hasCycle) {
            cout << "图中有环, 不存在拓扑序列" << endl;
        }
        else {
            for (int i = 0; i < sequence.size(); ++i) {
                if (i > 0) cout << " -> ";
                cout << sequence[i];
            }
            cout << endl;
        }
    }

};

int main(int argc, char const* argv[]) {
    /* Kahn算法基于 BFS 进行拓扑排序 */
    
    int n, m;       // 顶点数 边数
    cin >> n >> m;  // 顶点编号从 0 开始
    unordered_map<int, vector<int>> grid;
    // 初始化所有顶点的邻接表, 避免访问未定义的键
    for (int i = 0; i < n; ++i) {
        grid[i] = vector<int>();
    }

    // 使用unique_ptr管理TopologicalSortKahn对象
    unique_ptr<TopologicalSortKahn> kahn = make_unique<TopologicalSortKahn>(n);

    while (m--) {
        int u, v;
        cin >> u >> v;
        kahn->inDegree[v]++;  // 通过智能指针访问成员
        grid[u].push_back(v);
    }

    kahn->printTopologicalSortSequence(grid);  // 执行排序并打印结果
    // 无需手动delete, unique_ptr出作用域自动释放内存 
    
    return 0;
}