### 一、什么是二分答案？

简单来说，二分答案的本质是：**当问题的答案具有单调性时，我们可以通过二分法来“猜测”答案，并用一个检验函数来验证这个猜测是否可行，从而将求解问题转化为判定问题**

**核心思想：**

1. 确定答案可能存在的范围 `[left, right]`
2. 在这个范围内进行二分查找，假设当前的中间值 `mid` 就是我们的候选答案
3. 设计一个 `check(mid)` 函数，用于判断这个候选答案 `mid` 是否**可行**（或是否满足某种条件）
4. 根据 `check(mid)` 的结果，来缩小答案的搜索范围：
   * 如果 `mid` **可行**，那么根据问题要求，调整 `left` 或 `right`
   * 如果 `mid` **不可行**，同样调整另一边
5. 当 `left` 和 `right` 相遇（或满足循环结束条件）时，我们就找到了最优答案

---

### 二、为什么需要二分答案？

对于某些问题，直接求解最优答案可能非常困难，复杂度很高。但是，**如果我们给你一个具体的答案 `X`，让你判断这个 `X` 是否能够实现，这个问题（判定问题）往往会简单得多**

二分答案就利用了这一点：

* **求解问题**：求最优的答案 `ans`
* **判定问题**：给定的 `X` 是否是一个可行解？

二分答案通过反复求解判定问题，来“逼近”最终的解

---

### 三、算法框架与步骤

以下是二分答案最通用的代码框架：

#### 最小化最大值

```cpp
// C++模板
bool check(int x) {
    // 根据题目而定, check()函数决定了题目的难度
}

int main(int argc, char const* argv[]) {
    int l = 0, r = 1e9; // r 的初始值可以根据题目确定
    int ans = 0;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) {
            ans = mid;
            // 缩小答案
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return 0;
}
```

```java
public class Main {
    static boolean check(int x) {
        // 根据题目而定, check()函数决定了题目的难度
    }

    public static void main(String[] args) {
        int l = 0, r = 1e9; // r 的初始值可以根据题目确定
        int ans = 0;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) {
                ans = mid;
                // 缩小答案
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
    }
}
```

#### 最大化最小值

```cpp
// C++模板
bool check(int x) {
    // 根据题目而定, check()函数决定了题目的难度
}

int main(int argc, char const* argv[]) {
    int l = 0, r = 1e9; // r 的初始值可以根据题目确定
    int ans = 0;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) {
            ans = mid;
            // 扩大答案
            left = mid + 1;
        }
        else {
            right = mid + 1;
        }
    }
    return 0;
}
```

```java
public class Main {
    static boolean check(int x) {
        // 根据题目而定, check()函数决定了题目的难度
    }

    public static void main(String[] args) {
        int l = 0, r = 1e9; // r 的初始值可以根据题目确定
        int ans = 0;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) {
                ans = mid;
                // 扩大答案
                left = mid + 1;
            }
            else {
                right = mid + 1;
            }
        }
    }
}
```

**注意：**

* `check(mid)` 函数是算法的灵魂，它因题而异
* 边界调整 (`right = mid` 还是 `left = mid + 1`，以及循环条件是 `<` 还是 `<=`) 需要根据问题的具体情况来定。上面的框架是“找第一个满足条件的值”的经典写法

---

### 四、二分答案的适用场景与要点

1. **适用场景**：

   * **最大值最小化**：将最大的值尽可能变得小
     * 例题：将一堆书分给 `k` 个人，每个人连续分到若干本，如何分使得每个人分到的页数最大值最小？
   * **最小值最大化**：将最小的值尽可能变得大
     * 例题：在一条直线上有 `n` 个点，选取 `k` 个点，使得任意两个选取的点之间的距离尽可能大，求这个最大的最小距离
2. **核心要点**：

   * **单调性是前提**：必须保证候选答案的可行性随着数值的变化是单调的（要么从可行突然变得不可行，要么从不可行突然变得可行）
   * **`check` 函数是关键**：这个函数的实现决定了算法的正确性。它需要高效地验证候选答案
