# 数位 DP（Digital DP）

数位 DP 用于统计满足某些“数位相关条件”的数字个数，典型问题形如：

> 求区间 `[L, R]` 中，十进制/二进制表示满足某条件的数字个数。

条件例子：数位和能被 K 整除、数字 2 出现偶数次、不含数字 4、二进制中 1 的个数为偶数、回文数等。

核心思想：**把数字按位拆开，从高位到低位逐位枚举，用记忆化搜索避免重复计算。**

数位 DP = DFS 枚举所有数 + 记忆化（memo）剪掉重复子树 + 状态设计（tight / 题目相关 state）。

---

## 1. 通用骨架（记忆化搜索版）

```cpp
#include <bits/stdc++.h>
using namespace std;

int digits[20], len;          // 十进制最多 19 位，开 20 够用
long long memo[20][2][/*state 大小*/];

// pos  : 当前处理到第几位（0 表示最高位）
// tight: 从最高位到前一位，是否每一位都等于上界的对应位
// state: 题目相关状态（奇偶 / 余数 / 计数 / 标志位 ...）
long long dfs(int pos, bool tight, int state) {
    // 边界：所有位填完，判断是否合法
    if (pos == len) return /* 边界条件 */;

    // 记忆化：算过就直接返回
    long long &res = memo[pos][tight][state];
    if (res != -1) return res;

    res = 0;
    // 卡上界时当前位最多取 digits[pos]，否则取进制-1（十进制 9，二进制 1）
    int up = tight ? digits[pos] : 9;

    for (int d = 0; d <= up; d++) {
        int nstate = /* 状态转移 */;
        res += dfs(pos + 1, tight && (d == up), nstate);
    }
    return res;
}

// 统计 [0, x] 中满足条件的个数
long long solve(long long x) {
    if (x < 0) return 0;

    len = 0;
    long long t = x;
    if (t == 0) {
        digits[len++] = 0;
    } else {
        while (t) { digits[len++] = t % 10; t /= 10; }
    }
    reverse(digits, digits + len);   // 只反转有效部分

    memset(memo, -1, sizeof(memo));  // 每次 solve 必须清空
    return dfs(0, true, 0);
}

int main() {
    long long L, R;
    cin >> L >> R;
    cout << solve(R) - solve(L - 1) << "\n";
    return 0;
}
```

**区间答案**统一用 `solve(R) - solve(L - 1)`。

---

## 2. tight 的含义

`tight = true` 等价于：

> 当前构造的前缀，和上界 x 的前缀完全相等。

- `tight = true` 时，当前位最多取 `digits[pos]`；
- `tight = false` 时，当前位可自由取 `0 ~ 进制-1`；
- 转移写 `tight && (d == up)`：只有“原来卡上界”且“这一位取到上限”才继续卡。

注意：`tight=true` 不是只看第一位，而是**一路贴着上界走的那条链**。一旦某位取小，后面全部 `tight=false`。

---

## 3. 状态设计：第三维存“等价类”

第三维不是存某个数值，而是存**子问题所处的状态类别**。原则：

> 只保留“对后续决策有影响”的信息，把对任意后续填法结果都相同的状态合并。

常见状态设计：


| 题目要求          | state                 | 状态数 | 转移                        |
| ------------------- | ----------------------- | -------- | ----------------------------- |
| 1 的个数为偶数    | `parity` 0/1          | 2      | `parity ^ d`                |
| 数字 2 出现偶数次 | `parity` 0/1          | 2      | `parity ^ (d == 2)`         |
| 数位和 % K == 0   | `mod` 0..K-1          | K      | `(mod + d) % K`             |
| 数字 2 恰好 2 次  | `cnt` 0/1/2/3（饱和） | 4      | `d==2 ? min(cnt+1,3) : cnt` |
| 数字 2 至少 1 次  | `flag` 0/1            | 2      | `flag |= (d == 2)`          |
| 不含数字 4        | `flag` 0/1            | 2      | `flag |= (d == 4)`          |
| 数位和恰好 S      | `sum` 0..9·len       | ≤172  | `sum + d`                   |
| 数字 0 出现偶数次 | `started` + `parity`  | 4      | 见前导零一节                |

