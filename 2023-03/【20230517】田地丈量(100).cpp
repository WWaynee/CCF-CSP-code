# include <iostream>
# define N 105
typedef unsigned long long ull;

struct field{
    int x1, x2, y1, y2;
};

int main() {
    int n, a, b;
    std::cin>>n>>a>>b;
    field f[N];
    for (int i = 1; i <= n; i++) {
        std::cin>>f[i].x1>>f[i].y1>>f[i].x2>>f[i].y2;
    }
    ull sum = 0;
    for (int i = 1; i <= n; i++) {
        // Intersect or not
        if (((f[i].x1 >= 0 && f[i].x1 < a) || (f[i].x2 > 0 && f[i].x2 <= a)) && ((f[i].y1 >= 0 && f[i].y1 < b) || (f[i].y2 > 0 && f[i].y2 <= b))) {
            int width, height;
            if (f[i].x1 < 0) {
                width = f[i].x2;
            } else {
                if (f[i].x2 > a) width = a - f[i].x1;
                else width = f[i].x2 - f[i].x1;
            }
            if (f[i].y1 < 0) {
                height = f[i].y2;
            } else {
                if (f[i].y2 > b) height = b - f[i].y1;
                else height = f[i].y2 - f[i].y1;
            }
            sum += (height * width);
        }
    }
    std::cout<<sum<<std::endl;
    return 0;
}