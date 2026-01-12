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
            sum += nums[right] % 2;
            while (left <= right && sum >= k) {
                // 收缩窗口
                sum -= nums[left] % 2;
                ++left;
            }
            ans += left;
        }
        return ans;
    }

public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        return count(nums, k) - count(nums, k + 1);
    }
};

int main(int argc, char const* argv[]) {
    vector<int> nums = {1, 1, 2, 1, 1};
    int k = 3;
    Solution s;
    cout << s.numberOfSubarrays(nums, k);
    return 0;
}
