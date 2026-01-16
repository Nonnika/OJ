#include<iostream>
#include<algorithm>

using namespace std;

long long num[1000001];

void solve(long long n) {
    // 对数组进行排序
    sort(num, num + n);
    
    // res表示当前能表示的最大连续正整数
    // 初始时，我们可以表示[1, res-1]的所有数，res初始为1
    long long res = 1;
    
    for(int i = 0; i < n; i++) {
        // 如果当前数字小于等于res，那么我们可以表示[1, res+num[i]-1]的所有数
        if(num[i] <= res) {
            res += num[i];
        } else {
            // 如果当前数字大于res，那么res就是不能表示的最小正整数
            // 需要检查res是否大于n来决定输出
            if(res > n) {
                cout << "Cool!" << endl;
            } else {
                cout << res << endl;
            }
            return;
        }
    }
    
    // 如果所有数都能被使用，那么res就是不能表示的最小正整数
    // 根据原始代码的逻辑：
    // 1. 如果所有1到n都能表示，输出"Cool!"
    // 2. 否则输出第一个不能表示的正整数
    // 所以如果res > n，那么所有1到n都能表示，输出"Cool!"
    // 如果res <= n，那么res就是第一个不能表示的正整数，输出res
    if(res > n) {
        cout << "Cool!" << endl;
    } else {
        cout << res << endl;
    }
}

/*
算法解释：
这个问题是经典的"找出最小的不能表示为给定正整数集合中某些数之和的正整数"。
例如：给定集合[1, 2, 4, 9]，最小的不能表示的正整数是8。

算法步骤：
1. 对数组排序
2. 初始化res = 1（表示我们可以表示[1, res-1]的所有数）
3. 遍历排序后的数组：
   - 如果当前数 <= res，那么我们可以表示[1, res+当前数-1]，所以res += 当前数
   - 否则，res就是答案

时间复杂度：O(n log n)（排序）
空间复杂度：O(1)

测试用例：
输入: [1, 2, 4, 9]
输出: 8

输入: [1, 2, 3, 4]
输出: 11

输入: [1, 1, 1, 1]
输出: 5
*/

int main(void) {
    int t;  // 测试用例数量
    cin >> t;
    
    while(t--) {
        long long n;
        cin >> n;
        
        for(int i = 0; i < n; i++) {
            cin >> num[i];
        }
        
        solve(n);
    }
    
    return 0;
}