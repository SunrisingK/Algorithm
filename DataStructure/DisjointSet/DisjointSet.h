#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <algorithm>
#include <vector>

class DisjointSet {
public:
    DisjointSet(int n) {
        p.resize(1 + n);
        for (int i = 1; i <= n; ++i) {
            p[i] = i;
        }
        count.resize(1 + n, 1);
    }

    int find(int x) {
        if (x != p[x]) {
            p[x] = find(p[x]);  // 路径压缩
        }
        return p[x];
    }

    // 快速判断两个点 x 和 y 是否在同一个集合里
    bool isInSame(int x, int y) {
        return find(x) == find(y);
    }    

    // 把两个点 x 和 y 加入到同一个集合里
    void merge(int x, int y) {
        int px = find(x), py = find(y);
        if (px != py) {
            if (count[px] < count[py]) {
                std::swap(px, py);
            }
            count[px] += count[py];
            p[py] = px;
        }
    }
private:
    std::vector<int> p;          // 节点所在集合的根节点
    std::vector<int> count;      // 节点所在集合的元素数量
};

#endif