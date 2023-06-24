#include <iostream>
using namespace std;

const int MAX = 1e5+5;

// 出行计划：出行时间 + 时间限制
// 比如时间10出行，要求24小时内核酸
// 那么符合核酸结果的时间段是10~10+24-1
pair<int, int> items[MAX];

int main() {
    int n, m, k, time;
    cin>>n>>m>>k;
    for (int i = 0; i < n; i++) {
        cin>>items[i].first>>items[i].second;
    }
    while (m--) {
        cin>>time;
        // 查询符合要求的活动数量
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            // 出核酸结果的时间：[time + k];
            // 核酸结果有效的时间段：a = [time + k, time + k + items[i].second - 1]
            // 该场所能接收的有效时间段：b = [items[i].first, items[i].first + items[i].second - 1]
            // 所以要保证a跟b在前面部分有交集
            if (time + k + items[i].second - 1 >= items[i].first && time + k <= items[i].first) {
                cnt++;
            }
        }
        cout<<cnt<<endl;
    }
    return 0;
}