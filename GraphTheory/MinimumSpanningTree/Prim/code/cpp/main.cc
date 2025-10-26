#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int MAX_VAL = 1e5 + 1;
int v, e;               // 顶点数 边数 
int a, b, val;          // 顶点a 顶点b 权重

int valSumOfMST(vector<vector<int>>& grid) {
    // 顶点编号从 1 开始, isIntree[i]表示顶点 i 是否已经加入到MST中
    vector<int> isInTree(v + 1);
    // 顶点编号从 1 开始, minDist[i]表示顶点 i 到 MST 的最小距离
    vector<int> minDist(v + 1, MAX_VAL);

    // 只需要循环 v - 1 次, 建立 v - 1条边, 就可以把 v 个节点的图连在一起
    for (int i = 1; i < v; ++i) {
        // Prim算法第一步: 选择未加入到最小生成树中且距离最小生成树最近的顶点
        // 使用 isInTree[] 数组和  minDist[] 数组找到
        int cur = -1;   // 待加入树的顶点
        int minVal = INT_MAX;
        for (int j = 1; j <= v; ++j) {
            if (!isInTree[j] && minDist[j] < minVal) {
                minVal = minDist[j];    // 更新minVal
                cur = j;
            }
        }

        // Prim算法第2步: 把找到的顶点cur加入到MST中
        isInTree[cur] = 1;

        // Prim算法第3步: 利用权重更新minDIst[]数组, 只更新不在MST中且与cur相连的顶点到NST的距离(权重)
        for (int j = 1; j <= v; ++j) {
            if (!isInTree[j] && grid[cur][j] < minDist[j]) {
                minDist[j] = grid[cur][j];
            }
        }
    }

    // MST构建完成, 输出最小权值
    // 由于在Prim算法中默认顶点 1 是 MST 的根节点, 这里遍历midDist[]数组时从顶点 2 开始
    int ans = 0;
    for (int i = 2; i <= v; ++i) {
        ans += minDist[i];
    }

    return ans;
}

int main(int argc, char const* argv[]) {
    cin >> v >> e;

    // 邻接矩阵 grid[i][j] = val 表示顶点i到顶点j的边权重为 val 
    // 注意: 如果顶点i和顶点j之间没有边相连, 权值设为无限大
    vector<vector<int>> grid(v + 1, vector<int>(v + 1, MAX_VAL));   
    
    while (e--) {
        cin >> a >> b >> val;
        grid[a][b] = val;
        grid[b][a] = val;
    }
    
    cout << valSumOfMST(grid);

    return 0;   
}