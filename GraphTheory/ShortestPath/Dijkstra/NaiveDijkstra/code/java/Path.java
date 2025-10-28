package GraphTheory.ShortestPath.Dijkstra.NaiveDijkstra.code.java;

import java.util.Arrays;
import java.util.Collections;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Path {
    private static class NaiveDijkstra {
        private int n;
        private boolean pathExists;

        private int[] minDist;
        private boolean[] visited;
        private int[] parent;
        private int[][] grid;

        public NaiveDijkstra(int[][] grid) {
            this.grid = grid;
            this.n = grid.length - 1;
            this.pathExists = false;
        }

        private void shortestPath(int start, int end) {
            minDist = new int[n + 1];
            Arrays.fill(minDist, Integer.MAX_VALUE);

            visited = new boolean[n + 1];
            
            parent = new int[n + 1];
            Arrays.fill(parent, -1);

            minDist[start] = 0;
            // 遍历所有顶点, 遍历 minDist[] 数组
            for (int i = 1; i <= n; ++i) {
                // Dijkstra算法第1步: 选择一个未被访问过且到起点最近的顶点
                int cur = -1;
                int minVal = Integer.MAX_VALUE;
                for (int v = 1; v <= n; ++v) {
                    if (!visited[v] && minDist[v] < minVal) {
                        cur = v;
                        minVal = minDist[v];
                    }
                }

                // 如果找不到可用的顶点，说明剩下的顶点都不可达
                if (cur == -1) {
                    pathExists = false;
                    break;
                }

                // Dijkstra算法第 2 步: 把找到的顶点标记为已访问
                visited[cur] = true;

                // Dijkstra算法第3步: 更新起点到剩余未被访问过的顶点的距离
                for (int v = 1; v <= n; ++v) {
                    if (!visited[v] && grid[cur][v] != Integer.MAX_VALUE && minDist[cur] + grid[cur][v] < minDist[v]) {
                        minDist[v] = minDist[cur] + grid[cur][v];
                        parent[v] = cur;
                    }
                }
            }
            pathExists = minDist[end] != Integer.MAX_VALUE;
        }

        private List<Integer> reconstructPath(int start, int end) {
            List<Integer> path = new ArrayList<>();
            if (!pathExists) return path;

            // 从终点反向到起点 
            for (int v = end; v != -1; v = parent[v]) {
                path.add(v);
            }

            Collections.reverse(path);

            if (path.isEmpty() || path.get(0) != start) {
                pathExists = false;
                return new ArrayList<>();
            }

            return path;
        }

        public void printShortestPath(int start, int end) {
            shortestPath(start, end);
            if (pathExists) {
                System.out.println("起点" + start + "到终点" + end + "存在最短路径: ");
                List<Integer> path = reconstructPath(start, end);
                for (int i = 0; i < path.size(); ++i) {
                    if (i > 0) System.out.print(" -> ");
                    System.out.print(path.get(i));
                }
                System.out.println("\n路径长度: " + minDist[end]);
            }
            else {
                System.out.println("起点" + start + "到终点" + end + "不存在路径");
            }
        }

        // 获取最短路径长度
        public int getShortestDistance(int start, int end) {
            shortestPath(start, end);
            return pathExists ? minDist[end] : -1;
        }

        // 额外的工具方法：只获取路径不打印
        public List<Integer> getShortestPath(int start, int end) {
            shortestPath(start, end);
            return reconstructPath(start, end);
        }

        // 检查路径是否存在
        public boolean hasPath(int start, int end) {
            shortestPath(start, end);
            return pathExists;
        }
    }


    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();

        int[][] grid = new int[n + 1][n + 1];
        for (int i = 0; i <= n; ++i) {
            Arrays.fill(grid[i], Integer.MAX_VALUE);
        }
        for (int i = 0; i < m; ++i) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int val = sc.nextInt();
            // 有向边 a->b
            grid[a][b] = val;
        }

        NaiveDijkstra naiveDij = new NaiveDijkstra(grid);
        naiveDij.printShortestPath(1, n);
        naiveDij.getShortestDistance(2, n);
        naiveDij.getShortestPath(3, n);
        naiveDij.hasPath(4, n);

        sc.close();
    }
}