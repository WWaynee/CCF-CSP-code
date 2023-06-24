#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct range{
	int left, right;
};

bool cmp(range &r1, range &r2) {
	if (r1.left == r2.left) return r1.right < r2.right;
	return r1.left < r2.left;
}

int main() {
	// n块田地，m个施肥车
	int n, m;
	cin>>n>>m;
	vector<range> rs(m);
	for (int i = 0; i < m; i++) {
		cin>>rs[i].left>>rs[i].right;
	}
	sort(rs.begin(), rs.end(), cmp);
	int sum = 0;
	// 暴力枚举区间的可能情况
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			bool flag = false;
			// 涂区间，满足的设置为false
			vector<bool> r(j - i + 1, false);
			// 检测当前区间是否符合条件
			for (int k = 0; k < m; k++) {
				if (rs[k].left >= i && rs[k].right <= j) {
					for (int q = rs[k].left; q <= rs[k].right; q++) {
						r[q - i] = true;
					}
				}
				if (rs[k].left > j) break;
			}
			for (int k = 0; k < r.size(); k++) {
				if (!r[k]) { // 不可能
					flag = true;
					break;
				}
			}
			if (!flag) {
				sum++;
			}
		}
	}
	cout<<sum<<endl;
	return 0;
}