# include <iostream>
# include <vector>
using namespace std;
int main(){
    int size;
    cin>>size;
    vector<int> b(size,0);
    for(int i=0;i<size;i++)
        cin>>b[i];
    int maxn,minn;
    maxn = minn = b[0];
    for(int i=1;i<size;i++){
        maxn += b[i];
        if(b[i]!=b[i-1]) minn += b[i];
    }
    cout<<maxn<<endl<<minn;
    return 0;
}