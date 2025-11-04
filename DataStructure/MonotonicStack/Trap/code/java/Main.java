package DataStructure.MonotonicStack.Trap.code.java;

import java.util.Stack;

class Solution {
    public int trap(int[] height) {
        // 计算方法: 横向切割, 利用单调减栈计算雨水面积
        // int mid = stk.pop();
        // {stk.peek(), mid, i}
        Stack<Integer> stk = new Stack<>();
        int n = height.length;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            while (!stk.isEmpty() && height[i] > height[stk.peek()]) {
                int mid = stk.pop();        // 栈顶
                if (!stk.isEmpty()) {
                    int h = Math.min(height[stk.peek()], height[i]) - height[mid];
                    int w = i - stk.peek() - 1;
                    ans += h * w;
                }
            }
            stk.push(i);
        }   
        return ans;     
    }
}

public class Main {
    public static void main(String[] args) {
        int[] height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
        Solution solution = new Solution();
        System.out.println(solution.trap(height));
    }
}
