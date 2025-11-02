package DoublePointer.VariableLengthSlidingWindow.NumLegalSubarray.JustLegal.NumSubarraysWithSum.code.java;

import java.util.HashMap;
import java.util.Map;

class OptimalSolution {
    public int numSubarraysWithSum(int[] nums, int goal) {
        // 前缀和 + 哈希表写法
        // i 和 j 表示长度, i < j
        // prefix[j] - prefix[i] = goal;
        int n = nums.length;
        int[] prefix = new int[n + 1];
        for (int i = 1; i <= n; ++i) {
            prefix[i] = prefix[i - 1] + nums[i - 1];
        }
        Map<Integer, Integer> mp = new HashMap<>();
        int ans = 0;
        // 枚举长度, i 表示当前的长度
        for (int i = 0; i <= n; ++i) {
            // 在哈希表中查找 "当前的前缀和 - 目标值" 是否存在记录
            if (mp.containsKey(prefix[i] - goal)) {
                ans += mp.get(prefix[i] - goal);
            }
            // 使用 getOrDefault 避免空指针
            int val = mp.getOrDefault(prefix[i], 0) + 1;
            mp.put(prefix[i], val);
        }
        return ans;
    }
}

public class Optimal {
    public static void main(String[] args) {
        int[] nums = {1, 0, 1, 0, 1};
        OptimalSolution s = new OptimalSolution();
        int goal = 2;
        System.out.println(s.numSubarraysWithSum(nums, goal));
    }
}
