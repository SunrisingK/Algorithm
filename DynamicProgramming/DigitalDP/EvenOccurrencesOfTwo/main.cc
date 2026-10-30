#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int digit[20];      // 至多有20位数字
ll mem[20][2][2];   // 记忆化数组, 三个维度[当前生成数字的位数][前缀是否紧贴上界][状态(0表示偶数次/1表示奇数次)]
int len;            // 输入的数字位数

// 使用dfs来遍历每个数位的可能情况, 直到生成完成
ll dfs(int pos, bool tight, int state) {
    // pos == len表示已经生成完成了一个数字, 检查它当前的状态, 返回给它的父节点;
    // 由父节点收集答案并继续返回上一层
    if (pos == len) {
        return state == 0 ? 1 : 0;
    }

    // 记忆数组, 如果已经搜索过(pos, tight, state)为根节点的树
    // 就直接返回结果;
    ll& res = mem[pos][tight][state];
    if (res != -1) return res;

    // 这里就开始遍历(pos, tight, state)为根节点的树
    res = 0;
    
    // tight表示最高位到当前位的前一位，是否每一位数字都取到上界, 没有取到上界, 该数位就能取到9
    // 例如数字2345, digit[] = {2, 3, 4, 5}, dfs遍历到pos = 2时, 如果最高位第0位置上的数字取到了2, 第0位置上的数字取到了3,
    // 那么该位第2位置上的数字就只能取到4, 否则可以取到9
    // 简单来说, tight表示当前位的前缀数位是否都取到了上界
    int up = tight ? digit[pos] : 9;
    // d表示该数位上的候选数字[0, up]
    for (int d = 0; d <= up; ++d) {
        // 异或运算翻转奇偶性
        // state = 0 ^ 1 = 1
        int next_state = state ^ (d == 2 ? 1 : 0);
        // 更新tight = tight && (d == up)并传递给下一位
        res += dfs(pos + 1, tight && (d == up), next_state);
    }

    return res;
} 

ll solve(ll num) {
    // 小于0直接返回答案0, 表示没有合法数字
    if (num < 0) return 0;

    len = 0;

    // 0 只有 1 位
    if (num == 0) {
        digit[len++] = 0;
    }
    else {
        ll t = num;
        while (t > 0) {
            digit[len++] = t % 10;
            t /= 10;
        }
    }
    // 反序, 表示真正的数字
    reverse(digit, digit + len);

    // 初始化记忆数组, 一个小细节
    memset(mem, -1, sizeof(mem));
    
    // dfs + 记忆化搜索找答案
    // 初始状态, 从digit[]的第0位开始生成, 也就是最高位
    // 最高位不能超过digit[0], 他一定是紧贴上界的
    // 初始状态下还没有数字生成, 2出现了0次, 0也是偶数, state = 0
    return dfs(0, true, 0);
}


int main(int argc, char const* argv[]) {
    ll L, R;
    cin >> L >> R;
    cout << solve(R) - solve(L - 1) << endl;
    return 0;
}

// [1, 100]
// 2, 12, 32, 42, 52, 62, 72, 82, 92
// 20, 21, 23, 24, 25, 26, 27, 28, 29