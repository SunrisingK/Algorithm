#include <iostream>
#include <vector>
#include <queue>
using namespace std;


class Solution {
private:
    int n, m;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    vector<vector<bool>> visited;

    void bfs(int x, int y, vector<vector<int>>& grid) {
        queue<pair<int, int>> que;
        que.push({x, y});
        visited[x][y] = true;
        
        while (!que.empty()) {
            pair<int, int> p = que.front();
            que.pop();
            for (int i = 0; i < 4; ++i) {
                int next_x = p.first + dx[i];
                int next_y = p.second + dy[i];
                if (next_x < 0 || next_x >= n || next_y < 0 || next_y >= m) continue;
                if (grid[next_x][next_y] == 0 || visited[next_x][next_y]) continue;
                que.push({next_x, next_y});
                visited[next_x][next_y] = true;
            }
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
                    bfs(i, j, grid);
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