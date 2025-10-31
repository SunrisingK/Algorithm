package GraphTheory.ShortestPath.BellmanFord.QueueOptimizedBellmanFord.code.java;

import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Queue;
import java.util.LinkedList;

public class Main {
    static class Edge {
        private int out;
        private int val;

        Edge(int out, int val) {
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

    static int queueOptimizedBellmanFord(int start, int end, List<List<Edge>> grid) {
        int n = grid.size() - 1;
        int[] minDist = new int[n + 1];
        Arrays.fill(minDist, Integer.MAX_VALUE);
        boolean[] isInQueue = new boolean[n + 1];    // 记录是否在队列中

        Queue<Integer> que = new LinkedList<>();     // 存放计算过的顶点
        que.offer(start);       
        minDist[start] = 0;

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
                    // out 已经计算过了, 如果不在队列中则需要入队
                    // if () 条件判断可以避免重复入队
                    if (!isInQueue[out]) {
                        que.offer(out);
                        isInQueue[out] = true;
                    }
                }
            }
        }
        return minDist[end];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();

        List<List<Edge>> grid = new ArrayList<>();
        // 使用邻接表存储图, 邻接表得指定大小并初始化
        for (int i = 0; i <= n; i++) {
            grid.add(new ArrayList<>());
        }

        while (m-- > 0) {
            int in = sc.nextInt();
            int out = sc.nextInt();
            int val = sc.nextInt();
            grid.get(in).add(new Edge(out, val));
        }

        int start = 1;
        int end = n;

        int shortestPath = queueOptimizedBellmanFord(start, end, grid);
        String s = (shortestPath == Integer.MAX_VALUE ? "unconnected" : String.valueOf(shortestPath));
        System.out.println(s);

        sc.close();
    }
}
