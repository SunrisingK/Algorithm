#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* Kruskal算法拓展: 打印出最小生成树, 也就是说打印出MST的所有边 */

class DisjointSet {
private:
    static const int N = 1e5;   // 顶点数量的最大值
    int size;
    vector<int> p;              // 集合根节点
    vector<int> count;          // 所在集合的元素数量
public:
    DisjointSet(int size = N) {
        this->size = size;
        p.resize(size + 1);
        for (int i = 0; i <= size; ++i) {
            p[i] = i;
        }
        count.resize(size + 1, 1);
    }

    // 查找x的根节点
    int find(int x) {
        if (x != p[x]) {
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

    // 检查 x 和 y 是否在同一个集合中
    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    // 返回连通分量(也就是集合)的个数
    int getComponentCount() {
        int count = 0;
        for (int i = 1; i <= size; ++i) {
            count += (p[i] == i);
        }
        return count;
    }
};


// Kruskal算法的重点是边, 这里写一个边的结构体
struct Edge {
    int a, b;   // 表示边的顶点
    int val;    // 边的权重
};


// 将Kruskal算法封装成一个类, 可以返回MST的权重和, 还有打印MST
// 为了使代码更加健壮, 增加判断是否生成了MST的代码
class KruskalMST {
private:
    vector<Edge> edges;
    DisjointSet st;
    
    int v;
    int sum;
    bool computed;
    bool mstExists;

    vector<Edge> mstEdges;

public:
    KruskalMST(int v, vector<Edge> edges): st(v), edges(edges) {
        this->v = v;
        sum = 0;
        computed = false;
        mstExists = false;
    }

private:
    void MSTPath() {
        // Kruskal算法第 1 步: 按照边的权重从小到大排序
        sort(edges.begin(), edges.end(), [&](const Edge& e1, const Edge& e2) {
            return e1.val < e2.val;
        });

        // Kruskal算法第 2 步: 遍历排序后的边数组, 选择一个加入到MST中不会产生环路的边
        for (Edge& edge: edges) {
            if (mstEdges.size() == v - 1) break;

            int pa = st.find(edge.a);
            int pb = st.find(edge.b);
            if (pa != pb) {
                st.merge(pa, pb);
                sum += edge.val;
                mstEdges.push_back(edge);
            }
        }
        // 确保计算成功时设为true
        mstExists = (mstEdges.size() == v - 1);  
        computed = true;
    }

public:
    // 是否可以得到MST 
    bool canGenerateMST() {
        if (!computed) MSTPath();
        return mstExists;
    }

    // 返回MST权重之和
    int sumOfMSTValues() {
        if (!computed) MSTPath();
        return mstExists ? sum : -1;
    }

    void printMST() {
        if (!computed) MSTPath();

        if (!mstExists) {
            cout << "无法生成最小生成树" << endl;
            return;
        }

        cout << "生成最小生成树: " << endl;
        for (Edge& edge: mstEdges) {
            cout << edge.a << " - " << edge.b << " (权重: " << edge.val << ")" << endl;
        }
    }
};


int main(int argc, char const* argv[]) {
    int v, e;
    int a, b, val;
    cin >> v >> e;

    vector<Edge> edges;
    for (int i = 0; i < e; ++i) {
        cin >> a >> b >> val;
        edges.push_back({a, b, val});
    }

    KruskalMST* kmst = new KruskalMST(v, edges);
    
    // 先检查是否能生成MST
    if (kmst->canGenerateMST()) {
        kmst->printMST();
        cout << "MST权重和: " << kmst->sumOfMSTValues() << endl;
    } 
    else {
        cout << "无法生成最小生成树" << endl;
    }

    delete kmst;
    return 0;
}