[题目链接](https://leetcode.cn/problems/edit-distance/)


给你两个单词 `word1` 和 `word2`， *请返回将 `word1` 转换成 `word2` 所使用的最少操作数*  。

你可以对一个单词进行如下三种操作：

* 插入一个字符
* 删除一个字符
* 替换一个字符

**示例 1：**

<pre><strong>输入：</strong>word1 = "horse", word2 = "ros"
<strong>输出：</strong>3
<strong>解释：</strong>
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')
</pre>

**示例 2：**

<pre><strong>输入：</strong>word1 = "intention", word2 = "execution"
<strong>输出：</strong>5
<strong>解释：</strong>
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')
</pre>

**提示：**

* `0 <= word1.length, word2.length <= 500`
* `word1` 和 `word2` 由小写英文字母组成
