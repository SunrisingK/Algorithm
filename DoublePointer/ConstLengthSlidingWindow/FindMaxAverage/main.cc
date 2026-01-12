#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    double findMaxAverage(vector<int> nums, int k) {
        int ans = INT_MIN;
        int sum = 0;
        for (int right = 0; right < nums.size(); ++right) {
            // 第 1 步: 右端点进入窗口, 更新统计量, 一般情况下此时窗口长度为 k
            sum += nums[right];

            // 计算左端点
            int left = right - k + 1;
            // 尚未形成长度为 k 的窗口
            if (left < 0) continue;

            // 第 2 步: 更新答案(也可以放在计算left前)
            ans = max(ans, sum);

            // 第 3 步: 左端点离开窗口, 更新统计量, 此时窗口长度为 k - 1
            sum -= nums[left];
        }
        return 1.0 * ans / k;
    }
};

int main(int argc, char const* argv[]) {
    vector<int> nums = {1, 12, -5, -6, 50, 3}; 
    int k = 4;
    Solution solution;
    cout << solution.findMaxAverage(nums, k);
    return 0;
}