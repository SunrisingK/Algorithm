package DoublePointer.ConstLengthSlidingWindow.MaxVowels.code.java;

class Solution {
    private int check(char c) {
        boolean b = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
        return b ? 1 : 0; 
    }
    public int maxVowels(String s, int k) {
        // 返回长度为 k 的窗口内的元音字母数量最大值
        // 这里用2个指针表示窗口
        int ans = 0;
        int count = 0;
        for (int right = 0; right < s.length(); ++right) {
            // 第 1 步: 右端点进入窗口, 更新统计量, 一般情况下此时窗口长度为 k
            count += check(s.charAt(right));
            
            // 计算左端点
            int left = right - k + 1;
            // 尚未形成长度为 k 的窗口
            if (left < 0) continue;

            // 第 2 步: 更新答案
            ans = Math.max(ans, count);
            if (ans == k) break;    // 窗口内全是元音字母, 就是最大值, 直接退出循环

            // 第 3 步: 左端点离开窗口, 更新统计量, 此时窗口长度为 k - 1
            count -= check(s.charAt(left));
        }
        return ans;
    }
}

public class Main {
    public static void main(String[] args) {
        String s = "abciiidef";
        int k = 3;
        Solution solution = new Solution();
        System.out.println(solution.maxVowels(s, k)); 
    }
}
