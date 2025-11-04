单调栈是解决"Next Greater Element"类问题的高效工具, 理解它能大幅提升数组类算法的解题效率

单调栈本质是一种**栈结构**, 其核心特性是栈内元素始终保持**严格递增或严格递减**的顺序, 通过在入栈时移除破坏单调性的元素, 确保栈的有序性, 从而实现O(n)的时间复杂度

### 一、核心特性与分类

1. **核心规则**：新元素入栈前, 会将栈顶所有"破坏当前单调性"的元素弹出, 再将新元素压栈
2. **两大分类**：
   - **单调递增栈**：栈内元素从栈底到栈顶依次增大, 用于寻找"元素右侧第一个更小的元素"
   - **单调递减栈**：栈内元素从栈底到栈顶依次减小, 用于寻找"元素右侧第一个更大的元素"(最常用场景)

### 二、典型应用场景

单调栈的优势在于"用空间换时间", 能高效解决数组中"元素与前后元素的大小关系"问题, 常见场景包括：

- 寻找数组中每个元素的下一个更大元素
- 寻找数组中每个元素的下一个更小元素
- 计算柱状图中最大矩形的面积--[LeetCode 84题](https://leetcode.cn/problems/largest-rectangle-in-histogram/description/)
- 计算接雨水的总量--[LeetCode 42题](https://leetcode.cn/problems/trapping-rain-water/description/)
- 解决去除重复字母并保持字典序最小的问题--[LeetCode 316题](https://leetcode.cn/problems/remove-duplicate-letters/description/)

### 三、解题步骤(以"下一个更大元素"为例)

以单调递减栈求解"数组中每个元素右侧第一个更大元素"为例, 步骤清晰固定：

1. 初始化一个空栈, 栈内存储数组索引(而非元素值, 便于定位)
2. 遍历数组, 对每个元素 `nums[i]`：
   - 若栈不为空, 且当前元素 `nums[i]`大于栈顶索引对应的元素 `nums[stack.peek()]`, 则弹出栈顶索引, 并记录"栈顶索引对应的元素的下一个更大元素为 `nums[i]`"
   - 重复上一步, 直到栈为空或当前元素不大于栈顶元素
   - 将当前索引 `i`压入栈中
3. 遍历结束后, 栈中剩余索引对应的元素, 其"下一个更大元素"均为 `-1`(无更大元素)

### 四、代码示例 

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, -1); // 初始化默认值为-1
        stack<int> stk;         // 栈存索引
        for (int i = 0; i < n; ++i) {
            // 弹出栈中比当前元素小的索引, 记录结果
            while (!stk.empty() && nums[stk.top()] < nums[i]) {
                int index = stk.top(); stk.pop();
                ans[index] = nums[i];
            }
            stk.push(i);        // 压入当前索引
        }
        return ans;
    }
};

int main(int argc, char const* argv[]) {
    vector<int> nums = {2, 1, 2, 4, 3};
    Solution solution;
    vector<int> ans = solution.nextGreaterElement(nums);
    for (int& x: ans) cout << x << " ";
}
```

---

```java
import java.util.Stack;
import java.util.Arrays;

public class Main {
    public class Solution {
        public int[] nextGreaterElement(int[] nums) {
            int n = nums.length;
            int[] result = new int[n];
            Arrays.fill(result, -1);                // 初始化默认值为-1
            Stack<Integer> stack = new Stack<>();   // 栈存索引
        
            for (int i = 0; i < n; i++) {
                // 弹出栈中比当前元素小的索引, 记录结果
                while (!stack.isEmpty() && nums[i] > nums[stack.peek()]) {
                    int topIndex = stack.pop();
                    result[topIndex] = nums[i];
                }
                stack.push(i);                      // 压入当前索引
            }
            return result;
        }
    }

    public static void main(String[] args) {
        Solution solution = new NextGreaterElement();
        int[] nums = {2, 1, 2, 4, 3};
        int[] res = solution.nextGreaterElement(nums);
        System.out.println(Arrays.toString(res));
    }
}
```