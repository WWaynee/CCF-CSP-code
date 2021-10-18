# include <iostream>
using namespace std;
# define N 605

int img[N][N] = {0};

int main(){
    int n,l,r,t;
    int i,j,x,y,res = 0;
    cin>>n>>l>>r>>t;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            cin>>img[i][j];

    for(i=0;i<n;i++){
        int cnt = 0,rows = 0;
        double sum = 0;
        for(j=0;j<n;j++){
            //����ÿһ�еĵ�һ������
            if(j==0){
                for(x=i-r;x<=i+r;x++){
                    for(y=j-r;y<=j+r;y++){
                        if(x<0 || y<0 || x>=n || y>=n) continue;
                        cnt++;
                        sum += img[x][y];
                    }
                    if(x>=0 && x<n) rows++;
                }
            }
            //ÿһ��֮���Ԫ�ظ���ǰһ��Ԫ�ؼ���
            else{
                //��ȥy-1-r�е�ֵ����y+r�е�ֵ���з�Χ
                if(j-1-r>=0){
                    for(x=i-r;x<=i+r;x++){
                        if(x<0 || x>=n) continue;
                        sum -= img[x][j-1-r];
                    }
                    cnt -= rows;
                }
                if(j+r<n){
                    for(x=i-r;x<=i+r;x++){
                        if(x<0 || x>=n) continue;
                        sum += img[x][j+r];
                    }
                    cnt += rows;
                }
            }
            if(sum/cnt<=t) res++;
        }
    }
    cout<<res;
    return 0;
}