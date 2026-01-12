#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        // 计算方法: 横向切割, 利用单调减栈计算雨水面积
        // int mid = stk.pop();
        // {stk.peek(), mid, i}
        stack<int> stk;
        int n = height.size();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && height[i] > height[stk.top()]) {
                int mid = stk.top(); stk.pop();
                if (!stk.empty()) {
                    int h = min(height[i], height[stk.top()]) - height[mid];
                    int w = i - stk.top() - 1;
                    ans += h * w;
                }
            }
            stk.push(i);
        }
        return ans;
    }
};

int main(int argc, char const* argv[]) {
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    Solution solution;
    cout << solution.trap(height);
    return 0;
}