**压缩技巧：**

- **饱和计数**：超过上限后全部合并为一个“废”状态（如恰好 2 次，3 表示 ≥3）。
- **同余压缩**：只存 `sum % K`，不存完整和。
- **多状态组合**：`state = a * size_b + b`，把多个维度压成一个整数。

---

## 4. 两个 return

```cpp
if (pos == len) return 边界条件;       // 第一个 return
if (memo[pos][tight][state] != -1) return 它;  // 第二个 return
```

- **第一个 return**：走到叶子，判断这个完整数字是否合法，返回 0/1；父节点通过 `res +=` 收集，层层向上汇总。
- **第二个 return**：以当前 `(pos, tight, state)` 为根的子树之前算过，直接抄缓存，不再展开。

顺序：先判叶子，再查缓存。

`memo` 用 `-1` 作“未计算”哨兵，因为方案数非负。

---

## 5. 前导零（started）

判断是否需要 `started`：

> 前导零这个 0 会不会被 state 统计进去？


| 题目              | 需要 started | 原因                 |
| ------------------- | -------------- | ---------------------- |
| 数字 2 出现偶数次 | 否           | 前导零不是 2         |
| 数位和 % K        | 否           | 前导零加 0           |
| 数字 0 出现偶数次 | 是           | 前导零是 0，会污染   |
| 不含数字 0        | 是           | 前导零会误判“含 0” |
| 回文数 / 位数相关 | 是           | 前导零影响长度与对称 |
| 首位不能为 0      | 是           | 前导零影响首位       |

带 `started` 的写法：

```cpp
long long dfs(int pos, bool tight, bool started, int state) {
    if (pos == len) return started ? 边界条件 : /* 数字 0 的特殊判断 */;

    long long &res = memo[pos][tight][started][state];
    if (res != -1) return res;

    res = 0;
    int up = tight ? digits[pos] : 9;
    for (int d = 0; d <= up; d++) {
        bool nstarted = started || (d != 0);
        int nstate = state;
        if (nstarted) nstate = /* 只有真正开始后才更新 state */;
        res += dfs(pos + 1, tight && (d == up), nstarted, nstate);
    }
    return res;
}
```

`memo` 多一维；也可把 `(started, state)` 压成一个整数。

---

## 6. 换进制：十进制 → 二进制

只改 3 处，骨架不动：


| 位置     | 十进制                    | 二进制                  |
| ---------- | --------------------------- | ------------------------- |
| 拆位     | `t % 10; t /= 10`         | `t & 1; t >>= 1`        |
| up 上限  | `tight ? digits[pos] : 9` | `tight ? bits[pos] : 1` |
| 翻转条件 | `parity ^ (d == 2)`       | `parity ^ d`            |

二进制拆位示例：

```cpp
len = 0;
long long t = x;
if (t == 0) bits[len++] = 0;
else { while (t) { bits[len++] = t & 1; t >>= 1; } }
reverse(bits, bits + len);
```

`x ≤ 10^18 < 2^60`，`bits[64]`、`memo[64][...]` 够用。

---

## 7. 常见题型

1. **数位和能被 K 整除**：state = `sum % K`，边界 `mod == 0`。
2. **数字 2 出现偶数次**：state = `parity`，转移 `parity ^ (d == 2)`。
3. **数字 2 恰好出现 2 次**：饱和计数，state ∈ {0,1,2,3}。
4. **不含数字 4 / 数字 2 至少 1 次**：`flag` 状态。
5. **二进制中 1 的个数为偶数**：二进制 + `parity ^ d`。
6. **二进制中 1 的个数是 3 的倍数**：二进制 + `(state + d) % 3`。
7. **双状态组合**：不含 4 且数字 2 出现偶数次，`memo[pos][tight][has4][parity]`。
8. **数字 0 出现偶数次 / 不含 0**：需要 `started`。
9. **回文数**：需要 `started` + 记录对应位，状态设计更复杂。

