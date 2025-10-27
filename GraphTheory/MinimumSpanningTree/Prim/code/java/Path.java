package Prim.code.java;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

/* Prim算法拓展: 打印出最小生成树, 也就是说打印出MST的所有边 */
public class Path {
    public static void main(String[] args) {
        final int MAX_VAL = 10005;
        Scanner sc = new Scanner(System.in);
        int v = sc.nextInt();
        int e = sc.nextInt();
        int[][] grid = new int[v + 1][v + 1];
        for (int i = 0; i <= v; ++i) {
            Arrays.fill(grid[i], MAX_VAL);
        }

        while (e-- > 0) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int val = sc.nextInt();
            grid[a][b] = val;
            grid[b][a] = val; 
        }
        sc.close();

        PrimMST pmst = new PrimMST(MAX_VAL, v, grid);

        // 先检查是否能生成MST
        if (pmst.canGenerateMST()) {
            pmst.printMST();
           System.out.println("MST权重和: " + pmst.sumOfMSTValues());
        } 
        else {
            System.out.println("无法生成最小生成树");;
        }
    }
}

// 将Prim算法封装成一个类, 可以返回MST的权重和, 还有打印MST
// 为了使代码更加健壮, 增加判断是否生成了MST的代码
class PrimMST {
    private int v;
    private int sum;
    private boolean mstExists;
    private boolean computed;

    private final int MAX_VAL;
    private boolean[] isInTree;
    private int[] minDist;
    private int[] parent;       // 父顶点数组, parent[i] = j表示顶点i的父节点是顶点j
    private int[][] grid;

    public PrimMST(int MAX_VAL, int v, int[][] grid) {
        this.MAX_VAL = MAX_VAL;
        this.v = v;
        this.sum = 0;
        this.computed = false;
        this.mstExists = false;
        this.grid = grid;

        isInTree = new boolean[this.v + 1];

        minDist = new int[this.v + 1];
        Arrays.fill(minDist, this.MAX_VAL);
        parent = new int[v + 1];
        Arrays.fill(parent, -1);
    }

    // 用 BFS 检查图的连通性, 也可以统计MST中的节点数量
    private boolean isGraphConnected() {
        int count = 0;
        int root = 1;
        boolean[] visited = new boolean[v + 1];
        
        Queue<Integer> que = new LinkedList<>();
        que.add(root);
        visited[root] = true;
        while (!que.isEmpty()) {
            int cur =  que.poll();    // Java中的poll()方法移除并返回队首元素
            count++;
            // 将还没有访问过并且与cur相连的边入队
            for (int j = 1; j <= v; ++j) {
                if (!visited[j] && grid[cur][j] < MAX_VAL) {
                    que.add(j);     // 元素入队
                    visited[j] = true;
                }
            }
        }

        return count == v;
    }

    private void MSTPath() {
        if (this.computed) return;

        // 检查图是否连通
        if (!isGraphConnected()) {
            mstExists = false;
            computed = true;
            return;
        }

        minDist[1] = 0;
        // 循环 v - 1次, 构建 v - 1 条边
        for (int i = 1; i < this.v; ++i) {
            // Prim算法第 1 步: 找到一个未加入 MST 且权重最小的顶点
            int cur = -1;
            int minVal = Integer.MAX_VALUE;
            for (int j = 1; j <= v; ++j) {
                if (!isInTree[j] && minDist[j] < minVal) {
                    cur = j;
                    minVal = minDist[j];
                }
            }

            // 如果找不到合适的顶点, 说明图不连通
            if (cur == -1) {
                mstExists = false;
                computed = true;
                return;
            }

            // Prim算法第 2 步: 把已找到的顶点 cur 加入到 MST 中
            isInTree[cur] = true;

            // Prim算法第 3 步: 更新minDist数组, 只更新不在 MST 中且与 cur 相连的
            for (int j = 1; j <= v; ++j) {
                if (!isInTree[j] && grid[cur][j] < minDist[j]) {
                    minDist[j] = grid[cur][j];
                    parent[j] = cur;
                }
            }
        }

        for (int i = 1; i <= v; ++i) {
            // 有顶点没有加入到MST中
            if (i != 1 && minDist[i] == MAX_VAL) {
                computed = true;
                mstExists = false;
                return;
            }
            sum += minDist[i];
        }
        computed = true;
        mstExists = true;
    }

    // 检查是否能生成MST
    public boolean canGenerateMST() {
        if (!computed) MSTPath();
        return mstExists;
    }

    public int sumOfMSTValues() {
        if (!computed) MSTPath();
        // 如果不能生成MST, 返回-1;
        return mstExists ? sum : -1;
    }

    // 打印 MST
    public void printMST() {
        if (!computed) MSTPath();        
        
        if (!mstExists) {
            System.out.println("无法生成最小生成树, 图不连通");
            return;
        }
        
        System.out.println("最小生成树的边：");
        for (int i = 2; i <= v; ++i) {  // 从2开始，因为顶点1没有父节点
            if (parent[i] != -1) {
                // cout << parent[i] << " - " << i << " (权重: " << grid[parent[i]][i] << ")" << endl;
                System.out.println(parent[i] + " - " + i + " (权重: " + grid[parent[i]][i] + ")");
            }
        }
    }

    // 获取MST的边
    public List<int[]> getMSTEdges() {
        if (!computed) MSTPath();
        
        List<int[]> edges = new ArrayList<>();
        if (mstExists) {
            for (int i = 2; i <= v; ++i) {
                if (parent[i] != -1) {
                    edges.add(new int[]{parent[i], i});
                }
            }
        }
        return edges;
    }
}