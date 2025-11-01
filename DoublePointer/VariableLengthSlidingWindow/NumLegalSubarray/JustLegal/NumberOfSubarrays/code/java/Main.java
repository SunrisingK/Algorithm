class Solution {
    private int count(int[] nums, int k) {
        int ans = 0;
        int sum = 0;
        int left = 0;
        for (int right = 0; right < nums.length; ++right) {
            sum += (nums[right] % 2);
            while (left <= right && sum >= k) {
                sum -= (nums[left] % 2);
                ++left;
            }
            ans += left;
        }
        return ans;
    }

    public int numberOfSubarrays(int[] nums, int k) {
        return count(nums, k) - count(nums, k + 1);
    }
}

public class Main {
    public static void main(String[] args) {
        int[] nums = {1, 1, 2, 1, 1};
        int k = 3;
        Solution s = new Solution();
        System.out.println(s.numberOfSubarrays(nums, k));
    }
}
