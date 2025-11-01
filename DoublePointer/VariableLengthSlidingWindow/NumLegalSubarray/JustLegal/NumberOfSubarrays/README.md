[题目链接](https://leetcode.cn/problems/count-number-of-nice-subarrays/description/)

给你一个整数数组 `nums` 和一个整数 `k`。如果某个连续子数组中恰好有 `k` 个奇数数字，我们就认为这个子数组是「 **优美子数组** 」。

请返回这个数组中 **「优美子数组」** 的数目。

**示例 1：**

<pre><strong>输入：</strong>nums = [1,1,2,1,1], k = 3
<strong>输出：</strong>2
<strong>解释：</strong>包含 3 个奇数的子数组是 [1,1,2,1] 和 [1,2,1,1] 。
</pre>

**示例 2：**

<pre><strong>输入：</strong>nums = [2,4,6], k = 1
<strong>输出：</strong>0
<strong>解释：</strong>数列中不包含任何奇数，所以不存在优美子数组。
</pre>

**示例 3：**

<pre><strong>输入：</strong>nums = [2,2,2,1,2,2,1,2,2,2], k = 2
<strong>输出：</strong>16
</pre>

**提示：**

* `1 <= nums.length <= 50000`
* `1 <= nums[i] <= 10^5`
* `1 <= k <= nums.length`
