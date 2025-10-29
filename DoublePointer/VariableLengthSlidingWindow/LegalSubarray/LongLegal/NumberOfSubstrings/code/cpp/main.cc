#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
private:
    bool check(vector<int>& count) {
        return count[0] > 0 && count[1] > 0 && count[2] > 0;
    }

public:
    int numberOfSubstrings(string s) {
        // 子串长度越长越合法
        // 内层循环中不断缩小窗口直到窗口不合法, 那么最后一次收缩窗口前的那个窗口一定是合法的
        // [left, right]不合法, 那么[left - 1, right]合法, [left - 2, right]合法..., [0, right]合法
        // 子串个数为 left
        int ans = 0;
        int left = 0;
        vector<int> count(3);     // 统计出现的数组
        for (int right = 0; right < s.length(); ++right) {
            count[s[right] - 'a']++;
            while (left <= right && check(count)) {
                count[s[left] - 'a']--;
                left++;
            }
            ans += left;
        }
        return ans;
    }
};

int main(int argc, char const* argv[]) {
    string s = "abcabc";
    Solution sl;
    cout << sl.numberOfSubstrings(s);
    return 0;
}