#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int ans = 0;
        unordered_set<char> st;

        int left = 0;
        // 枚举右维护左
        for (int right = 0; right < s.size(); ++right) {
            char c = s[right];  // 待加入窗口的字符
            // 用while()循坏确保窗口内没有待加入字符
            while (left <= right && st.count(c)) {
                st.erase(s[left]);
                left++;
            }
            st.insert(c);
            // 更新答案
            ans = max(ans, right - left + 1);
        }
        return ans;
    }      
};

int main(int argc, char const* argv[]) {
    string s = "abcabcbb";
    Solution solution;
    cout << solution.lengthOfLongestSubstring(s);
    return 0;
}