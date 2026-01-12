#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        // 数组元素是正整数, 越长的子数组越容易满足题意
        // 求最小长度可以用不定长滑动窗口解决
        int ans = nums.size() + 1; 
        int left = 0;
        int sum = 0;
        // 枚举右维护左
        for (int right = 0; right < nums.size(); ++right) {
            sum += nums[right];
            while (left <= right && sum >= target) {
                // 找到一个合法解就更新答案
                ans = min(ans, right - left + 1);
                // 缩小窗口
                sum -= nums[left];
                ++left;
            }
        }
        return ans == nums.size() + 1 ? 0 : ans;
    }
};

int main(int argc, char const* argv[]) {
    vector<int> nums = {2, 3, 1, 2, 4, 3};
    int target = 7;
    Solution s;
    cout << s.minSubArrayLen(target, nums);
    return 0;
}