#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
    int count(vector<int>& nums, int k) {
        int ans = 0; 
        int sum = 0;
        // 越长越合法
        int left = 0;
        for (int right = 0; right < nums.size(); ++right) {
            sum += nums[right];
            while (left <= right && sum >= k) {
                // 收缩窗口
                sum -= nums[left];
                ++left;
            }
            ans += left;
        }
        return ans;
    }

public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        // 不定长滑动窗口写法
        // count(nums, k) 返回元素和 >= k 的子数组数目
        // ans = count(nums, goal) - count(nums, goal + 1)
        return count(nums, goal) - count(nums, goal + 1);
    }
};

int main(int argc, char const* argv[]) {
    vector<int> nums = {1, 0, 1, 0, 1};
    int goal = 2;
    Solution s;
    cout << s.numSubarraysWithSum(nums, goal);
    return 0;
}
