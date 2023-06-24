# include <iostream>
# include <algorithm>
const int N = 1e5+5;

struct field{
    int t;
    int c;
};

bool cmp(const field& f1, const field& f2) {
    if (f1.t != f2.t) return f1.t > f2.t;
    return f1.c > f2.c;
}

int main() {
    int n, m, k;
    std::cin>>n>>m>>k;
    field f[N];
    int time = 0;
    for (int i = 1; i <= n; i++) {
        std::cin>>f[i].t>>f[i].c;
    }
    while (true) {
        // sort
        std::sort(f + 1, f + n + 1, cmp);
        // from beginning
        int t_ = f[1].t;
        time = t_;
        for (int i = 1; i <= n; i++) {
            // subtract from the biggest side and make the biggest elements go down
            if (f[i].t == t_) {
                m -= f[i].c;
                // not enough
                if (m < 0 || f[i].t <= k) {
                    time = f[i].t;
                    std::cout<<time<<std::endl;
                    return 0;
                } // enough
                else {
                    f[i].t--;
                }
            } else break;
        }
    }
    std::cout<<time<<std::endl;
    return 0;
}