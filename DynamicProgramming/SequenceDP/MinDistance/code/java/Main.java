package DynamicProgramming.SequenceDP.MinDistance.code.java;


class Solution {
    public int minDistance(String word1, String word2) {
        int n = word1.length();
        int m = word2.length();

        int[][] dp = new int[1 + n][1 + m];
        for (int i = 0; i <= n; ++i) dp[i][0] = i;
        for (int j = 0; j <= m; ++j) dp[0][j] = j;

        // dp[i][j] 表示前缀长度为 i 的 word1 变换到前缀长度为 j 的 word2 需要的最短距离
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    // 遍历到相同字符
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    // 3 个方向更新最小值
                    dp[i][j] = Math.min(
                        Math.min(dp[i - 1][j], dp[i][j - 1]), 
                        dp[i - 1][j - 1]
                    ) + 1;
                }
            }
        }
        return dp[n][m];
    }
}

public class Main {
    public static void main(String[] args) {
        String word1 = "horse";
        String word2 = "ros";
        Solution solution = new Solution();
        System.out.println(solution.minDistance(word1, word2));
    }
}
