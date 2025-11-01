[题目链接](https://kamacoder.com/problempage.php?pid=1179)

题目描述

给定一个包含 n 个节点的无向图中，节点编号从 1 到 n （含 1 和 n ）。

你的任务是判断是否有一条从节点 source 出发到节点 destination 的路径存在。

输入描述

第一行包含两个正整数 N 和 M，N 代表节点的个数，M 代表边的个数。

后续 M 行，每行两个正整数 s 和 t，代表从节点 s 与节点 t 之间有一条边。

最后一行包含两个正整数，代表起始节点 source 和目标节点 destination。

输出描述

输出一个整数，代表是否存在从节点 source 到节点 destination 的路径。如果存在，输出 1；否则，输出 0。

输入示例

```
5 4
1 2
1 3
2 4
3 4
1 4
```

输出示例

```
1
```

数据范围：

```
1 <= M, N <= 100
```

![提示信息](https://kamacoder.com/upload/kamacoder.com/image/20240416/20240416112946_20453.png)
