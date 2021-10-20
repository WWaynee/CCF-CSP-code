// 1. 注意配额ld、lr为0代表不限制，只有在不为0时才需要检查是否满足
// 2. 注意看题目的限制，如果N或者输入规模较小时用vector或map来优化时间性能
# include <iostream>
# include <string>
# include <vector>
# include <map>
using namespace std;
typedef long long ll;
# define N 1500005// N>2^20-1

int fileId = 1;//文件编号

struct file{
    ll ld = 0,lr = 0;//目录配额，后代配额
    ll lds = 0,lrs = 0;//已经使用的配额总和
    ll size = 0;//文件大小
    int type = 0;//文件类型：1普通文件，2目录文件
    int father = 0;//父节点
    map<string,int> child;
}File[N];

//工具函数1：将路径切为字符串数组
vector<string> split(string path){
    vector<string> res;
    int beg = 1,end = 1;
    for(;end<path.size() && beg<path.size();){
        if(path[end]!='/') end++;
        else {
            res.push_back(path.substr(beg,end-beg));
            beg = (++end);
        }
    }
    if(beg!=path.size())
        res.push_back(path.substr(beg,end-beg));
    return res;
}

vector<pair<int,string> > retreat;//标记需要撤销的文件

//工具函数2：撤销创建的目录，因为不删除文件所以不需要改变配额
void drawback(){
    int delsz = retreat.size();
    for(int i=0;i<delsz;i++){
        File[retreat[i].first].child.erase(retreat[i].second);
    }
    retreat.clear();
}

//工具函数3：递归删除某个父目录下某个名字的目录文件
void delDir(int dirId,string name){
    int curId = File[dirId].child[name];//找到该子文件的id
    if(curId==0) return ;
    map<string,int> childfiles = File[curId].child;
    if(childfiles.size()!=0) {
        map<string, int>::iterator it;
        for (it = childfiles.begin(); it != childfiles.end(); it++) {
            delDir(curId, (*it).first);//递归删除子目录的文件
            File[curId].child.erase((*it).first);
        }
    }
    File[dirId].child.erase(name);
}

//创建普通文件
bool create(string path, ll size){
    // 1. 获取路径上的文件名数组
    vector<string> pathfiles = split(path);
    int pathsize = pathfiles.size();
    // 2. 检查最后一级之前的文件名，必须是目录
    int dirId = 0, curId;//从父目录开始
    for(int i=0;i<pathsize-1;i++){
        curId = File[dirId].child[pathfiles[i]];//获取该目录的id
        // 2.1 如果目录文件不存在则创建目录
        if(curId==0){
            File[fileId].type = 2;
            File[fileId].father = dirId;
            File[dirId].child[pathfiles[i]] = fileId;
            retreat.push_back(pair<int,string>{dirId,pathfiles[i]});//加入撤销集合中方便后续撤销创建的目录
            dirId = fileId;
            fileId++;
        }
        // 2.2 如果有同名普通文件，创建失败，撤销之前创建的目录
        else if(File[curId].type==1){
            return false;
        }
        // 2.3 如果已有同名目录文件，无需操作其他
        else if(File[curId].type==2){
            dirId = curId;
        }
    }
    // 3. 检查最后一级文件名
    curId = File[dirId].child[pathfiles[pathsize-1]];
    // 3.1 如果普通文件不存在，检查配额后创建
    if(curId==0){
        // 3.1.1 检查父目录配额
        if(File[dirId].ld>0 && File[dirId].ld - File[dirId].lds < size) {//不满足父目录配额条件
            drawback();
            return false;
        }
        // 3.1.2 检查祖先目录后代配额
        int rootId = dirId;
        while(rootId!=-1){//一直查到根目录
            if(File[rootId].lr>0 && (File[rootId].lr - File[rootId].lrs < size)){
                drawback();
                return false;
            }
            rootId = File[rootId].father;
        }
        // 3.1.3 如果可以创建普通文件
        // 3.1.3.1 添加文件
        File[fileId].father = dirId;
        File[fileId].size = size;
        File[fileId].type = 1;
        File[dirId].child[pathfiles[pathsize-1]] = fileId;
        fileId++;
        // 3.1.3.2 修改父目录配额ld
        File[dirId].lds += size;
        // 3.1.3.3 修改祖先目录配额lr
        rootId = dirId;
        while(rootId!=-1){
            File[rootId].lrs += size;
            rootId = File[rootId].father;
        }
        retreat.clear();
        return true;
    }// 3.2 如果普通文件已经存在，检查配额后替换
    else if(File[curId].type==1){
        // 3.2.1 检查父目录配额ld
        if(File[dirId].ld>0 && File[curId].size<size && File[dirId].ld - File[dirId].lds < size - File[curId].size){
            return false;
        }
        // 3.2.2 检查祖先目录配额lr
        int rootId = dirId;
        while(rootId!=-1){
            if(File[rootId].lr>0 && File[curId].size<size && File[rootId].lr - File[rootId].lrs < size - File[curId].size){
                return false;
            }
            rootId = File[rootId].father;
        }
        // 3.3.3 覆盖普通文件
        // 3.3.3.1 修改父目录配额ld
        File[dirId].lds += (size - File[curId].size);
        // 3.3.3.2 修改祖先目录配额lr
        rootId = dirId;
        while(rootId!=-1){
            File[rootId].lrs += (size - File[curId].size);
            rootId = File[rootId].father;
        }
        // 3.3.3.3 替换文件大小
        File[curId].size = size;
        return true;
    }// 3.3 如果是同名目录文件则创建失败
    else if(File[curId].type==2){
        return false;
    }
    return true;
}

