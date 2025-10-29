[题目链接](https://leetcode.cn/problems/number-of-substrings-containing-all-three-characters/description/)

给你一个字符串 `s` ，它只包含三种字符 a, b 和 c

请你返回 a，b 和 c 都 **至少**出现过一次的子字符串数目。

**示例 1：**

<pre><strong>输入：</strong>s = "abcabc"
<strong>输出：</strong>10
<strong>解释：</strong>包含 a，b 和 c 各至少一次的子字符串为<em> "</em>abc<em>", "</em>abca<em>", "</em>abcab<em>", "</em>abcabc<em>", "</em>bca<em>", "</em>bcab<em>", "</em>bcabc<em>", "</em>cab<em>", "</em>cabc<em>" </em>和<em> "</em>abc<em>" </em>(<strong>相同</strong><strong>字符串算多次</strong>)<em>。</em>
</pre>

**示例 2：**

<pre><strong>输入：</strong>s = "aaacb"
<strong>输出：</strong>3
<strong>解释：</strong>包含 a，b 和 c 各至少一次的子字符串为<em> "</em>aaacb<em>", "</em>aacb<em>" </em>和<em> "</em>acb<em>" 。</em>
</pre>

**示例 3：**

<pre><strong>输入：</strong>s = "abc"
<strong>输出：</strong>1
</pre>

**提示：**

* `3 <= s.length <= 5 x 10^4`
* `s` 只包含字符 a，b 和 c 。
