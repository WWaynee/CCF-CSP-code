# include <iostream>
# include <vector>
using namespace std;
int main(){
    int n,m,l,num;
    cin>>n>>m>>l;
    vector<int> res(l,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>num;
            res[num]++;
        }
    }
    for(int i=0;i<res.size();i++)
        cout<<res[i]<<' ';
    return 0;
}