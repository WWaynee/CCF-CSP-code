#include <iostream>
#include <unordered_map>
#include <vector>
#include <array>

int main() {
    std::unordered_map<int, int> map;
    std::vector<std::vector<std::array<int, 3> > > boards;
    std::vector<int> res;
    int n;
    std::cin>>n;
    while (n--) {
        // 输入当前的局面
        char ch;
        std::vector<std::array<int, 3> > board;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                std::cin>>ch;
                if (ch != '*') {
                    board.push_back({i, j, ch});
                }
            }
        }
        // 比较局面是否出现过
        if (boards.empty()) {
            boards.push_back(board);
            map[0] = 1;
            res.push_back(1);
        } else {
            bool exist = true;
            int index = -1;
            for (int i = 0; i < boards.size(); i++) {
                exist = true;
                if (board.size() != boards[i].size()) {
                    exist = false;
                    continue;
                }
                for (int j = 0; j < boards[i].size(); j++) {
                    if (board[j][0] != boards[i][j][0] || board[j][1] != boards[i][j][1] || board[j][2] != boards[i][j][2]) {
                        exist = false;
                        break;
                    }
                }
                if (!exist) continue;
                exist = true;
                index = i;
                break;
            }
            if (exist) {
                map[index]++;
                res.push_back(map[index]);
            } else {
                boards.push_back(board);
                map[boards.size() - 1] = 1;
                res.push_back(1);
            }
        }
    }
    for (int i = 0; i < res.size(); i++) std::cout<<res[i]<<std::endl;
    return 0;
}