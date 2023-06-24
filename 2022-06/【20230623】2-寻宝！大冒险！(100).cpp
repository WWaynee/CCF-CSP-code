#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int MAX_S = 55;

int n, L, S, cnt = 0;
bool s[MAX_S][MAX_S];

int main() {
    cin>>n>>L>>S;
    map<pair<int, int>, bool> tree;
    int x, y;
    for (int i = 0; i < n; i++) {
        cin>>x>>y;
        tree[{x, y}] = true;
    }
    for (int i = 0; i <= S; i++) {
        for (int j = 0; j <= S; j++) {
            cin>>x;
            if (x == 0) s[S - i][j] = false;
            else s[S - i][j] = true;
        }
    }
    for (auto iter = tree.begin(); iter != tree.end(); iter++) {
        // 超出边界
        if (iter->first.first + S > L || iter->first.second + S > L) continue;
        // 逐点匹配
        // 以大地图当前点(iter->first.first, iter->first.second)为宝藏图(0, 0)点
        bool flag = true;
        for (int i = 0; i <= S; i++) {
            for (int j = 0; j <= S; j++) {
                if (s[i][j] != tree[{iter->first.first + i, iter->first.second + j}]) {
                    flag = false;
                    break;
                }
            }
            if (!flag) break;
        }
        if (flag) cnt++;
    }
    cout<<cnt<<endl;
    return 0;
}