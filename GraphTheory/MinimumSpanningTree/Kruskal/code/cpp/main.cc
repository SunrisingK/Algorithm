#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 并查集, 用于快速判断待生成的树中是否有环
class UnionSet {
private:
    static const int N = 1e5;   // 顶点数量的最大值
    int size;
    vector<int> count;          // 所在集合的元素数量
    vector<int> p;              // 集合根节点
public:
    UnionSet(int size = N) : size(size) {
        p.resize(size + 1);
        count.resize(size + 1, 1);
        for (int i = 0; i < size; ++i) {
            p[i] = i;
        }
    }

    // 查找x的根节点
    int find(int x) {
        if (p[x] != x) {
            p[x] = find(p[x]);  // 路径压缩
        }
        return p[x];
    }

    // 合并节点x和节点y
    void merge(int x, int y) {
        int px = find(x), py = find(y);
        if (px != py) {
            // 简单的按大小合并
            if (count[px] < count[py]) {
                swap(px, py);
            }
            count[px] += count[py];
            p[py] = px;
        }
    }
};

// Kruskal算法的重点是边, 这里写一个边的结构体
struct Edge {
    int a, b;   // 表示边的顶点
    int val;    // 边的权重
};


int main(int argc, char const* argv[]) {
    int v, e;
    int a, b, val;
    
    cin >> v >> e;
    vector<Edge> edges;
    while (e--) {
        cin >> a >> b >> val;
        edges.push_back({a, b, val});
    }

    // Kruskal算法第1步: 按照权重从小打大排序边
    sort(edges.begin(), edges.end(), [&](Edge& e1, Edge& e2) {
        return e1.val < e2.val;
    });

    // 初始化并查集(顶点编号从1开始)
    UnionSet st(v);

    int ans = 0;
    int count = 0;      // 统计加入到MST的边
    // 遍历排序后的边, 算法每次选出不在同一个集合里的2个顶点
    for (Edge& edge: edges) {
        if (count == e - 1) break;
        int a = edge.a, b = edge.b;
        int pa = st.find(a);
        int pb = st.find(b);

        // a和b不在同一个集合里, 就把边<a, b>加入到 MST 中
        if (pa != pb) {
            ans += edge.val;    // 累加最小权重
            st.merge(pa, pb);   // 合并集合
            ++count;
        }
    }

    cout << ans;

    return 0;
}