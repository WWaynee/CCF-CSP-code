#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, x, sum;

int main() {
	cin>>n>>x;
	vector<int> price(n);
	for (int i = 0; i < n; i++) {
		cin>>price[i];
		sum += price[i];
	}
	vector<bool> dp(sum + 1, false);
	// 每本书最多只能被拿一次
	dp[0] = true;
	for (int i = 0; i < n; i++) {
		// 防止多拿
		for (int j = sum; j >= price[i]; j--) {
			dp[j] = dp[j] | dp[j - price[i]];
		}
	}
	for (int i = x; i <= sum; i++) {
		if (dp[i]) {
			cout<<i<<endl;
			return 0;
		}
	}
	return 0;
}