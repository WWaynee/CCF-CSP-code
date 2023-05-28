#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <string>
#include <bitset>

const int N = 2500, M = 500;
int users_num, attr_num, cmds_num;
std::vector<std::bitset<N> > vec;

struct user {
    int dn;
    std::unordered_map<int, int> attr;
}users[N];

int str2num(std::string &s, int beg, int end) {
    return atoi(s.substr(beg, end - beg + 1).c_str());
}

// 解析原子表达式
std::bitset<N> parse_atomic(std::string &s, int beg, int end) {
    std::bitset<N> res;
    int i = beg;
    for (; i <= end && s[i] != ':' && s[i] != '~'; i++); // 第i位字符是断言:或者反断言~
    int attr = str2num(s, beg, i - 1);
    int val = str2num(s, i + 1, end);
    if (s[i] == ':') { // 断言
        for (int i = 0; i < users_num; i++) {
            if (users[i].attr.find(attr) != users[i].attr.end() && users[i].attr[attr] == val) res.set(i, true);
        }
    } else {
        for (int i = 0; i < users_num; i++) {
            if (users[i].attr.find(attr) != users[i].attr.end() && users[i].attr[attr] != val) res.set(i, true);
        }
    }
    return res;
}

// 找到嵌套表达式第一个最外围表达式的右括号位置
// 不需要用到栈，直接计算括号数量即可
int find_emb(std::string &s, int beg, int end) {
    int cnt = 0;
    for (int i = beg; i <= end; i++) {
        if (s[i] == '(') cnt++;
        if (s[i] == ')') {
            cnt--;
            if (cnt == 0) return i;
        }
    }
    return -1;
}

// 解析复杂表达式
std::bitset<N> parse_group(std::string &s, int beg, int end) {
    if (s[beg] == '&' || s[beg] == '|') { // 嵌套表达式需要递归解析
        int i = find_emb(s, beg + 1, end);
        auto res1 = parse_group(s, beg + 2, i - 1);
        auto res2 = parse_group(s, i + 2, end - 1);
        if (s[beg] == '&') return res1 & res2;
        else return res1 | res2;
    } else return parse_atomic(s, beg, end);
}

int main() {
    std::cin>>users_num;
    int attr, val;
    for (int i = 0; i < users_num; i++) {
        std::cin>>users[i].dn>>attr_num;
        for (int j = 0; j < attr_num; j++) {
            std::cin>>attr>>val;
            users[i].attr[attr] = val;
        }
    }
    std::sort(users, users + users_num, [](user &a, user &b){return a.dn < b.dn;});
    std::cin>>cmds_num;
    std::string cmd;
    while (cmds_num--) {
        std::cin>>cmd;
        auto res = parse_group(cmd, 0, cmd.size() - 1);
        vec.push_back(res);
    }
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < users_num; j++) {
            if (vec[i][j]) std::cout<<users[j].dn<<' ';
        }
        std::cout<<std::endl;
    }
    return 0;
}