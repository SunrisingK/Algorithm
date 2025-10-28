package GraphTheory.ShortestPath.Dijkstra.NaiveDijkstra.code.java;
import java.util.Scanner;
import java.util.Arrays;

public class Main {
    private static int naiveDijkstra(int n, int start, int end, int[][] grid) {
        int[] minDist = new int[n + 1];
        Arrays.fill(minDist, Integer.MAX_VALUE);
        boolean[] visited = new boolean[n + 1];
        
        // 遍历所有的顶点, 遍历 minDist[] 数组
        minDist[start] = 0;
        for (int i = 1; i <= n; ++i) {
            // Dijkstra算法第 1 步: 选择一个没被访问过且距离起点最近的顶点 v
            int cur = -1;
            int minVal = Integer.MAX_VALUE;
            for (int v = 1; v <= n; ++v) {
                if (!visited[v] && minDist[v] < minVal) {
                    cur = v;
                    minVal = minDist[v];
                }
            }

            // 如果找不到可用的顶点，说明剩下的顶点都不可达
            if (cur == -1) break;

            // Dijkstra算法第 2 步: 把找到的顶点标记为已访问
            visited[cur] = true;

            // Dijkstra算法第 3 步: 更新 minDist 数组, 只更新与 cur 相连的顶点的 minDist 值
            for (int v = 1; v <= n; ++v) {
                if (!visited[v] && grid[cur][v] != Integer.MAX_VALUE && minDist[cur] + grid[cur][v] < minDist[v]) {
                    minDist[v] = minDist[cur] + grid[cur][v];
                }
            }
        }

        return minDist[end] == Integer.MAX_VALUE ? -1 : minDist[end];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();   // 顶点数
        int m = sc.nextInt();   // 边数

        int[][] grid = new int[n + 1][n + 1];
        for (int i = 0; i <= n; ++i) {
            Arrays.fill(grid[i], Integer.MAX_VALUE);
        }

        for (int i = 0; i < m; ++i) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int val = sc.nextInt();
            grid[a][b] = val;
        }

        int start = 1;
        int end = n;

        System.out.println(naiveDijkstra(n, start, end, grid));

        sc.close();
    }
}
