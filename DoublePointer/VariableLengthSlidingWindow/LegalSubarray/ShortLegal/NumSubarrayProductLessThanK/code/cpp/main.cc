#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k == 0) return 0;

        // 题目中的数组元素都是正整数, 子数组长度越短越合法
        // [left, right]是合法的, 那么窗口里的所有子数组都是合法的
        // 但是有一点需要注意, 这些子数组都需要以right结尾
        // [right, right], [right - 1, right], [right - 2, right], ... , [left, right]
        int ans = 0; 
        int left = 0;
        int product = 1;
        // 枚举右维护左
        for (int right = 0; right < nums.size(); ++right) {
            product *= nums[right];
            while (left <= right && product >= k) {
                // 缩小窗口找到合法解
                product /= nums[left];
                ++left;
            }
            ans += right - left + 1;
        }
        return ans;
    }
};

int main(int argc, char const* argv[]) {
    vector<int> nums = {2, 3, 1, 2, 4, 3};
    int k = 7;
    Solution s;
    cout << s.numSubarrayProductLessThanK(nums, k);
    return 0;
}