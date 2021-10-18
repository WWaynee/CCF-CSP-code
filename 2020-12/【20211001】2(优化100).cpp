# include <iostream>
# include <vector>
# include <algorithm>
using namespace std;
//每一个数值猜对的次数 = 前面猜为0的对的次数 + 本身及之后猜为1的对的次数
// 状态转移方程：num1 = num1 - pre1
// num0 = num0 + pre0

int main(){
    int size;
    cin>>size;
    vector<pair<int,int> > a(size);
    for(int i=0;i<size;i++){
        cin>>a[i].first>>a[i].second;
    }
    sort(a.begin(),a.end());
    int key = a[0].first, i, j, res;
    int num0, num1, max, pre0, pre1, cur0, cur1;
    num0 = num1 = max = pre0 = pre1 = cur0 = cur1 = 0;
    int idx = 0;
    for(i = 0;i < size;i++){
        if(a[i].second==1){
            num1++;
            if(a[i].first==key) pre1++;
        }else{
            if(a[i].first==key) pre0++;
        }
        if(a[i].first!=key && idx==0) idx = i;
    }
    max = num0 + num1;
    res = key;
    for(i = idx;i<size;){
        key = a[i].first;
        cur1 = 0; cur0 = 0;
        for(j=i;j<size && a[j].first==key;j++){
            if(a[j].second==1) cur1++;
            else cur0++;
        }
        num1 -= pre1;
        num0 += pre0;
        if(num1 + num0 >= max){
            max = num1 + num0;
            res = key;
        }
        pre1 = cur1;
        pre0 = cur0;
        i = j;
    }
    cout<<res;
    return 0;
}