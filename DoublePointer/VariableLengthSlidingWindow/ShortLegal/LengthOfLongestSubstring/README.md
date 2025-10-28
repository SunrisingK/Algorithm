[题目链接](https://leetcode.cn/problems/longest-substring-without-repeating-characters/description/)

给定一个字符串 `s` ，请你找出其中不含有重复字符的 **最长子串** 的长度。

**示例 1:**

<pre><strong>输入: </strong>s = "abcabcbb"
<strong>输出: </strong>3 
<strong>解释:</strong> 因为无重复字符的最长子串是 "abc"，所以其长度为 3。注意 "bca" 和 "cab" 也是正确答案。
</pre>

**示例 2:**

<pre><strong>输入: </strong>s = "bbbbb"
<strong>输出: </strong>1
<strong>解释: </strong>因为无重复字符的最长子串是 "b"，所以其长度为 1。
</pre>

**示例 3:**

<pre><strong>输入: </strong>s = "pwwkew"
<strong>输出: </strong>3
<strong>解释: </strong>因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 <strong>子串 </strong>的长度，"pwke" 是一个<em>子序列，</em>不是子串。
</pre>

**提示：**

* `0 <= s.length <= 5 * 10^4`
* `s` 由英文字母、数字、符号和空格组成
