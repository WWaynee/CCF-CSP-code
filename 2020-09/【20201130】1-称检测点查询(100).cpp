# include <stdio.h>
const int len = 2005;
int i1=0,i2=0,i3=0;//序号
int d1=4999999,d2=5000000,d3=5000001;//距离 d1<=d2<=d3
int main()
{
    int n,x,y,tx,ty;
    int i,j,k,d;
    scanf("%d %d %d",&n,&x,&y);
    for(i=1;i<=n;i++){
        scanf("%d %d",&tx,&ty);
        d = (tx-x)*(tx-x) + (ty-y)*(ty-y);//计算距离的平方
        if(d<d1 || (d==d1 && i1>i)){
            d3 = d2;d2 = d1;
            i3 = i2;i2 = i1;
            d1 = d;i1 = i;
        }
        else if(d<d2 || (d==d2 && i2>i)){
            d3 = d2;i3 = i2;
            d2 = d;i2 = i;
        }
        else if(d<d3 || (d==d3 && i3>i)){
            d3 = d;i3 = i;
        }
    }
    printf("%d\n%d\n%d",i1,i2,i3);
    return 0;
}