#include <iostream>
#include <vector>
using namespace std;


class Solution {
private:
    vector<int> path;
    vector<vector<int>> result;

    void dfs(int cur, int n, vector<vector<int>>& grid) {
        if (cur == n) {
            path.push_back(cur);
            result.push_back(path);
            path.pop_back();
            return;
        }
        
        path.push_back(cur);
        vector<int> vertices = grid[cur];
        for (int i = 1; i <= n; ++i) {
            if (vertices[i] == 0) continue;
            dfs(i, n, grid);
        }
        path.pop_back();
    }
// 1 2 4 5
public:
    vector<vector<int>> findAllPath(vector<vector<int>>& grid) {
        int n = grid.size() - 1;
        dfs(1, n, grid);
        return result;
    }
};


int main(int argc, char const* argv[]) {
    int n, m;   // n 个顶点, m 条边
    cin >> n >> m;
    // 建立邻接表
    vector<vector<int>> grid(1 + n, vector<int>(1 + n));
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        grid[a][b] = 1;
    }

    Solution* s = new Solution();
    vector<vector<int>> result = s->findAllPath(grid);
    if (result.empty()) {
        cout << -1;
    }
    else {
        for (vector<int> p : result) {
            for (int x: p) {
                cout << x;
                if (x < n) cout << " ";
            }
            cout << endl;
        }
    }

    return 0;
}

/**
 *  0 1 1 0 0 
 *  0 0 0 1 0
 *  0 0 0 0 1
 *  0 0 0 0 1
 *  0 0 0 0 0 
 */