#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        // 前缀和 + 哈希表写法, 最佳写法
        // i 和 j 表示长度, i < j
        // prefix[j] - prefix[i] = goal;
        int n = nums.size();
        vector<int> prefix(1 + n);
        for (int i = 1; i <= n; ++i) {
            prefix[i] = prefix[i - 1] + nums[i - 1];
        }
        int ans = 0;
        unordered_map<int, int> mp;
        // 枚举长度, i 表示当前的长度
        for (int i = 0; i <= n; ++i) {
            // 在哈希表中查找 "当前的前缀和 - 目标值" 是否存在记录
            if (mp.count(prefix[i] - goal)) {
                ans += mp[prefix[i] - goal];
            }
            mp[prefix[i]]++;
        }
        return ans;
    }
};

int main(int argc, char const* argv[]) {
    vector<int> nums = {1, 0, 1, 0, 1};
    int goal = 2;
    Solution s;
    cout << s.numSubarraysWithSum(nums, goal);
    return 0;
}
