#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stack>
using namespace std;


class TopologicalSortDFS {
private:
    int n;
    bool computed;
    bool hasCycle;

    vector<bool> visited;                   // 记录顶点是否被访问
    vector<bool> finished;                  // 表示顶点 u 的后续依赖是否处理完
    stack<int> stk;                         // 存放后序遍历的顶点
    vector<int> sequence;                   // 拓扑序列    

public:
    TopologicalSortDFS(int n) : n(n) {
        this->computed = false;
        this->hasCycle = false;
        visited.resize(n);
        finished.resize(n);
    }

private:
    // 后序DFS 
    void dfs(int u, const unordered_map<int , vector<int>>& grid) {
        // 处理掉顶点 u 以及其后续顶点的所有依赖关系, 得到一个序列
        visited[u] = true;              // 设置顶点 u 已访问, 此后不会再访问顶点u, visited[u] 不用回溯
        finished[u] = false;            // 设置顶点 u 在递归栈里, 表示顶点 u 的后续依赖还没处理完 

        auto it = grid.find(u);
        if (it == grid.end()) {
            // 后序, 所有依赖顶点处理完后, 当前顶点 u 入栈
            stk.push(u);
            // 退出递归栈
            finished[u] = true;
            return;
        }
        // 获取与顶点 u 相连的顶点集合
        vector<int> vertices = it->second;
        for (int v: vertices) {
            if (!visited[v]) {
                // dfs()过程中涉及修改 hasCycle 的代码
                dfs(v, grid);
                // 每进行一次dfs(), 都可以检查 hasCycle
                if (hasCycle) return;
            }
            else if (!finished[v]) {
                // 如果遍历到了递归栈中的顶点, 就说明存在环
                hasCycle = true;
                return;
            }
        }
        
        finished[u] = true;     // 顶点 u 已经处理完了 
        stk.push(u);            // 把顶点 u 加入到结果栈里
    }

    void topologicalSort(const unordered_map<int, vector<int>>& grid) {
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                // dfs()过程中涉及修改 hasCycle 的代码
                dfs(i, grid);
                // 每进行一次dfs(), 都可以检查 hasCycle
                if (hasCycle) {
                    computed = true;
                    return;
                }
            }
        }

        while (!stk.empty()) {
            sequence.push_back(stk.top());
            stk.pop();
        }

        computed = true;
        hasCycle = false;
    }

public: 
    void printTopologicalSortSequence(const unordered_map<int, vector<int>>& grid) {
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
    /* DFS 算法进行拓扑排序 */
    
    int n, m;       // 顶点数 边数
    cin >> n >> m;  // 顶点编号从 0 开始
    unordered_map<int, vector<int>> grid;
    // 初始化所有顶点的邻接表, 避免访问未定义的键
    for (int i = 0; i < n; ++i) {
        grid[i] = vector<int>();
    }

    // 使用unique_ptr管理TopologicalSortKahn对象
    unique_ptr<TopologicalSortDFS> topoDFS = make_unique<TopologicalSortDFS>(n);

    while (m--) {
        int u, v;
        cin >> u >> v;
        grid[u].push_back(v);
    }

    topoDFS->printTopologicalSortSequence(grid);  // 执行排序并打印结果
    // 无需手动delete, unique_ptr出作用域自动释放内存 
    
    return 0;
}