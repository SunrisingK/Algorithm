单调队列是解决“滑动窗口最值”等高频问题的高效数据结构, 核心优势是能把时间复杂度从暴力的 O(nk) 降到 O(n)。

### 一、核心定义

单调队列(Monotonic Queue)是一种**队列内元素始终保持单调递增或单调递减**的特殊队列。它不遵循普通队列“先进先出”的严格规则, 而是在元素入队时, 会删除队列中破坏单调性的元素, 确保队列头部始终是当前队列的“最值”(最大值或最小值)。

常见的两种类型：

- **单调递减队列**：队列内元素从队头到队尾依次减小, 队头是当前队列的最大值。
- **单调递增队列**：队列内元素从队头到队尾依次增大, 队头是当前队列的最小值。

### 二、核心操作(以单调递减队列为例)

单调队列的操作围绕“维护单调性”展开, 主要有 **入队(push)** 和 **出队(pop)** 两种核心操作：

#### 1. 入队(push): 确保新元素入队后队列仍递减

假设要将元素 `x` 入队, 操作步骤如下：

1. 从队尾开始, 依次比较队列内元素与 `x`。
2. 若队尾元素 **小于等于** `x`(破坏递减性), 则删除该队尾元素, 重复此步骤。
3. 当队尾元素 **大于** `x` 或队列为空时, 将 `x` 加入队尾。

#### 2. 出队(pop)：仅删除队头的“过期”元素

只有当队头元素是当前窗口/区间中“不再需要”的元素(如滑动窗口移出左边界的元素)时, 才将其从队头删除。

- 普通情况下, 队头始终是当前最值, 不会主动删除(除非过期)。

#### 3. 优势

1. **时间效率高**：每个元素仅入队和出队各一次, 整体时间复杂度 O(n), 远优于暴力法的 O(nk)。
2. **针对性强**：完美解决“滑动窗口最值”“区间最值查询”等问题, 是这类场景的最优解之一。

### 三、实现方式

```cpp
#include <deque>    // 借助双端队列deque实现单调队列
using namespace std;

int main(int argc, char const* argv[]) {
    vector<int> nums = {1, 1, 4, 5, 1, 4, 1, 9, 1, 9, 8, 1, 0};
    int k = 3;
    // 定长窗口内的最大值和最小值
    vector<int> maxv, minv;
    deque<int> que;     // 单调队列存储的是数组的下标
  
    // 单调减队列
    for (int i = 0; i < nums.size(); ++i) {
        // 淘汰队尾
        while (!que.empty() && nums[que.back()] <= nums[i]) {
            que.pop_back();
        }
        que.push_back(i);

        // 计算队列左端点
        int left = i - k + 1;

        // 淘汰过期元素
        if (que.front() < left) {
            que.pop_front();
        }

        if (left >= 0) {
            maxv.push_back(que.front());
        }
    }
    que.clear();

    // 单调增队列
    for (int i = 0; i < nums.size(); ++i) {
        // 淘汰队尾
        while (!que.empty() && nums[que.back()] >= nums[i]) {
            que.pop_back();
        }
        que.push_back(i);

        // 计算队列左端点
        int left = i - k + 1;

        // 淘汰过期元素
        if (que.front() < left) {
            que.pop_front();
        }

        if (left >= 0) {
            minv.push_back(nums[que.front()]);
        }
    }
}
```

---

```java
import java.util.ArrayDeque;
import java.util.Deque;

/**
 * Java中除了提供ArrayDeque实现双端队列, 还提供了LinkedList实现方法
 * -- C++<deque>        -- Java ArrayDeuqe      -- Java LinkedList
 * -- que.pop_back()    -- que.removeLast()     -- que.pollLast()
 * -- que.push_back()   -- que.addLast()        -- que.offerLast()
 * -- que.pop_front()   -- que.removerFirst()   -- que.pollFirst()
 * -- que.front()       -- que.getFirst()       -- que.peakFirst()
*/

public class Main {
    public static void main(String[] args) {
        int[] nums = {1, 1, 4, 5, 1, 4, 1, 9, 1, 9, 8, 1, 0};
        int n = nums.length;
        int k = 3;
      
        int[] maxv = new int[n - k + 1];            // 窗口个数
        int[] minv = new int[n - k + 1];            // 窗口个数
        Deque<Integer> que = new ArrayDeque<>();    // 单调队列

        // 单调减队列
        for (int i = 0; i < n; i++) {
            // 1. 右边入
            while (!que.isEmpty() && nums[que.getLast()] <= nums[i]) {
                que.removeLast(); // 维护 que 的单调性
            }
            que.addLast(i); // 注意保存的是下标, 这样下面可以判断队首是否离开窗口

            // 2. 左边出
            int left = i - k + 1; // 窗口左端点
            if (que.getFirst() < left) { // 队首离开窗口
                que.removeFirst();
            }

            // 3. 在窗口左端点处记录答案
            if (left >= 0) {
                // 由于队首到队尾单调递减, 所以窗口最大值就在队首
                ans[left] = nums[que.getFirst()];
            }
        }

        que.clear();

        // 单调增队列
        for (int i = 0; i < n; i++) {
            // 1. 右边入
            while (!que.isEmpty() && nums[que.getLast()] >= nums[i]) {
                que.removeLast(); // 维护 que 的单调性
            }
            que.addLast(i); // 注意保存的是下标, 这样下面可以判断队首是否离开窗口

            // 2. 左边出
            int left = i - k + 1; // 窗口左端点
            if (que.getFirst() < left) { // 队首离开窗口
                que.removeFirst();
            }

            // 3. 在窗口左端点处记录答案
            if (left >= 0) {
                // 由于队首到队尾单调递减, 所以窗口最大值就在队首
                ans[left] = nums[que.getFirst()];
            }
        }
    }
}
```
