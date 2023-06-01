#include <iostream>
#include <vector>
typedef long long ll;

int main() {
    int n, d;
    std::cin>>n>>d;
    // 输入矩阵Q
    std::vector<std::vector<ll> > Q(n, std::vector<ll>(d));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            std::cin>>Q[i][j];
        }
    }
    // 输入矩阵K，顺便也把转置运算做了
    std::vector<std::vector<int> > K(d, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            std::cin>>K[j][i];
        }
    }
    // 输入矩阵V
    std::vector<std::vector<int> > V(n, std::vector<int>(d));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            std::cin>>V[i][j];
        }
    }
    // 输入向量W
    std::vector<int> W(n);
    for (int i = 0; i < n; i++) std::cin>>W[i];
    // 运算
    // 先从Q*K(T)*W开始，Q（n*d）和KT（d*n），结果是n*n矩阵
    int max = (n > d? n: d);
    std::vector<std::vector<ll> > res(max, std::vector<ll>(max, 0));
    // 计算结果，单个元素值可能大于10^10，int存不下
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // res[i][j] = Q的第i行 * K的第j列 挨个元素相乘(一共d个元素) 然后相加
            for (int m = 0; m < d; m++) {
                // 顺便把乘W的操作也做了吧
                res[i][j] += (Q[i][m] * K[m][j] * W[i]);
            }
        }
    }
    // 再去乘V，res（n*n）和V（n*d）的结果应该是n*d，直接用Q矩阵来用就好了不用再开一个
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            Q[i][j] = 0;
            for (int m = 0; m < n; m++) {
                Q[i][j] += (res[i][m] * V[m][j]);
            }
        }
    }
    // 输出结果
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            std::cout<<Q[i][j]<<' ';
        }
        std::cout<<std::endl;
    }
    return 0;
}