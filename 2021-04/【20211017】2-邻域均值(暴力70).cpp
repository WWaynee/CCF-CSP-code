# include <iostream>
using namespace std;
# define N 605
int img[N][N];

int main(){
    int n,l,r,t,i,j,x,y;
    cin>>n>>l>>r>>t;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            cin>>img[i][j];
    int res = 0;
    //挨个元素计算
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            //检查元素的领域
            double avg = 0;
            int cnt = 0;
            for(x=i-r;x<=i+r;x++){
                for(y=j-r;y<=j+r;y++){
                    if(x<0 || y<0 || x>=n || y>=n) continue;
                    else{
                        cnt++;
                        avg+=img[x][y];
                    }
                }
            }
            avg /= cnt;
            if(avg<=t) res++;
        }
    }
    cout<<res;
    return 0;
}