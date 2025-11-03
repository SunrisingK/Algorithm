最大化最小值代码模板

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
            right = mid - 1;
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
                right = mid - 1;
            }
        }
    }
}
```
