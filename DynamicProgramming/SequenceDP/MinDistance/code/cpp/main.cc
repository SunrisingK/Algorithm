#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        // dp[i][j] 表示前缀长度为 i 的 word1 变换到前缀长度为 j 的 word2 需要的最短距离
        vector<vector<int>> dp(1 + n, vector<int>(1 + m));
        for (int i = 0; i <= n; ++i) dp[i][0] = i;
        for (int j = 0; j <= m; ++j) dp[0][j] = j;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    // 遍历到相同字符
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    // 3 个方向更新最小值
                    dp[i][j] = min({
                        dp[i - 1][j - 1], 
                        dp[i - 1][j], 
                        dp[i][j - 1]
                    }) + 1;
                }
            }
        }
        return dp[n][m];
    }
};


int main(int argc, char const* argv[]) {
    string word1 = "horse";
    string word2 = "ros";
    Solution solution;
    cout << solution.minDistance(word1, word2);
}