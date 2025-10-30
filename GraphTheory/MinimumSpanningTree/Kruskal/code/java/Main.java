package Kruskal.code.java;

import java.util.*;


class Edge {
    private int a, b, val;

    public Edge(int a, int b, int val) {
        this.a = a;
        this.b = b;
        this.val= val;
    }

    public int getA() { return a; }
    public int getB() { return b; }
    public int getVal() { return val; }
}

class DisjointSet {
    private int[] p;
    private int[] count;

    public DisjointSet(int n) {
        p = new int[n];
        count = new int[n];
        for (int i = 0; i < n; ++i) {
            p[i] = i;
            count[i] = 1;
        }
    }

    public int find(int x) {
        if (p[x] != x) {
            p[x] = find(p[x]);  // 路径压缩
        }
        return p[x];
    }

    public void merge(int x, int y) {
        int px = find(x), py = find(y);
        if (px != py) {
            if (count[px] < count[py]) {
                int temp = px;
                px = py;
                py = temp;
            }
            count[px] += count[py];
            p[py] = px;
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int v = sc.nextInt();   // 顶点数
        int e = sc.nextInt();   // 边数
        
        Edge[] edges = new Edge[e];
        for (int i = 0; i < e; ++i) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int val = sc.nextInt();
            edges[i] = new Edge(a, b, val);
        }

        // Kruskal算法第1步: 按照权重从小打大排序边
        Arrays.sort(edges, (e1, e2) -> Integer.compare(e1.getVal(), e2.getVal()));

        // 初始化并查集(顶点编号从1开始)
        DisjointSet st = new DisjointSet(v + 1);
        int ans = 0;
        for (Edge edge: edges) {
            int a = edge.getA();
            int b = edge.getB();
            int pa = st.find(a);
            int pb = st.find(b);
            if (pa != pb) {
                ans += edge.getVal();
                st.merge(pa, pb);
            }
        }
        System.out.println(ans);
        sc.close();
    }
}
