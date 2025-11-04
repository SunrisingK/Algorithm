package DataStructure.DisjointSet;

public class DisjointSet {
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