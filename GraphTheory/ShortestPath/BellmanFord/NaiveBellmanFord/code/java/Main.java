package GraphTheory.ShortestPath.BellmanFord.NaiveBellmanFord.code.java;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;


public class Main {
    static class Edge {
        private int in;
        private int out; 
        private int val;

        public Edge(int in, int out, int val) {
            this.in = in;
            this.out = out;
            this.val = val;
        }

        public int getIn() {
            return this.in;
        }

        public int getOut() {
            return this.out;
        }

        public int getVal() {
            return this.val;   
        }
    }

    static int naiveBellmanFord(int start, int end, int n, List<Edge> grid) {
        int[] minDist = new int[n + 1];
        Arrays.fill(minDist, Integer.MAX_VALUE);
        // BellmanFord算法里没有 visited[] 数组
        // 因为同一个点会被访问多次进行松弛操作, 而在Dijkstra算法里顶点最多被访问过一次

        // 朴素版BellmanFord算法: 进行n - 1 次松弛操作, 每次操作都要松弛可以到达的顶点作为入点的边 
        minDist[start] = 0;
        for (int i = 1; i < n; ++i) {
            for (Edge edge: grid) {
                int u = edge.getIn();
                int v = edge.getOut();
                int val = edge.getVal();

                // 每次只松弛计算过的边, 也就是说 minDist[u] != INT_MAX
                // minDist[u] != INT_MAX, 表示顶点 u 可以到达
                // 顶点 u 还是入点, 那么就可以松弛有向边<u, v>

                if (minDist[u] != Integer.MAX_VALUE && minDist[u] + val < minDist[v]) {
                    minDist[v] = minDist[u] + val;
                }
            }
        }
        return minDist[end];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();

        List<Edge> grid = new ArrayList<>();
        while (m-- > 0) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int val = sc.nextInt();
            grid.add(new Edge(a, b, val));
        }

        int start = 1;
        int end = n;

        int shortestPath = naiveBellmanFord(start, end, n, grid);
        String s = (shortestPath == Integer.MAX_VALUE ? "unconnected" : String.valueOf(shortestPath));
        System.out.println(s);

        sc.close();
    }
}
