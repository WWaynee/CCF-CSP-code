# include <stdio.h>
int ps = 0;
int st = 0;
int xl,yd,xr,yu;
bool inter(int x,int y){
    if((xl<=x && xr>=x) && (yd<=y && yu>=y))
        return true;
    return false;
}
int main()
{
    int n,k,t;
    int i;
    int tx,ty,flag,lockp,locks;
    scanf("%d %d %d %d %d %d %d",&n,&k,&t,&xl,&yd,&xr,&yu);
    while(n--){
        flag = 0;
        lockp = 0;
        locks = 0;
        for(i=0;i<t;i++){
            scanf("%d %d",&tx,&ty);
            if(inter(tx,ty)){
                if(lockp==0){
                    ps++;lockp=1;
                }
                flag++;
            }else{
                flag = 0;
            }
            if(flag>=k && locks==0){
                st++;locks=1;
            }
        }
    }
    printf("%d\n%d",ps,st);
    return 0;
}