package GraphTheory.ShortestPath.Dijkstra.HeapOptimizedDijkstra.code.java;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.PriorityQueue;     // Java中使用优先队列的包

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
            return val;
        }
    };

    // 用于优先队列的Pair类
    static class Pair {
        private int vertex;     // 已知最小距离的顶点
        private int dist;       // 最小距离

        public Pair(int vertex, int dist) {
            this.vertex = vertex;
            this.dist = dist;
        }

        public int getVertex() {
            return this.vertex;
        }

        public int getDist() {
            return this.dist;
        }
    }

    static int heapDijkstra(int start, int end, List<List<Edge>> grid) {
        int n = grid.size() - 1;
        int[] minDist = new int[n + 1];
        Arrays.fill(minDist, Integer.MAX_VALUE);
        boolean[] visited = new boolean[n + 1];
        // 堆优化版的Dijkstra算法仍然使用 minDist[] 数组和 visited[] 数组
        // 对比朴素Dijkstra算法, 区别在于堆优化版遍历的是边, 朴素版遍历的是顶点

        // 使用小顶堆, 使用Lambda表达式来替代比较器类
        PriorityQueue<Pair> que = new PriorityQueue<>((a, b) -> a.dist - b.dist);

        // 起点到起点作为初始状态, 作为初始边
        minDist[start] = 0;
        que.offer(new Pair(start, 0));

        while (!que.isEmpty()) {
            // (顶点, 最短距离)
            Pair p = que.poll();    // 获取并弹出堆顶元素
            int cur = p.vertex;
            
            // Dijkstra算法第 1 步: 选择一个未被访问过且到起点最近的顶点
            if (visited[cur]) continue;

            // Dijkstra算法第 2 步: 把找到的顶点标记为已访问
            visited[cur] = true;
            // 如果当前节点就是终点，可以提前结束
            if (cur == end) break;

            // Dijkstra算法第 3 步: 更新起点到剩余未被访问过的顶点的距离, 只更新与 cur 相连的
            for (Edge edge: grid.get(cur)) {
                int v = edge.getOut();
                if (!visited[v] && minDist[cur] + edge.getVal() < minDist[v]) {
                    minDist[v] = minDist[cur] + edge.getVal();
                    que.offer(new Pair(v, minDist[v]));
                }
            }
        }
        return minDist[end] == Integer.MAX_VALUE ? -1 : minDist[end];
    }


    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        
        // 存储图的邻接表, 大小为 n + 1
        List<List<Edge>> grid = new ArrayList<>();
        for (int i = 0; i <= n; ++i) {
            grid.add(new ArrayList<>());
        }

        while (m-- > 0) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int val = sc.nextInt();
            grid.get(a).add(new Edge(b, val));  // 添加有向边
        }
        
        int start = 1;
        int end = n;

        System.out.println(heapDijkstra(start, end, grid));

        sc.close();        
    }
}
