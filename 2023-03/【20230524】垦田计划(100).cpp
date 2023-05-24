#include <iostream>
#include <unordered_map>
#include <algorithm>
typedef unsigned long long ull;
const int N = 1e5+5;
int n, m, k, ind;

struct field {
    int t;
    ull c;
} f[N];

bool check(int min, int max) {
    if (min > max) return false;
    int mid = (min + max) >> 1;
    int sum = 0;
    for (int i = 0; i < ind; i++) {
        if (f[i].t > mid) sum += ((f[i].t - mid) * f[i].c);
        // 不够用
        if (sum > m) return false;
    }
    // 够用
    return true;
}

int main() {
    int t, c;
    ind = 0;
    std::cin>>n>>m>>k;
    std::unordered_map<int, int> map;
    int maxt = 0;
    for (int i = 0; i < n; i++) {
        std::cin>>t>>c;
        if (map.find(t) == map.end()) {
            map[t] = ind;
            f[ind].t = t;
            f[ind].c = c;
            ind++;
        } else {
            f[map[t]].c += c;
        }
        if (maxt < t) maxt = t;
    }
    int ans = 0;
    bool flag = true;
    while (flag) {
        if (check(k, maxt)) {
            int mid = ((k + maxt) >> 1);
            if (mid == maxt) maxt = mid - 1;
            else maxt = mid;
            ans = mid;
        } else {
            int mid = ((k + maxt) >> 1);
            if (mid == k) k = mid + 1;
            else k = mid;
        }
        if (k >= maxt) flag = false;
    }
    std::cout<<ans<<std::endl;
    return 0;
}