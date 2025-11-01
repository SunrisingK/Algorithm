#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int numberOfSubarrays(vector<int> nums, int k) {
        // 这题最佳做法是利用前缀数组统计奇数元素出现的次数
        // 前缀和 + 哈希表
        int n = nums.size();
        vector<int> prefix(1 + n);

        for (int i = 1; i <= n; ++i) {
            prefix[i] = prefix[i - 1] + nums[i - 1] % 2;
        }

        // prefix[j] - prefix[i] = k;
        vector<int>mp(1 + n);
        int ans = 0;
        for (int i = 0; i <= n; ++i) {
            int key = prefix[i] - k;
            if (key >= 0 && mp[key] > 0) {
                ans += mp[key];
            }
            mp[prefix[i]]++;
        }
        return ans;
    }
};

int main(int argc, char const* argv[]) {
    vector<int> nums = {1, 1, 2, 1, 1};
    int k = 3;
    Solution s;
    cout << s.numberOfSubarrays(nums, k);
    return 0;
}
