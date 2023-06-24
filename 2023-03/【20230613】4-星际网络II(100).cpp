/**
 * 数据结构：线段树
 * 技巧：离散化+1处理
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 把这个Q改成2e6+10就100分了...
const int Q = 2e6+10;

vector<string> addrs;

struct request {
	int type, id;
	string left, right, point;
}reqs[Q];

struct node {
	int cnt, left, right, lazy, minn, maxn;
}tree[Q];

string addr_add_one(string addr) {
	// 45分修改bug卡在这里：addrs.size()忘记-1
	// 提示运行错误
	for (int i = addr.size() - 1; i >= 0; i--) {
		if (addr[i] == ':') continue;
		if (addr[i] == '9') {
			addr[i] = 'a';break;
		}
		else if (addr[i] == 'f') addr[i] = '0';
		else {
			addr[i]++;break;
		}
	}
	return addr;
}

void push_up(int index) {
	tree[index].cnt = tree[index << 1].cnt + tree[index << 1 | 1].cnt;
	tree[index].minn = min(tree[index << 1].minn, tree[index << 1 | 1].minn);
	tree[index].maxn = max(tree[index << 1].maxn, tree[index << 1 | 1].maxn);
}

void push_down(int index) {
	if (tree[index].lazy != 0) {
		tree[index << 1].minn = tree[index << 1].maxn = tree[index].lazy;
		tree[index << 1].cnt = tree[index << 1].right - tree[index << 1].left + 1;
		tree[index << 1].lazy = tree[index].lazy;

		tree[index << 1 | 1].minn = tree[index << 1 | 1].maxn = tree[index].lazy;
		tree[index << 1 | 1].cnt = tree[index << 1 | 1].right - tree[index << 1 | 1].left + 1;
		tree[index << 1 | 1].lazy = tree[index].lazy;

		tree[index].lazy = 0;
	}
}

// 线段树板子操作：build、pushup、pushdown、query、modify
void build(int index, int left, int right) {
	tree[index] = {0, left, right, 0, (int)1e9, (int)-1e9};
	if (left >= right) return ;
	int mid = left + right >> 1;
	build(index << 1, left, mid);
	build(index << 1 | 1, mid + 1, right);
}

int query_cnt(int index, int left, int right) {
	if (left <= tree[index].left && right >= tree[index].right) {
		return tree[index].cnt;
	}
	push_down(index);
	int mid = tree[index].left + tree[index].right >> 1;
	int cnt = 0;
	if (left <= mid) cnt += query_cnt(index << 1, left, right);
	if (right > mid) cnt += query_cnt(index << 1 | 1, left, right);
	return cnt;
}

int query_minn(int index, int left, int right) {
	if (left <= tree[index].left && right >= tree[index].right) {
		return tree[index].minn;
	}
	push_down(index);
	int mid = tree[index].left + tree[index].right >> 1;
	int minn = (int)1e9;
	if (left <= mid) minn = query_minn(index << 1, left, right);
	if (right > mid) minn = min(minn, query_minn(index << 1 | 1, left, right));
	return minn;
}

int query_maxn(int index, int left, int right) {
	if (left <= tree[index].left && right >= tree[index].right) {
		return tree[index].maxn;
	}
	push_down(index);
	int mid = tree[index].left + tree[index].right >> 1;
	int maxn = (int)-1e9;
	if (left <= mid) maxn = query_maxn(index << 1, left, right);
	if (right > mid) maxn = max(maxn, query_maxn(index << 1 | 1, left, right));
	return maxn;
}

void modify(int index, int left, int right, int id) {
	// 能完全容纳当前结点表示的区间
	if (left <= tree[index].left && right >= tree[index].right) {
		tree[index].lazy = tree[index].minn = tree[index].maxn = id;
		tree[index].cnt = tree[index].right - tree[index].left + 1;
		return ;
	}
	push_down(index);
	int mid = tree[index].left + tree[index].right >> 1;
	if (left <= mid) modify(index << 1, left, right, id);
	if (right > mid) modify(index << 1 | 1, left, right, id);
	push_up(index);
}

int find(string addr) {
	return lower_bound(addrs.begin(), addrs.end(), addr) - addrs.begin() + 1;
}

int main() {
	int n, q;
	cin>>n>>q;
	for (int i = 0; i < q; i++) {
		cin>>reqs[i].type;
		if (reqs[i].type == 1) {
			cin>>reqs[i].id>>reqs[i].left>>reqs[i].right;
			addrs.push_back(reqs[i].left);
			addrs.push_back(reqs[i].right);
			addrs.push_back(addr_add_one(reqs[i].right));
		} else if (reqs[i].type == 2) {
			cin>>reqs[i].point;
			addrs.push_back(reqs[i].point);
			addrs.push_back(addr_add_one(reqs[i].point));
		} else {
			cin>>reqs[i].left>>reqs[i].right;
			addrs.push_back(reqs[i].left);
			addrs.push_back(reqs[i].right);
			addrs.push_back(addr_add_one(reqs[i].right));
		}
	}
	sort(addrs.begin(), addrs.end());
	addrs.erase(unique(addrs.begin(), addrs.end()), addrs.end());
	build(1, 1, addrs.size()); // 建树
	for (int i = 0; i < q; i++) {
		if (reqs[i].type == 1) {
			int id = reqs[i].id, l = find(reqs[i].left), r = find(reqs[i].right);
			int cnt = query_cnt(1, l, r), maxn = query_maxn(1, l, r), minn = query_minn(1, l, r);
			if (cnt == 0 || minn == id && maxn == id && cnt < r - l + 1) {	// 这块区域没人用过 或者 被当前用户用了一部分且其余部分没人用
				cout<<"YES"<<endl;
				modify(1, l, r, id); // 修改线段树
			} else {
				cout<<"NO"<<endl;
			}
		} else if (reqs[i].type == 2) {
			int p = find(reqs[i].point);
			int cnt = query_cnt(1, p, p), minn = query_minn(1, p, p);
			if (cnt == 0) { // 还没被分配
				cout<<0<<endl;
			} else {	// 已经被分配则输出用户id
				cout<<minn<<endl;
			}
		} else {
			int l = find(reqs[i].left), r = find(reqs[i].right);
			int cnt = query_cnt(1, l, r), maxn = query_maxn(1, l, r), minn = query_minn(1, l, r);
			if (minn == maxn && cnt == r - l + 1) { // 完整分配给某个用户
				cout<<minn<<endl;
			} else {
				cout<<0<<endl;
			}
		}
	}
	return 0;
}