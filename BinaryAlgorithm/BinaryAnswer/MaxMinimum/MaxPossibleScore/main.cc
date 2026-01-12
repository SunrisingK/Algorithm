#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;


class Solution {
private:
    bool check(int x, vector<int>& start, int d) {
        /*
         * 贪心, 现在问题变成
         * 给定 x , 能否从每个区间各选一个数
         * 使得任意两数之差的大于等于 x (初始数字越小越容易满足这个条件)
         * =====================================================================
         * 选定左端点 s0 作为初始候选数字n0, 候选数字 n1 = s0 + x 范围 [s1, s1 + d]
         * 如果 s0 + x < s1, 那么候选数字设为 s1 是符合要求的(s1 - s0 >= x)
         * 如果 s0 + x >= s1, 那么候选数字设为 s1 是不符合要求的(s1 - s0 <= x)
         * 所以候选数字为 max(s0 + x, s1), 但不能大于区间右端点, 后续候选数字同理可得
        */
        long long cur = LLONG_MIN;          // 候选数字
        for (int s: start) {
            cur = max(cur + x, (long long)s);          // 候选数字 >= 区间左端点 s
            if (cur > s + d) return false;
        }
        return true;
    }

public:
    int maxPossibleScore(vector<int>& start, int d) {
        ranges::sort(start);
        int n = start.size();
        int ans = 0;
        int left = 0; 
        int right = 1 + (d + start[n - 1] - start[0]) / (n - 1);
        // right设置成 start[n - 1] 也可以, 这个可以想到

        // right = 1 + (d + start[n - 1] - start[0]) / (n - 1)
        // d + start[n - 1] - start[0]表示区间的最大跨度
        // 要把区间分成 n 个小区间, 每个小区间之间会有间隔, 一共有 n - 1 个间隔
        // 平均分配的间隔再加 1 就是可能的最大值
        
        while (left <= right) {
            int mid = left +  (right - left) / 2;
            if (check(mid, start, d)) {
                ans = mid;
                // 扩大答案
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return ans;
    }
};


int main(int argc, char const* argv[]) {
    vector<int> start = {6, 0, 3};
    int d = 2;
    Solution s;
    cout << s.maxPossibleScore(start, d);
    return 0;
}