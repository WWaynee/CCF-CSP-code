# include <iostream>
# include <algorithm>
# include <unordered_map>
const int N = 1e5+5;
typedef unsigned long long ull;

struct field{
    int t;
    ull c;
};

bool cmp(const field& f1, const field& f2) {
    if (f1.t != f2.t) return f1.t > f2.t;
    return f1.c > f2.c;
}

int main() {
    int n, m, k;
    std::cin>>n>>m>>k;
    std::unordered_map<int, int> map;
    field f[N];
    int time, t, c, index = 1;
    for (int i = 1; i <= n; i++) {
        std::cin>>t>>c;
        if (map.find(t) == map.end()) {
            f[index].t = t;
            f[index].c = c;
            map[t] = index;
            index++;
        } else f[map[t]].c += c;// after this map won't be used
    }
    int beg = 1;
    std::sort(f + beg, f + index, cmp);
    while (true) {
        int time = f[beg].t;
        m -= f[beg].c;
        f[beg].t--;
        if (m < 0 || f[beg].t < k) {
            std::cout<<time<<std::endl;
            return 0;
        }
        if (beg < index - 1 && f[beg].t == f[beg + 1].t){
            f[beg + 1].c += f[beg].c;
            beg++;
            std::sort(f + beg, f + index, cmp);
        }
    }
    return 0;
}