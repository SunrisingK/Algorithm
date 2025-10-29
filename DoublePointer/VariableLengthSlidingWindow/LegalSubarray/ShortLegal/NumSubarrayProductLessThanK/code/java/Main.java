package DoublePointer.VariableLengthSlidingWindow.LegalSubarray.ShortLegal.NumSubarrayProductLessThanK.code.java;

class Solution {
    public int numSubarrayProductLessThanK(int[] nums, int k) {
        if (k == 0) return 0;

        // 题目中的数组元素都是正整数, 子数组长度越短越合法
        // [left, right]是合法的, 那么窗口里的所有子数组都是合法的
        // 但是有一点需要注意, 这些子数组都需要以right结尾
        int ans = 0;
        int left = 0;
        int product = 1;
        // 枚举右维护左
        for (int right = 0; right < nums.length; ++right) {
            product *= nums[right];
            while (left <= right && product >= k) {
                // 收缩窗口直到找到合法解
                product /= nums[left];
                ++left;
            }
            ans += right - left + 1;
        }
        return ans;
    }
}

public class Main {
    public static void main(String[] args) {
        int[] nums = {10, 5, 2, 6};
        int k = 100;
        Solution s = new Solution();
        System.out.println(s.numSubarrayProductLessThanK(nums, k));
    }    
}
