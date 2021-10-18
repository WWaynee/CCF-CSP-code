# include <iostream>
# include <vector>
# include <map>
using namespace std;
int main(){
    int size;//数组长度
    cin>>size;
    vector<int> a(size,0);//原始的B数组
    map<int,vector<int> > m;//数字及其在数组中的所有索引map
    vector<bool> filled(size,false);//filled[i]表示a[i]是否被填为0
    //统计初始的子集数量
    bool flag = false; int count = 0,res = 0;
    for(int i=0;i<size;i++){//在输入过程中统计子集数量
        cin>>a[i];
        m[a[i]].push_back(i);
        if(a[i]==0) filled[i] = true;//数值为0默认已被填为0
        if(flag && a[i]>0) continue;
        else if(!flag && a[i]>0) {
            flag = true;
            count++;
        }else flag = false;
    }
    if(size==1) return count;//数组长度为1时直接返回
    res = count;
    //迭代查找子集数量最大情况
    map<int,vector<int> >::iterator it;
    for(it=m.begin();it!=m.end();it++){
        int key = (*it).first;//数值
        if(key==0) continue;
        vector<int> index = (*it).second;//索引数组
        int len = index.size();
        //迭代索引数组
        for(int i=0;i<len;i++){
            //在开头
            if(index[i]==0){
                //如果右侧已经被填为0
                if(filled[index[i]+1]) count--;
            }
            //在末尾
            else if(index[i]==size-1){
                //如果左侧已经被填为0
                if(filled[index[i]-1]) count--;
            }
            //在内部
            else{
                //左右均被填
                if(filled[index[i]-1] && filled[index[i]+1]) count--;
                //左右均没被填
                else if(!filled[index[i]-1] && !filled[index[i]+1]) count++;
            }
            filled[index[i]] = true;
        }
        if(res<count) res = count;
    }
    cout<<res;
    return 0;
}