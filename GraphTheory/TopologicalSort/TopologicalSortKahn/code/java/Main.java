package GraphTheory.TopologicalSort.TopologicalSortKahn.code.java;

import java.util.Scanner;
import java.util.Queue;
import java.util.HashMap;
import java.util.Map;
import java.util.List;
import java.util.ArrayList;  
import java.util.LinkedList;


class TopologicalSortKahn {
    public Map<Integer, List<Integer>> grid;
    public int[] InDegree;

    private int n;
    private boolean computed;
    private boolean hasCycle;
    private List<Integer> sequence;

    public TopologicalSortKahn(int n) {
        this.n = n;
        this.InDegree = new int[n];  // 顶点编号 0~n-1，入度数组长度为n
        this.sequence = new LinkedList<>();
        this.grid = new HashMap<>();
        this.computed = false;
        this.hasCycle = false;

        // 为每个顶点初始化空的邻接表，避免get(u)返回null
        for (int i = 0; i < n; i++) {
            grid.put(i, new ArrayList<>());
        }
    }

    private void topologicalSort(Map<Integer, List<Integer>> grid) {
        Queue<Integer> que = new LinkedList<>();
        for (int i = 0; i < n; ++i) {
            if (InDegree[i] == 0) {
                que.offer(i);
            }
        }

        while (!que.isEmpty()) {
            int u = que.poll();
            sequence.add(u);
            // 更新入度数组, 只更新与 u 相连的顶点
            List<Integer> vertices = grid.get(u);
            for (int v : vertices) {
                InDegree[v]--;
                if (InDegree[v] == 0) {
                    que.offer(v);
                }
            }
        }
        computed = true;
        hasCycle = (sequence.size() < n);  // 序列长度不足则有环
    }

    public void printTopologicalSortSequence(Map<Integer, List<Integer>> grid) {
        if (!computed) {
            topologicalSort(grid);
        }

        if (hasCycle) {
            System.out.println("图中有环, 不存在拓扑序列");
        } else {
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
        int n = sc.nextInt();  // 顶点数（0~n-1）
        int m = sc.nextInt();  // 边数
        
        TopologicalSortKahn kahn = new TopologicalSortKahn(n);

        while (m-- > 0) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            kahn.InDegree[v]++;
            kahn.grid.get(u).add(v);  // 此时grid.get(u)已初始化，不会为null
        }

        // 调用打印方法，执行拓扑排序并输出结果
        kahn.printTopologicalSortSequence(kahn.grid);

        sc.close();
    }
}