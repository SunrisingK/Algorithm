[题目链接](https://leetcode.cn/problems/maximum-average-subarray-i/description/)

给你一个由 `n` 个元素组成的整数数组 `nums` 和一个整数 `k`

请你找出平均数最大且 **长度为 `k`** 的连续子数组，并输出该最大平均数

任何误差小于 `10<sup>-5</sup>` 的答案都将被视为正确答案

**示例 1：**

<pre><strong>输入：</strong>nums = [1,12,-5,-6,50,3], k = 4
<strong>输出：</strong>12.75
<strong>解释：</strong>最大平均数 (12-5-6+50)/4 = 51/4 = 12.75
</pre>

**示例 2：**

<pre><strong>输入：</strong>nums = [5], k = 1
<strong>输出：</strong>5.00000
</pre>

**提示：**

* `n == nums.length`
* `1 <= k <= n <= 10^5`
* `-10^4 <= nums[i] <= 10^4`
