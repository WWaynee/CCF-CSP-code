# include <iostream>
# include <vector>
# include <set>
# include <algorithm>
using namespace std;

int main(){
    int size;
    cin>>size;
    vector<int> a(size,0);
    set<int> num;
    int times = 0, res = 0;
    bool flag = false;
    for(int i=0;i<size;i++){
        cin>>a[i];
        num.insert(a[i]);
    }
    //±©Á¦½â·¨
    set<int>::iterator it;
    for(it=num.begin();it!=num.end();it++){
        int key = *it;
        if(key==0) continue;
        int times_ = 0;
        flag = false;
        for(int i=0;i<size;i++){
            if(flag && a[i]>=key && a[i]!=0) continue;
            else if(!flag && a[i]>=key && a[i]!=0){
                flag = true;
                times_++;
            }else{
                flag = false;
            }
        }
        if(times_>times) {
            times = times_;
            res = key;
        }
    }
    cout<<times;
    return 0;
}