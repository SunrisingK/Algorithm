package GraphTheory.ShortestPath.Dijkstra.HeapOptimizedDijkstra.code.java;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Arrays;
import java.util.Collections;

/* 堆优化 Dijkstra 算法拓展: 打印出最短路径 */

// 将堆优化 Dijkstra 算法封装成一个类, 可以返回最短路径长度, 还有打印最短路径
class HeapDijkstra {
    static class Edge {
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

    private class Pair {
        private int vertex;
        private int dist;

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

    private int n;
    private boolean pathExists;
    private boolean computed;

    private int[] minDist;
    private boolean[] visited;
    private int[] parent;
    private List<List<Edge>> grid;

    private PriorityQueue<Pair> que;

    private int lastStart;
    private int lastEnd;

    public HeapDijkstra(List<List<Edge>> grid) {
        this.n = grid.size() - 1;
        this.grid = grid;
        this.pathExists = false;
        this.computed = false;
    }

    private void shortestPath(int start, int end) {
        // 如果已经计算过相同的起点终点，直接返回
        if (computed && lastStart == start && lastEnd == end) return;
        
        minDist = new int[this.n + 1];
        Arrays.fill(minDist, Integer.MAX_VALUE);
        
        visited = new boolean[this.n + 1];
        
        parent = new int[this.n + 1];
        Arrays.fill(parent, -1);

        que = new PriorityQueue<>((a, b) -> Integer.compare(a.getDist(), b.getDist()));

        // 小顶堆中存放的是从起点到某个顶点点的当前已知最短距离
        // 起点到起点作为初始状态, 作为初始边
        minDist[start] = 0;
        que.offer(new Pair(start, 0));

        while (!que.isEmpty()) {
            //  (顶点, 最短距离)
            Pair p = que.poll();
            int cur = p.getVertex();

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
                    parent[v] = cur;
                }
            }
        }
        pathExists = minDist[end] != Integer.MAX_VALUE;
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
        
        List<List<HeapDijkstra.Edge>> grid = new ArrayList<>();
        for (int i = 0; i <= n; ++i) {
            grid.add(new ArrayList<>());
        }

        while (m-- > 0) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int val = sc.nextInt();
            grid.get(a).add(new HeapDijkstra.Edge(b, val));
        }

        int start = 1;
        int end = n;

        HeapDijkstra headDij = new HeapDijkstra(grid);
        headDij.printShortestPath(start, end);

        sc.close();
    }
}