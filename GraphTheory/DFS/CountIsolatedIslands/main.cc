#include <iostream>
#include <vector>
using namespace std;


class Solution {
private:
    int n, m;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    vector<vector<bool>> visited;

    void dfs(int x, int y, vector<vector<int>>& grid) {
        if (x < 0 || x >= n || y < 0 || y >= m) return;
        if (grid[x][y] == 0 || visited[x][y]) return;

        visited[x][y] = true;
        for (int i = 0; i < 4; ++i) {
            int next_x = x + dx[i];
            int next_y = y + dy[i];
            dfs(next_x, next_y, grid);
        }
    }
    
public:
    int countIsolatedIslands(vector<vector<int>>& grid) {
        int count = 0;
        
        n = grid.size(); 
        m = grid[0].size();
        visited.resize(n, vector<bool>(m, false));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    dfs(i, j, grid);
                    ++count;
                }
            }
        }

        return count;
    }
};


int main(int argc, char const* argv[]) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }

    Solution* s = new Solution();
    cout << s->countIsolatedIslands(grid);

    return 0;
}