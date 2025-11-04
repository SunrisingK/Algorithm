package DataStructure.DisjointSet.FindPath.code.java;

import DataStructure.DisjointSet.DisjointSet;
import java.util.Scanner;

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
