#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int M = 105;

int n, m;

int link[M] = {0};	// 后面项目对前面项目的1对1依赖关系
int days[M] = {0};	// 耗时天数
int early[M] = {0};
int late[M] = {0};

vector<int> dep[M];	// 前面项目对后面项目的1对多被依赖关系

int main() {
	cin>>n>>m;
	int early_cnt = 0, late_cnt = 0;
	bool flag = true;
	for (int i = 1; i <= m; i++) {
		cin>>link[i];
		if (link[i] == 0) {	// 如果没有依赖，那这个项目就依赖它自己，最早第一天就可以开始，最晚在第n天完成
			link[i] = i;
			early[i] = 1;
			early_cnt++;
			if (flag && early[i] + days[i] - 1 > n) {
				flag = false;	// 表明是否有必要计算最晚开始时间
			}
		} else {
			dep[link[i]].push_back(i);
		}
	}
	for (int i = 1; i <= m; i++)
		cin>>days[i];
	// 计算最早时间
	while (early_cnt < m) {
		for (int i = 1; i <= m; i++) {
			// 如果当前的最早开始时间已经计算过了就可以跳过
			if (early[i] != 0) continue;
			// 如果当前项目的依赖项目的最早开始时间已经计算出来，那当前项目的最早开始时间也可以计算
			if (early[link[i]] != 0) {
				early[i] = early[link[i]] + days[link[i]];
				early_cnt++;	// 已经得出结果的项目+1
				if (flag && early[i] + days[i] - 1 > n) flag = false;
			}
			if (early_cnt >= m) break;
		}
		if (early_cnt >= m) break;
	}
	for (int i = 1; i <= m; i++) cout<<early[i]<<' ';
	cout<<endl;
	// 计算最晚时间
	if (flag) {
		while (late_cnt < m) {
			for (int i = 1; i <= m; i++) {
				if (late[i] != 0) continue;
				// 如果不被其他项目依赖，保证最后一天及之前完成即可
				if (dep[i].empty()) {
					late[i] = n - days[i] + 1;
					if (late[i] < 1) return 0;	// 做不到
					late_cnt++;
				}
				// 如果有依赖，需要保证所有后续项目都已经计算出最晚完成时间，当前项目的最晚时间才能计算出来
				else {
					bool cal = true;
					for (int j = 0; j < dep[i].size(); j++) {
						if (late[dep[i][j]] == 0) {
							cal = false;
							break;
						}
					}
					if (cal) {	// 可以计算最晚时间则计算
						late[i] = (int)1e9;
						for (int j = 0; j < dep[i].size(); j++) {
							late[i] = min(late[i], late[dep[i][j]]);
						}
						late[i] -= days[i];
						if (late[i] < 1) return 0; // 做不到
						late_cnt++;
					}
				}
				if (late_cnt >= m) break;
			}
			if (late_cnt >= m) break;
		}
		for (int i = 1; i <= m; i++) cout<<late[i]<<' ';
		cout<<endl;
	}
	return 0;
}