---

## 8. 易错点

1. **`up` 写成 `digits[0]`**：必须 `digits[pos]`，`pos` 每层都变。
2. **`tight` 转移写成 `d == digits[pos]`**：统一用 `up` 更安全。
3. **`reverse` 范围写成整个数组**：只反转 `begin ~ begin+len`。
4. **`solve` 忘 `memset`**：不同 x 的 digits 不同，必须清空 memo。
5. **`x = 0` 没特判**：拆位时 `while` 不执行，需手动 `digits[len++] = 0`。
6. **`solve(-1)` 没返回 0**：`L = 0` 时会调用 `solve(-1)`。
7. **`memset` 设非 0/-1 值**：`memset` 按字节填充，只对 0 和 -1 安全。
8. **`long long` 写成 `int`**：`n ≤ 10^18` 必须 `long long`。
9. **前导零污染**：统计数字 0 / 位数 / 含 0 时，必须加 `started`。
10. **0 的边界定义**：题目是否把数字 0 算作合法，要在边界判断中明确。
11. **多组数据未清空 memo**：每组 `solve` 都要 `memset`。
12. **饱和计数忘记封顶**：状态数会膨胀，且超过上限后行为相同，应合并。

---

## 9. 复杂度

- 状态数：`len × 2 × |state|`（带 started 再乘 2）
- 每状态枚举 `进制` 个数字
- 总复杂度：`O(len × |state| × 进制)`
- 十进制 `len ≤ 19`，二进制 `len ≤ 60`，通常瞬间完成。

---

## 10. 做题自检清单

拿到新题，先回答 5 问再写代码：

1. **state 存什么？有几个取值？**（等价类压缩）
2. **边界 `pos == len` 返回什么？** 什么条件算合法？
3. **转移怎么写？** 这一位 `d` 如何影响 state？
4. **几进制？** 拆位和 `up` 上限对不对？
5. **前导零有影响吗？** 需要 `started` 吗？

5 问答完，代码就是填空。

---

## 11. 示例：数字 2 出现偶数次

```cpp
#include <bits/stdc++.h>
using namespace std;

int digits[20], len;
long long memo[20][2][2];   // [pos][tight][parity]

long long dfs(int pos, bool tight, int parity) {
    if (pos == len) return parity == 0 ? 1 : 0;

    long long &res = memo[pos][tight][parity];
    if (res != -1) return res;

    res = 0;
    int up = tight ? digits[pos] : 9;
    for (int d = 0; d <= up; d++) {
        int nparity = parity ^ (d == 2 ? 1 : 0);
        res += dfs(pos + 1, tight && (d == up), nparity);
    }
    return res;
}

long long solve(long long x) {
    if (x < 0) return 0;
    len = 0;
    long long t = x;
    if (t == 0) digits[len++] = 0;
    else { while (t) { digits[len++] = t % 10; t /= 10; } }
    reverse(digits, digits + len);
    memset(memo, -1, sizeof(memo));
    return dfs(0, true, 0);
}

int main() {
    long long L, R;
    cin >> L >> R;
    cout << solve(R) - solve(L - 1) << "\n";
    return 0;
}
```

验证：`[1, 22]` 输出 `18`；`solve(22) = 19`，`solve(0) = 1`。

---

## 12. 一句话总结

> 数位 DP = 按位 DFS 枚举所有数 + 记忆化剪掉重复子树 + 状态设计（tight / 题目相关 state）。骨架固定，换题只改：state 含义与取值、边界判断、状态转移、进制、是否需要前导零。