//删除文件
bool remove(string path){
    // 不删除根目录！！
    vector<string> pathfiles = split(path);
    int pathsize = pathfiles.size();
    int dirId = 0;//从根目录开始查找
    for(int i=0;i<pathsize-1;i++){
        int curId = File[dirId].child[pathfiles[i]];
        // 1. 要删除的文件不存在
        if(curId==0) return true;
        // 2. 继续迭代
        dirId = curId;
    }
    // 3. 检查最后一级文件是目录文件，普通文件，还是不存在
    int curId = File[dirId].child[pathfiles[pathsize-1]];
    if(curId==0){//不存在
        return true;
    }else{//要删除已存在的文件
        delDir(dirId,pathfiles[pathsize-1]);
        if(File[curId].type==1){//删除的是普通文件
            File[dirId].lds -= File[curId].size;
            int rootId = dirId;
            while(rootId!=-1){
                File[rootId].lrs -= File[curId].size;
                rootId = File[rootId].father;
            }
        }else{//删除的是目录文件
            int rootId = dirId;
            while(rootId!=-1){
                File[rootId].lrs -= File[curId].lrs;
                rootId = File[rootId].father;
            }
        }
    }
    return true;
}

// 设置配额
bool quote(string path,ll ld_,ll lr_){
    vector<string> pathfiles = split(path);
    int pathsize = pathfiles.size();
    int dirId = 0,curId = 0;
    // 1. 检查路径是否有问题
    for(int i=0;i<pathsize;i++){
        curId = File[dirId].child[pathfiles[i]];
        // 不允许为不存在的目录和普通文件设置配额
        if(curId==0 || File[curId].type==1) return false;
        dirId = curId;
    }
    // 2. 检查该目录的ld配额能否设置，注意特殊情况，ld或lr为0代表不限制
    if((ld_>0 && File[curId].lds > ld_) || (lr_>0 && File[curId].lrs > lr_)) return false;
    File[curId].ld = ld_;
    File[curId].lr = lr_;
    return true;
}

int main(){
    //根目录设置
    File[0].father = -1;
    File[0].type = 2;
    int num;
    char type;
    string path;
    ll ld_,lr_,size;
    cin>>num;
    bool flag;
    while(num--){
        cin>>type;
        switch(type){
            case 'C':cin>>path>>size;flag=create(path,size);break;
            case 'R':cin>>path;flag=remove(path);break;
            case 'Q':cin>>path>>ld_>>lr_;flag=quote(path,ld_,lr_);break;
            default:break;
        }
        flag?(cout<<'Y'<<endl):(cout<<'N'<<endl);
    }
    return 0;
}