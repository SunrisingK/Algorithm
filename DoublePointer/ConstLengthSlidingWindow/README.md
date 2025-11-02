**定长滑窗套路**

窗口右端点在 i 时，由于窗口长度为 k，所以窗口左端点为 **i−k+1**

解题套路总结成三步：入-更新-出。

1. 入：下标为 i 的元素进入窗口，更新相关统计量。如果窗口左端点 i−k+1<0，则尚未形成第一个窗口，重复第一步
2. 更新：更新答案。一般是更新最大值/最小值
3. 出：下标为 i−k+1 的元素离开窗口，更新相关统计量，为下一个循环做准备

以上三步适用于所有定长滑窗题目

引用自[灵茶山艾府](https://leetcode.cn/problems/maximum-number-of-vowels-in-a-substring-of-given-length/solutions/2809359/tao-lu-jiao-ni-jie-jue-ding-chang-hua-ch-fzfo/)
