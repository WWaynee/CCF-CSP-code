/**
 * 数据结构：差分数组
 * 技巧：对于边界溢出的处理
*/
#include <iostream>
using namespace std;

const int MAX = 4e5+5;

int diff[MAX] = {0};

int main() {
    int n, m, k, time, ti, ci;
    cin>>n>>m>>k;
    for (int i = 0; i < n; i++) {
        cin>>ti>>ci;
        int early = ti - k - ci + 1;    // 做核酸的最早时间
        int late = ti - k;  // 做核酸的最晚时间：保证第ti天时核酸刚好是出结果的当天
        // 差分数组
        if (late < 1) continue;
        early = early > 0 ? early : 1;
        diff[early]++;
        diff[late + 1]--;
    }
    for (int i = 1; i < MAX; i++) {
        diff[i] += diff[i - 1];
    }
    while (m--) {
        cin>>time;
        cout<<diff[time]<<endl;
    }
    return 0;
}