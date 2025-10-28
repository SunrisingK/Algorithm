package DoublePointer.VariableLengthSlidingWindow.ShortLegal.LengthOfLongestSubstring.code.java;

public class Main {
    public static void main(String[] args) {
        String s = "abcabcbb";
        Solution solution = new Solution();
        System.out.println(solution.lengthOfLongestSubstring(s));
    }
}

class Solution {
    public int lengthOfLongestSubstring(String s) {
        int ans = 0;
        char[] s_ = s.toCharArray(); // 转换成 char[] 加快效率（忽略带来的空间消耗）
        
        boolean[] st = new boolean[128];

        int left = 0;
        // 枚举右维护左
        for (int right = 0; right < s_.length; ++right) {
            char c = s_[right];  // 待加入窗口的字符

            // 用while()循坏确保窗口内没有待加入字符
            while (left <= right && st[c]) {
                st[s_[left]] = false;
                left++;
            }
            
            // 加入窗口
            st[c] = true;
            // 更新答案
            ans = Math.max(ans, right - left + 1);
        }
        return ans;
    }
}
