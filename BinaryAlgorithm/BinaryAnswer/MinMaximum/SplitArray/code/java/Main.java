package BinaryAlgorithm.BinaryAnswer.MinMaximum.SplitArray.code.java;

import java.util.Arrays;

class Solution {
    // 这一题的数组是非负整数数组, 这是一个很关键的信息
    // 当分割段数越大时, 答案越小, k 取最大值(数组长度)时, 答案为数组元素的最大值
    // 当分割段数越小时, 答案越大, k 取最小值( 1 )时, 答案为数组元素的和
    // 答案具有单调性, 可以用二分答案试一试, 不过难点在于分割数组求和
    public int splitArray(int[] nums, int k) {
        int left = Arrays.stream(nums).max().getAsInt();
        int right = Arrays.stream(nums).sum();
        int ans = 0;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (check(mid, nums, k)) {
                ans = mid;
                // 缩小答案
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return ans;
    }

    private boolean check(int x, int[] nums, int k) {
        // 所有的分段和都小于等于 x 
        int currentSum = 0; // 累加和
        int count = 0;      // count表示分段次数, 这很重要
        // 要想分成 k 段, 需要 k - 1 次分段操作, 需要count < k
        for (int n: nums) {
            currentSum += n;
            // 分段时机
            if (currentSum > x) {
                ++count;
                if (count >= k) return false;
                currentSum = n;
            }
        }
        return true;
    }
}

public class Main {
    public static void main(String[] args) {
        int[] nums = {7, 2, 5, 10, 8};
        int k = 2;
        Solution solution = new Solution();
        System.out.println(solution.splitArray(nums, k));
    }
}
