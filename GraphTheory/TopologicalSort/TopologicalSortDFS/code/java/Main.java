package GraphTheory.TopologicalSort.TopologicalSortDFS.code.java;

import java.util.Scanner;
import java.util.Stack;
import java.util.HashMap;
import java.util.Map;
import java.util.List;
import java.util.ArrayList;


class TopologicalSortDFS {
    private int n;
    private boolean computed;
    private boolean hasCycle;

    private boolean[] finished;
    private boolean[] visited;
    
    private List<Integer> sequence;
    private Stack<Integer> stk;

    public TopologicalSortDFS(int n) {
        this.n = n;
        this.computed = false;
        this.hasCycle = false;
        
        this.finished = new boolean[n];
        this.visited = new boolean[n];

        this.sequence = new ArrayList<>();
        this.stk = new Stack<>();
    }

    // 后序DFS 
    private void dfs(int u, Map<Integer, List<Integer>> grid) {
        // 处理掉顶点 u 以及其后续顶点的所有依赖关系, 得到一个序列
        visited[u] = true;      // 设置顶点 u 已访问, 此后不会再访问顶点u, visited[u] 不用回溯
        finished[u] = false;    // 设置顶点 u 在递归栈里, 表示顶点 u 的后续依赖还没处理完 

        List<Integer> vertices = grid.getOrDefault(u, new ArrayList<>());
        for (int v : vertices) {
            if (!visited[v]) {
                // dfs()过程中涉及修改 hasCycle 的代码
                dfs(v, grid);
                // 每进行一次dfs(), 都可以检查 hasCycle
                if (hasCycle) return;
            }
            else if (!finished[v]) {
                // 如果遍历到了递归栈中的顶点, 就说明存在环
                hasCycle = true;
                return;
            }
        }

        finished[u] = true;     // 顶点 u 已经处理完了 
        stk.push(u);            // 把顶点 u 加入到结果栈里
    } 

    private void topologicalSort(Map<Integer, List<Integer>> grid) {
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(i, grid);
                if (hasCycle) {
                    computed = true; 
                    return;
                }
            }
        }

        while (!stk.isEmpty()) {
            sequence.add(stk.pop());
        }

        this.computed = true;
        this.hasCycle = (sequence.size() < n);
    }

    public void printTopologicalSortSequence(Map<Integer, List<Integer>> grid) {
        if (!computed) topologicalSort(grid);
        

        if (hasCycle) {
            System.out.println("图中有环, 不存在拓扑序列");
        } 
        else {
            for (int i = 0; i < sequence.size(); ++i) {
                if (i > 0) System.out.print(" -> ");
                System.out.print(sequence.get(i));
            }
            System.out.println();
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();

        TopologicalSortDFS topoDFS = new TopologicalSortDFS(n);

        Map<Integer, List<Integer>> grid = new HashMap<>();
        // 为每个顶点初始化空的邻接表，避免get(u)返回null
        for (int i = 0; i < n; i++) {
            grid.put(i, new ArrayList<>());
        }
        
        while (m-- > 0) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            grid.get(u).add(v);
        }

        topoDFS.printTopologicalSortSequence(grid);

        sc.close();
    }
}
