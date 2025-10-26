package Prim.code.java;
import java.util.*;

public class Main {
    static final int MAX_VAL = 10001;

    private static int valSumofMST(int v, int[][] grid) {
        int[] minDist = new int[v + 1];
        Arrays.fill(minDist, MAX_VAL);
        boolean[] isInTree = new boolean[v + 1];

        // 循环 v - 1 次, 构建 v - 1 条边
        for (int i = 1; i < v; ++i) {
            // Prim算法第一步: 找到不在MST中的且具有最小权重的顶点
            int cur = -1;
            int minVal = Integer.MAX_VALUE;
            for (int j = 1; j <= v; ++j) {
                if (!isInTree[j] && minDist[j] < minVal) {
                    minVal = minDist[j];
                    cur = j;
                }
            }
            // 通常会把编号为 1 的顶点加入到 MST 中

            // Prim算法第2步: 把找到的顶点加入到MST中
            isInTree[cur] = true;

            // Prim算法第3步: 更新minDist[]数组, 只更新与cur相连的且不在MST中的顶点
            for (int j = 1; j <= v; ++j) {
                if (!isInTree[j] && grid[cur][j] < minDist[j]) {
                    minDist[j] = grid[cur][j];
                }
            }
        }

        minDist[1] = 0;
        int ans = 0;
        for (int i = 1; i <= v; ++i) {
            ans += minDist[i];
        }

        return ans;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int v = sc.nextInt();   // 顶点数
        int e = sc.nextInt();   // 边数
        // 邻接矩阵 grid[i][j] = val 表示顶点i到顶点j的边权重为 val 
        // 注意: 如果顶点i和顶点j之间没有边相连, 权值设为无限大
        int[][] grid = new int[v + 1][v + 1];
        for (int i = 0; i <= v; ++i) {
            Arrays.fill(grid[i], MAX_VAL);
        }

        while (e-- > 0) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int val = sc.nextInt();
            grid[a][b] = val;
            grid[b][a] = val;
        }

        System.out.println(valSumofMST(v, grid));

        sc.close();
    }
}
