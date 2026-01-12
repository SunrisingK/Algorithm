#include <iostream>
#include <vector>
#include <deque>
using namespace std;


class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ans;
        // 单调递减队列, 维护队首是最大元素
        deque<int> que;
        int n = nums.size();
        for (int right = 0; right < n; ++right) {
            // 淘汰队尾能力不足的元素
            while (!que.empty() && nums[que.back()] <= nums[right]) {
                que.pop_back();
            }
            // 经过惨烈的竞争, right干掉了不如你的末尾老登, 成为了新的吊车尾
            que.push_back(right);

            // 计算窗口左端点
            int left = right - k + 1;
            // 新的左端点已经超过了队首, 表示窗口该移动了, 需要淘汰队首元素
            if (left > que.front()) {
                que.pop_front();
            }

            // 窗口左端点合法, 就可以取队首元素了
            if (left >= 0) {
                ans.push_back(nums[que.front()]);
            }
        }
        return ans;
    }
};


int main(int argc, char const* argv[]) {
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    Solution s;
    vector<int> ans = s.maxSlidingWindow(nums, k);
    for (int& x: ans) cout << x << " ";    
    return 0;
}