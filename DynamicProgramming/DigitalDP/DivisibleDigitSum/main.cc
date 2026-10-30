#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int digit[20];
// 能被3整除, 就说明对3取余的结果为0, 而对3取余的结果集合为{0, 1, 2}
// 共3种状态
ll mem[20][2][3];
int len;

ll dfs(int pos, bool tight, int state) {
    if (pos == len) return state == 0 ? 1 : 0;

    ll& res = mem[pos][tight][state];
    if (res != -1) return res;

    res = 0;
    int up = tight ? digit[pos] : 9;
    for (int d = 0; d <= up; ++d) {
        // 在for()循环里更新state
        // 同余定理 (a + b) % c = ((a % c) + (b % c)) % c
        // (4 + 9) % 3 = ((4 % 3) + (9 % 3)) % 3 = 1
        // state本身存的就是前 pos - 1 位数字和对3的取余结果
        int next_state = (state + d) % 3;
        res += dfs(pos + 1, tight && (d == up), next_state);
    }

    return res;
}

ll solve(ll num) {
    if (num < 0) return 0;
    len = 0;
    if (num == 0) {
        digit[len++] = 0;
    }
    else {
        while (num > 0) {
            digit[len++] = num % 10;
            num /= 10;
        }
    }
    reverse(digit, digit + len);

    memset(mem, -1, sizeof(mem));
    // 初始情况下枚举最高位上的可能数字, tight必须是true
    // 初始情况下没有枚举任何数字, 和就是0, 0 mod 3 = 0
    return dfs(0, true, 0);
}

int main(int argc, char const* argv[]) {
    ll L, R;
    cin >> L >> R;
    cout << solve(R) - solve(L - 1) << endl;
    return 0;
}