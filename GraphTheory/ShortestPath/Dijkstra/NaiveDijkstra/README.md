#### 朴素版Dijkstra 算法

**核心思想**：贪心算法。从源点开始，每次选择**当前已知最短距离最小**的顶点，然后松弛（更新）其所有邻居的距离

**前提条件**：图中**不能有负权边**

**时间复杂度**：O(v²)，v表示顶点个数

**空间复杂度**：O(v²)，v表示顶点个数

**算法步骤**：

1. 选择距离起点最近且未被访问过的顶点
2. 将该顶点标记为被访问过
3. 更新起点到剩余未被访问过的顶点的距离，朴素版算法使用minDist[]数组存储距离

Dijkstra算法基于贪心算法，最终的算法结果可以返回起点到其他任意点的最短距离

#### 朴素版Dijkstra算法和Prim算法的区别

二者的区别在于minDist[] 数组的含义

* Prim算法中的 minDist[i] 表示顶点 i 到MST的最短距离，仅需顶点 i 与顶点 cur 相连即可视为顶点 i 已经加入到了 MST 中

```cpp
// Prim算法更新 minDist[] 数组
// 只更新不在MST中且与cur相连的顶点
// 顶点 j 通过与顶点 cur 相连更新了到MST的最短距离
for (int j = 1; j <= v; ++j) {
    if (!isIntree[j] && grid[cur][j] < minDist[j]) {
  	minDist[j] = grid[cur][j];
    }
}

```

* Dijkstra算法中的 minDist[i] 表示顶点 i 到起点的最短距离，顶点 i 需要与顶点 cur 相连，并提供cur到起点的最短距离更新自己到起点的最短距离

```cpp
// 朴素版Dijkstra算法更新 minDist[] 数组
// 只更新没有被访问过且与 cur 相连的顶点
// 顶点 v 通过与顶点 cur 相连更新了到MST的最短距离
for (int v = 1; v <= n; ++v) {
    if (!visited[v] && grid[cur][j] != MAX_VAL && minDist[cur] + grid[cur][v] < minDist[v]) {
        minDist[v] = minDist[cur] + grid[cur][v]; 
    }
}
```
