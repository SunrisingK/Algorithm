[题目链接](https://leetcode.cn/problems/binary-subarrays-with-sum/description/)

给你一个二元数组 `nums` ，和一个整数 `goal` ，请你统计并返回有多少个和为 `goal` 的非空子数组。

**子数组** 是数组的一段连续部分。

**示例 1：**

<pre><strong>输入：</strong>nums = [1,0,1,0,1], goal = 2
<strong>输出：</strong>4
<strong>解释：</strong>
有 4 个满足题目要求的子数组：[1,0,1]、[1,0,1,0]、[0,1,0,1]、[1,0,1]
</pre>

**示例 2：**

<pre><strong>输入：</strong>nums = [0,0,0,0,0], goal = 0
<strong>输出：</strong>15
</pre>

**提示：**

* `1 <= nums.length <= 3 * 10^4`
* `nums[i]` 不是 `0` 就是 `1`
* `0 <= goal <= nums.length`
