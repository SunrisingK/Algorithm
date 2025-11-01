package GraphTheory.ShortestPath.BellmanFord.QueueOptimizedBellmanFord.code.java;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;


/* 队列优化版 BellmanFord 算法拓展: 打印出最短路径 */

// 将队列优化版 BellmanFord 算法封装成一个类, 可以返回最短路径长度, 还有打印最短路径
class QueueOptimizedBellmanFord {
    public static class Edge {
        private int out;
        private int val;

        public Edge(int out, int val) {
            this.out = out;
            this.val = val;
        }

        public int getOut() {
            return this.out;
        }

        public int getVal() {
            return this.val;
        }
    }

    private int n;
    private boolean pathExists;
    private boolean computed;

    private int[] minDist;
    private boolean[] isInQueue;
    private int[] parent;
    private List<List<Edge>> grid;

    private Queue<Integer> que;

    private int lastStart;
    private int lastEnd;

    public QueueOptimizedBellmanFord(List<List<Edge>> grid) {
        this.grid = grid;
        this.n = grid.size() - 1;
        this.computed = false;
        this.pathExists = false;
        this.que = new LinkedList<>();
    }

    private void shortestPath(int start, int end) {
        // 如果已经计算过相同的起点终点, 直接返回
        if (computed && lastStart == start && lastEnd == end) return;

        minDist = new int[1 + n];
        Arrays.fill(minDist, Integer.MAX_VALUE);
        
        parent = new int[1 + n];
        Arrays.fill(parent, -1);

        isInQueue = new boolean[1 +  n];

        minDist[start] = 0;
        que.offer(start);

        while (!que.isEmpty()) {
            int vertex = que.poll();
            // 顶点出队, isInQueue[vertex] = false; 不能忘记
            isInQueue[vertex] = false;

            // 出队的顶点 vertex 是计算过的, 松弛以 vertex 为入点的边
            for (Edge edge: grid.get(vertex)) {
                int out = edge.getOut();
                int val = edge.getVal();

                if (minDist[vertex] + val < minDist[out]) {
                    minDist[out] = minDist[vertex] + val;
                    parent[out] = vertex;
                    // out 已经计算过了, 如果不在队列中则需要入队
                    // if () 条件判断可以避免重复入队
                    if (!isInQueue[out]) {
                        que.offer(out);
                        isInQueue[out] = true;
                    }
                }
            }
        }
        pathExists = (minDist[end] != Integer.MAX_VALUE);
        computed = true;
        lastStart = start;
        lastEnd = end;
    }

    // 重构路径的辅助函数
    private List<Integer> reconstructPath(int start, int end) {
        List<Integer> path = new ArrayList<>();
        if (!pathExists) return path;

        // 从终点反向追踪到起点 
        for (int v = end; v != -1; v = parent[v]) {
            path.add(v);
        }

        // 反转路径
        Collections.reverse(path);

        if (path.isEmpty() || path.get(0) != start) {
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

        List<List<QueueOptimizedBellmanFord.Edge>> grid = new ArrayList<>();
        
        // 使用邻接表存储图, 邻接表得指定大小并初始化
        for (int i = 0; i <= n; i++) {
            grid.add(new ArrayList<>());
        }

        while (m-- > 0) {
            int in = sc.nextInt();
            int out = sc.nextInt();
            int val = sc.nextInt();
            grid.get(in).add(new QueueOptimizedBellmanFord.Edge(out, val));
        }

        int start = 1;
        int end = n;

        QueueOptimizedBellmanFord qBF = new QueueOptimizedBellmanFord(grid);
        qBF.printShortestPath(start, end);

        sc.close();
    }
}
