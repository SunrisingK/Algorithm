package BinaryAlgorithm.BinaryAnswer.MaxMinimum.MaxPossibleScore.code.java;

import java.util.Arrays;

class Solution {
    public int maxPossibleScore(int[] start, int d) {
        Arrays.sort(start);
        int n = start.length;
        int ans = 0;
        int left = 0; 
        int right = 1 + (d + start[n - 1] - start[0]) / (n - 1);
        // right设置成 start[n - 1] 也可以, 这个可以想到

        // right = 1 + (d + start[n - 1] - start[0]) / (n - 1)
        // d + start[n - 1] - start[0]表示区间的最大跨度
        // 要把区间分成 n 个小区间, 每个小区间之间会有间隔, 一共有 n - 1 个间隔
        // 平均分配的间隔再加 1 就是可能的最大值
        
        while (left <= right) {
            int mid = left +  (right - left) / 2;
            if (check(mid, start, d)) {
                ans = mid;
                // 扩大答案
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return ans;
    }

    private boolean check(int x, int[] start, int d) {
        /*
         * 贪心, 现在问题变成
         * 给定 x , 能否从每个区间各选一个数
         * 使得任意两数之差的大于等于 x (初始数字越小越容易满足这个条件)
         * =====================================================================
         * 选定左端点 s0 作为初始候选数字n0, 候选数字 n1 = s0 + x 范围 [s1, s1 + d]
         * 如果 s0 + x < s1, 那么候选数字设为 s1 是符合要求的(s1 - s0 >= x)
         * 如果 s0 + x >= s1, 那么候选数字设为 s1 是不符合要求的(s1 - s0 <= x)
         * 所以候选数字为 max(s0 + x, s1), 但不能大于区间右端点, 后续候选数字同理可得
        */
        long cur = Long.MIN_VALUE;          // 候选数字
        for (int s: start) {
            cur = Math.max(cur + x, s);     // 候选数字 >= 区间左端点 s
            if (cur > s + d) return false;
        }
        return true;
    }
}

public class Main {
    public static void main(String[] args) {
        int[] start = {6, 0, 3};
        int d = 2;
        Solution solution = new Solution();
        System.out.println(solution.maxPossibleScore(start, d));
    }
}

// [6, 8], [0, 2], [3, 5]
// [0, 2], [3, 5], [6, 8]


// [2, 7], [6, 11], [13, 18], [13, 18]