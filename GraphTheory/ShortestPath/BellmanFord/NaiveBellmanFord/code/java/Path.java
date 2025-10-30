package GraphTheory.ShortestPath.BellmanFord.NaiveBellmanFord.code.java;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import java.util.Collections;

class NaiveBellmanFord {
    public static class Edge {
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

    private int n;
    private List<Edge> grid;
    
    private boolean pathExists;
    private boolean computed;
    private int lastStart;
    private int lastEnd;

    private int[] parent;
    private int[] minDist;


    public NaiveBellmanFord(int n, List<Edge> grid) {
        this.n = n;
        this.grid = grid;
    }

    private void shortestPath(int start, int end) {
        // 如果已经计算过相同的起点终点, 直接返回
        if (computed && lastStart == start && lastEnd == end) return;

        minDist = new int[n + 1];
        Arrays.fill(minDist, Integer.MAX_VALUE);

        parent = new int[n + 1];
        Arrays.fill(parent, -1);

        minDist[start] = 0;
        for (int i = 1; i < n; ++i) {
            for (Edge edge: grid) {
                int u = edge.getIn();
                int v = edge.getOut();
                int val = edge.getVal();

                if (minDist[u] != Integer.MAX_VALUE && minDist[u] + val < minDist[v]) {
                    minDist[v] = minDist[u] + val;
                    parent[v] = u;
                }
            }
        }
        pathExists = (minDist[end] != Integer.MAX_VALUE);
        computed = true;
        lastStart = start;
        lastEnd = end;
    }

    private List<Integer> reconstructPath(int start, int end) {
        List<Integer> path = new ArrayList<>();

        if (!pathExists) return path;

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

public class Path {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();

        List<NaiveBellmanFord.Edge> grid = new ArrayList<>();
        while (m-- > 0) {
            int in = sc.nextInt();
            int out = sc.nextInt();
            int val = sc.nextInt();
            grid.add(new NaiveBellmanFord.Edge(in, out, val));
        }

        int start = 1;
        int end = n;
        NaiveBellmanFord nBF = new NaiveBellmanFord(n, grid);
        nBF.printShortestPath(start, end);
        
        sc.close();
    }
}
