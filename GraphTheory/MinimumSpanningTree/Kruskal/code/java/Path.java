package Kruskal.code.java;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;


public class Path {
    static class Edge {
        private int a;
        private int b;
        private int val;
    
        public Edge(int a, int b, int val) {
            this.a = a;
            this.b = b;
            this.val = val;
        }
    
        public int getA() {
            return a;
        }
    
        public int getB() {
            return b;
        }
    
        public int getVal() {
            return val;
        }
    }
    
    static class UnionSet {
        private int size;
        private int[] p;        // 集合根节点
        private int[] count;    // 所在集合的元素数量
    
        public UnionSet(int size) {
            this.size = size;
            p = new int[size + 1];
            count = new int[size + 1];
            for (int i = 1; i <= size; ++i) {
                p[i] = i;
                count[i] = 1;
            }
        }
    
        // 查找x的根节点
        public int find(int x) {
            if (x != p[x]) {
                p[x] = find(p[x]);  // 路径压缩
            }
            return p[x];
        }
    
        // 合并节点x和节点y
        public void merge(int x, int y) {
            int px = find(x), py = find(y);
            if (px != py) {
                // 简单的按大小合并
                if (count[px] < count[py]) {
                    int temp = px;
                    px = py;
                    py = temp;
                }
                count[px] += count[py];
                p[py] = px;
            }
        }
    
        // 判断 x 和 y 是否在同一个集合里
        public boolean connected(int x, int y) {
            return find(x) == find(y);
        }
    
        // 返回集合的个数
        public int getComponentCount() {
            int count = 0;
            for (int i = 1; i <= size; ++i) {
                count += (p[i] == i) ? 1 : 0;
            }
            return count;
        }
    }
    
    static class KruskalMST {
        private UnionSet st;
        
        private int v;
        private int sum;
        private boolean computed;
        private boolean mstExists;
    
        private Edge[] edges;
        private List<Edge> mstEdges;
    
        public KruskalMST(int v, Edge[] edges) {
            st = new UnionSet(v);
            this.v = v;
            this.sum = 0;
            this.computed = false;
            this.mstExists = false;
            this.mstEdges = new ArrayList<>();
            this.edges = edges;
        }
    
        private void MSTPath() {
            // Kruskal算法第 1 步: 按照边的权重从小到大排序
            Arrays.sort(edges, (e1, e2) -> Integer.compare(e1.getVal(), e2.getVal()));
    
            // Kruskal算法第 2 步: 遍历排序后的边数组, 选择一个加入到MST中不会产生环路的边
            for (Edge edge : edges) {
                if (mstEdges.size() == v - 1) break;
    
                int pa = st.find(edge.getA());
                int pb = st.find(edge.getB());
                if (pa != pb) {
                    st.merge(pa, pb);
                    sum += edge.getVal();
                    mstEdges.add(edge);
                }
            }
            // 确保计算成功时设为true
            mstExists = (mstEdges.size() == v - 1);
            computed = true;
        }
    
        // 是否可以得到MST
        public boolean canGenerateMST() {   
            if (!computed) MSTPath();
            return mstExists;
        }
    
        // 返回MST权重之和
        public int sumOfMSTValues() {
            if (!computed) MSTPath();
            return mstExists ? sum : -1;
        }
    
        public void printMST() {
            if (!computed) MSTPath();
    
            if (!mstExists) {
                System.out.println("无法生成最小生成树");
                return;
            }
    
            System.out.println("生成最小生成树: ");
            for (Edge edge: mstEdges) {
                System.out.println(edge.getA() + " - " + edge.getB() + " (权重: " + edge.getVal() + ")");
            }
        }
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int v = sc.nextInt();
        int e = sc.nextInt();

        Edge[] edges = new Edge[e];
        for (int i = 0; i < e; ++i) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int val = sc.nextInt();
            edges[i] = new Edge(a, b, val);
        }

        KruskalMST kmst = new KruskalMST(v, edges);
        // 先检查是否能生成MST
        if (kmst.canGenerateMST()) {
            kmst.printMST();
            System.out.println("MST权重和: " + kmst.sumOfMSTValues());
        } 
        else {
            System.out.println("无法生成最小生成树");
        }

        sc.close();
    }
}