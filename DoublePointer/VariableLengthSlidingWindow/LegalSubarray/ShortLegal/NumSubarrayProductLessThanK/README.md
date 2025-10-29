[题目链接](https://leetcode.cn/problems/subarray-product-less-than-k/description/)

给你一个整数数组 `nums` 和一个整数 `k` ，请你返回子数组内所有元素的乘积严格小于 `k` 的连续子数组的数目。

**示例 1：**

`<strong>`输入：`</strong>`nums = [10,5,2,6], k = 100
`<strong>`输出：`</strong>`8
`<strong>`解释：`</strong>`8 个乘积小于 100 的子数组分别为：[10]、[5]、[2]、[6]、[10,5]、[5,2]、[2,6]、[5,2,6]。

**示例 2：**

`<strong>`输入：`</strong>`nums = [1,2,3], k = 0
`<strong>`输出：`</strong>`0`</pre>`

**提示:**

* `1 <= nums.length <= 3 * 10^4`
* `1 <= nums[i] <= 1000`
* `0 <= k <= 10^6`
