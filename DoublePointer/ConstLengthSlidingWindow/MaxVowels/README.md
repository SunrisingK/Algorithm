[题目链接](https://leetcode.cn/problems/maximum-number-of-vowels-in-a-substring-of-given-length/)

给你字符串 `s` 和整数 `k` 。

请返回字符串 `s` 中长度为 `k` 的单个子字符串中可能包含的最大元音字母数。

英文中的 **元音字母 **为（`a`, `e`, `i`, `o`, `u`）。

**示例 1：**

<pre><strong>输入：</strong>s = "abciiidef", k = 3
<strong>输出：</strong>3
<strong>解释：</strong>子字符串 "iii" 包含 3 个元音字母。
</pre>

**示例 2：**

<pre><strong>输入：</strong>s = "aeiou", k = 2
<strong>输出：</strong>2
<strong>解释：</strong>任意长度为 2 的子字符串都包含 2 个元音字母。
</pre>

**示例 3：**

<pre><strong>输入：</strong>s = "leetcode", k = 3
<strong>输出：</strong>2
<strong>解释：</strong>"lee"、"eet" 和 "ode" 都包含 2 个元音字母。
</pre>

**示例 4：**

<pre><strong>输入：</strong>s = "rhythms", k = 4
<strong>输出：</strong>0
<strong>解释：</strong>字符串 s 中不含任何元音字母。
</pre>

**示例 5：**

<pre><strong>输入：</strong>s = "tryhard", k = 4
<strong>输出：</strong>1
</pre>

**提示：**

* `1 <= s.length <= 10^5`
* `s` 由小写英文字母组成
* `1 <= k <= s.length`
