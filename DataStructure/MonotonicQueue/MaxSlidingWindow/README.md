[题目链接](https://leetcode.cn/problems/sliding-window-maximum/description/)


给你一个整数数组 `nums`，有一个大小为 `k` 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 `k` 个数字。滑动窗口每次只向右移动一位。

返回 滑动窗口中的最大值

**示例 1：**

<pre><b>输入：</b>nums = [1,3,-1,-3,5,3,6,7], k = 3
<b>输出：</b>[3,3,5,5,6,7]
<b>解释：</b>
滑动窗口的位置                          最大值
[1  3  -1] -3  5  3  6  7                       <strong>3</strong>
 1 [3  -1  -3] 5  3  6  7                       <strong>3</strong>
 1  3 [-1  -3  5] 3  6  7                       <strong> 5</strong>
 1  3  -1 [-3  5  3] 6  7                       <strong>5</strong>
 1  3  -1  -3 [5  3  6] 7                       <strong>6</strong>
 1  3  -1  -3  5 [3  6  7]                      <strong>7</strong>
</pre>

**示例 2：**

<pre><b>输入：</b>nums = [1], k = 1
<b>输出：</b>[1]
</pre>

**提示：**

* `1 <= nums.length <= 10^5`
* `-10^4 <= nums[i] <= 10^4`
* `1 <= k <= nums.length`
