package DataStructure.DisjointSet.FindPath.code.java;

import java.util.Scanner;

class DisjointSet {
    public DisjointSet(int n) {
        p = new int[1 + n];
        count = new int[1 + n];
        for (int i = 1; i <= n; ++i) {
            p[i] = i;
            count[i] = 1;
        }
    }

    public int find(int x) {
        if (x != p[x]) {
            p[x] = find(p[x]);  // 路径压缩
        }
        return p[x];
    }

    // 快速判断两个点 x 和 y 是否在同一个集合里
    public boolean isInSame(int x, int y) {
        return find(x) == find(y);
    }    

    // 把两个点 x 和 y 加入到同一个集合里
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

    private int[] p;        // 节点所在集合的根节点
    private int[] count;    // 节点所在集合的元素数量
}

public class Main {
    public static void main(String[] args) {
        // 输入的是无向图, 而且只要求返回是否存在路径
        // 输入的是由2个顶点表示的边, 直接套用并查集模板
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();

        DisjointSet st = new DisjointSet(n);
        while (m-- > 0) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            st.merge(a, b);
        }
        int source = sc.nextInt();
        int destination = sc.nextInt();
        System.out.println(st.isInSame(source, destination) ? 1 : 0);
        sc.close();
    }
}
