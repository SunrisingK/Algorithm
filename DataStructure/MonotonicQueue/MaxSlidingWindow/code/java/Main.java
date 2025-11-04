package DataStructure.MonotonicQueue.MaxSlidingWindow.code.java;

import java.util.ArrayDeque;
import java.util.Deque;

class Solution {
    public int[] maxSlidingWindow(int[] nums, int k) {
        int n = nums.length;
        // 一共有 n - k + 1 个窗口
        int[] ans = new int[n - k + 1];
        // 单调递减队列, 维护队首是最大元素的下标
        Deque<Integer> que = new ArrayDeque<>();
        
        for (int right = 0; right < n; ++right) {
            // 淘汰队尾能力不足的元素
            while (!que.isEmpty() && nums[que.getLast()] <= nums[right]) {
                que.removeLast();
            }
            // 经过惨烈的竞争, right干掉了不如你的末尾老登, 成为了新的吊车尾
            que.offerLast(right);

            // 计算窗口左端点
            int left = right - k + 1;
            // 新的左端点已经超过了队首, 表示窗口该移动了, 需要淘汰队首元素
            if (left > que.getFirst()) {
                que.removeFirst();
            }

            // 窗口左端点合法, 就可以取队首元素了
            if (left >= 0) {
                ans[left] = nums[que.getFirst()];
            }
        }
        return ans;
    }
}

public class Main {
    public static void main(String[] args) {
        int[] nums = {1, 3, -1, -3, 5, 3, 6, 7};
        int k = 3;
        Solution solution = new Solution();
        int[] ans = solution.maxSlidingWindow(nums, k);
        for (int x: ans) System.out.print(x + " ");
    }
}
