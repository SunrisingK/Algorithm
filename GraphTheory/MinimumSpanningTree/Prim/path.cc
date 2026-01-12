#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;


/* Prim算法拓展: 打印出最小生成树, 也就是说打印出MST的所有边 */

// 将Prim算法封装成一个类, 可以返回MST的权重和, 还有打印MST
// 为了使代码更加健壮, 增加判断是否生成了MST的代码
class PrimMST {
private:
    const int MAX_VAL;
    vector<bool> isInTree;
    vector<int> minDist;
    vector<vector<int>> grid;

    int v;                  // 顶点数
    int sum;                // MST的权重之和
    bool computed;          // 标记是否已计算MST
    bool mstExists;         // 标记是否能生成MST

    vector<int> parent;     // 父节点数组, parent[i] = j表示顶点i的父节点是顶点j

public:
    // 使用默认最大权重和一张邻接矩阵初始化PrimMST对象
    PrimMST(const int MAX_VAL, vector<vector<int>> grid): MAX_VAL(MAX_VAL) {
        v = grid.size() - 1;
        this->grid = grid;
        sum = 0;
        computed = false;
        mstExists = false;

        isInTree.resize(v + 1);
        minDist.resize(v + 1, MAX_VAL);
        parent.resize(v + 1, -1);       // 初始化为-1表示还没有找到父顶点
    }

private:
    // 用 BFS 检查图的连通性, 也可以统计MST中的节点数量
    bool isGraphConnected() {
        if (v <= 0) return false;

        vector<bool> visited(1 + v);
        queue<int> que;
        int count = 0;

        // 默认MST的根节点是1 
        int root = 1;
        que.push(root);
        visited[root] = true;

        while (!que.empty()) {
            int cur = que.front();
            que.pop();
            count++;
            // 将还没有访问过并且与cur相连的边入队
            for (int j = 1; j <= v; j++) {
                if (!visited[j] && grid[cur][j] < MAX_VAL) {
                    visited[j] = true;
                    que.push(j);
                }
            }
        }

        return count == v;
    }

    // 求解父顶点 parent[]数组和权重之和
    void MSTPath() {
        if (computed) return;

        // 检查图是否连通
        if (!isGraphConnected()) {
            mstExists = false;
            computed = true;
            return;
        }

        minDist[1] = 0;
        // 循环 v - 1次, 构建 v - 1 条边
        for (int i = 1; i < v; ++i) {
            // Prim算法第 1 步: 找到一个未加入 MST 且权重最小的顶点
            int cur = -1;
            int minVal = INT_MAX;
            for (int j = 1; j <= v; ++j) {    
                if (!isInTree[j] && minDist[j] < minVal) {
                    minVal = minDist[j];
                    cur = j;
                }
            }

            // 如果找不到合适的顶点, 说明图不连通
            if (cur == -1) {
                mstExists = false;
                computed = true;
                return;
            }

            // Prim算法第 2 步: 把已找到的顶点 cur 加入到 MST 中
            isInTree[cur] = true;

            // Prim算法第 3 步: 更新minDist数组, 只更新不在 MST 中且与 cur 相连的
            for (int j = 1; j <= v; ++j) {
                if (!isInTree[j] && grid[cur][j] < minDist[j]) {
                    minDist[j] = grid[cur][j];
                    // 顶点 j 通过与 cur 相连进入MST, 于是 j 的父顶点就是 cur
                    parent[j] = cur;
                }
            }
        }

        for (int i = 1; i <= v; ++i) {
            // 有顶点没有加入到MST中
            if (minDist[i] == MAX_VAL && i != 1) {
                mstExists = false;
                computed = true;
                return;
            }
            sum += minDist[i];
        }
        mstExists = true;  // 确保计算成功时设为true
        computed = true;
    }

public:
    // 检查是否能生成MST
    bool canGenerateMST() {
        if (!computed) MSTPath();
        return mstExists;
    }

    // 打印 MST
    void printMST() {
        if (!computed) MSTPath();
        
        if (!mstExists) {
            cout << "无法生成最小生成树, 图不连通" << endl;
            return;
        }
        
        cout << "最小生成树的边：" << endl;
        for (int i = 2; i <= v; ++i) {  // 从2开始，因为顶点1没有父节点
            if (parent[i] != -1) {
                cout << parent[i] << " - " << i << " (权重: " << grid[parent[i]][i] << ")" << endl;
            }
        }
    }

    int sumOfMSTValues() {
        if (!computed) MSTPath();
        // 如果不能生成MST, 返回-1;
        return mstExists ? sum : -1;  
    }

    // 获取MST的边
    vector<pair<int, int>> getMSTEdges() {
        vector<pair<int, int>> edges;
        if (!computed) MSTPath();
        
        if (mstExists) {
            for (int i = 2; i <= v; ++i) {
                if (parent[i] != -1) {
                    edges.push_back({parent[i], i});
                }
            }
        }
        return edges;
    }
};

int main(int argc, char const* argv[]) {
    const int MAX_VAL = 1e5 + 1;
    int v, e;               // 顶点数 边数 
    int a, b, val;          // 顶点a 顶点b 权重
    
    // 输入顶点数和边数
    cin >> v >> e;
    // 邻接矩阵 grid[i][j] = val 表示顶点i到顶点j的边权重为 val 
    // 注意: 如果顶点i和顶点j之间没有边相连, 权值设为无限大
    vector<vector<int>> grid(v + 1, vector<int>(v + 1, MAX_VAL));
    
    while (e--) {
        cin >> a >> b >> val;
        grid[a][b] = val;
        grid[b][a] = val;
    }
    PrimMST* pmst = new PrimMST(MAX_VAL, grid);

    // 先检查是否能生成MST
    if (pmst->canGenerateMST()) {
        pmst->printMST();
        cout << "MST权重和: " << pmst->sumOfMSTValues() << endl;
    } 
    else {
        cout << "无法生成最小生成树" << endl;
    }

    delete pmst;

    return 0;
}
