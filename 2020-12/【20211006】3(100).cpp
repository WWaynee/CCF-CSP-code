// 1. ע�����ld��lrΪ0�������ƣ�ֻ���ڲ�Ϊ0ʱ����Ҫ����Ƿ�����
// 2. ע�⿴��Ŀ�����ƣ����N���������ģ��Сʱ��vector��map���Ż�ʱ������
# include <iostream>
# include <string>
# include <vector>
# include <map>
using namespace std;
typedef long long ll;
# define N 1500005// N>2^20-1

int fileId = 1;//�ļ����

struct file{
    ll ld = 0,lr = 0;//Ŀ¼��������
    ll lds = 0,lrs = 0;//�Ѿ�ʹ�õ�����ܺ�
    ll size = 0;//�ļ���С
    int type = 0;//�ļ����ͣ�1��ͨ�ļ���2Ŀ¼�ļ�
    int father = 0;//���ڵ�
    map<string,int> child;
}File[N];

//���ߺ���1����·����Ϊ�ַ�������
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

vector<pair<int,string> > retreat;//�����Ҫ�������ļ�

//���ߺ���2������������Ŀ¼����Ϊ��ɾ���ļ����Բ���Ҫ�ı����
void drawback(){
    int delsz = retreat.size();
    for(int i=0;i<delsz;i++){
        File[retreat[i].first].child.erase(retreat[i].second);
    }
    retreat.clear();
}

//���ߺ���3���ݹ�ɾ��ĳ����Ŀ¼��ĳ�����ֵ�Ŀ¼�ļ�
void delDir(int dirId,string name){
    int curId = File[dirId].child[name];//�ҵ������ļ���id
    if(curId==0) return ;
    map<string,int> childfiles = File[curId].child;
    if(childfiles.size()!=0) {
        map<string, int>::iterator it;
        for (it = childfiles.begin(); it != childfiles.end(); it++) {
            delDir(curId, (*it).first);//�ݹ�ɾ����Ŀ¼���ļ�
            File[curId].child.erase((*it).first);
        }
    }
    File[dirId].child.erase(name);
}

//������ͨ�ļ�
bool create(string path, ll size){
    // 1. ��ȡ·���ϵ��ļ�������
    vector<string> pathfiles = split(path);
    int pathsize = pathfiles.size();
    // 2. ������һ��֮ǰ���ļ�����������Ŀ¼
    int dirId = 0, curId;//�Ӹ�Ŀ¼��ʼ
    for(int i=0;i<pathsize-1;i++){
        curId = File[dirId].child[pathfiles[i]];//��ȡ��Ŀ¼��id
        // 2.1 ���Ŀ¼�ļ��������򴴽�Ŀ¼
        if(curId==0){
            File[fileId].type = 2;
            File[fileId].father = dirId;
            File[dirId].child[pathfiles[i]] = fileId;
            retreat.push_back(pair<int,string>{dirId,pathfiles[i]});//���볷�������з����������������Ŀ¼
            dirId = fileId;
            fileId++;
        }
        // 2.2 �����ͬ����ͨ�ļ�������ʧ�ܣ�����֮ǰ������Ŀ¼
        else if(File[curId].type==1){
            return false;
        }
        // 2.3 �������ͬ��Ŀ¼�ļ��������������
        else if(File[curId].type==2){
            dirId = curId;
        }
    }
    // 3. ������һ���ļ���
    curId = File[dirId].child[pathfiles[pathsize-1]];
    // 3.1 �����ͨ�ļ������ڣ�������󴴽�
    if(curId==0){
        // 3.1.1 ��鸸Ŀ¼���
        if(File[dirId].ld>0 && File[dirId].ld - File[dirId].lds < size) {//�����㸸Ŀ¼�������
            drawback();
            return false;
        }
        // 3.1.2 �������Ŀ¼������
        int rootId = dirId;
        while(rootId!=-1){//һֱ�鵽��Ŀ¼
            if(File[rootId].lr>0 && (File[rootId].lr - File[rootId].lrs < size)){
                drawback();
                return false;
            }
            rootId = File[rootId].father;
        }
        // 3.1.3 ������Դ�����ͨ�ļ�
        // 3.1.3.1 ����ļ�
        File[fileId].father = dirId;
        File[fileId].size = size;
        File[fileId].type = 1;
        File[dirId].child[pathfiles[pathsize-1]] = fileId;
        fileId++;
        // 3.1.3.2 �޸ĸ�Ŀ¼���ld
        File[dirId].lds += size;
        // 3.1.3.3 �޸�����Ŀ¼���lr
        rootId = dirId;
        while(rootId!=-1){
            File[rootId].lrs += size;
            rootId = File[rootId].father;
        }
        retreat.clear();
        return true;
    }// 3.2 �����ͨ�ļ��Ѿ����ڣ���������滻
    else if(File[curId].type==1){
        // 3.2.1 ��鸸Ŀ¼���ld
        if(File[dirId].ld>0 && File[curId].size<size && File[dirId].ld - File[dirId].lds < size - File[curId].size){
            return false;
        }
        // 3.2.2 �������Ŀ¼���lr
        int rootId = dirId;
        while(rootId!=-1){
            if(File[rootId].lr>0 && File[curId].size<size && File[rootId].lr - File[rootId].lrs < size - File[curId].size){
                return false;
            }
            rootId = File[rootId].father;
        }
        // 3.3.3 ������ͨ�ļ�
        // 3.3.3.1 �޸ĸ�Ŀ¼���ld
        File[dirId].lds += (size - File[curId].size);
        // 3.3.3.2 �޸�����Ŀ¼���lr
        rootId = dirId;
        while(rootId!=-1){
            File[rootId].lrs += (size - File[curId].size);
            rootId = File[rootId].father;
        }
        // 3.3.3.3 �滻�ļ���С
        File[curId].size = size;
        return true;
    }// 3.3 �����ͬ��Ŀ¼�ļ��򴴽�ʧ��
    else if(File[curId].type==2){
        return false;
    }
    return true;
}

//ɾ���ļ�
bool remove(string path){
    // ��ɾ����Ŀ¼����
    vector<string> pathfiles = split(path);
    int pathsize = pathfiles.size();
    int dirId = 0;//�Ӹ�Ŀ¼��ʼ����
    for(int i=0;i<pathsize-1;i++){
        int curId = File[dirId].child[pathfiles[i]];
        // 1. Ҫɾ�����ļ�������
        if(curId==0) return true;
        // 2. ��������
        dirId = curId;
    }
    // 3. ������һ���ļ���Ŀ¼�ļ�����ͨ�ļ������ǲ�����
    int curId = File[dirId].child[pathfiles[pathsize-1]];
    if(curId==0){//������
        return true;
    }else{//Ҫɾ���Ѵ��ڵ��ļ�
        delDir(dirId,pathfiles[pathsize-1]);
        if(File[curId].type==1){//ɾ��������ͨ�ļ�
            File[dirId].lds -= File[curId].size;
            int rootId = dirId;
            while(rootId!=-1){
                File[rootId].lrs -= File[curId].size;
                rootId = File[rootId].father;
            }
        }else{//ɾ������Ŀ¼�ļ�
            int rootId = dirId;
            while(rootId!=-1){
                File[rootId].lrs -= File[curId].lrs;
                rootId = File[rootId].father;
            }
        }
    }
    return true;
}

// �������
bool quote(string path,ll ld_,ll lr_){
    vector<string> pathfiles = split(path);
    int pathsize = pathfiles.size();
    int dirId = 0,curId = 0;
    // 1. ���·���Ƿ�������
    for(int i=0;i<pathsize;i++){
        curId = File[dirId].child[pathfiles[i]];
        // ������Ϊ�����ڵ�Ŀ¼����ͨ�ļ��������
        if(curId==0 || File[curId].type==1) return false;
        dirId = curId;
    }
    // 2. ����Ŀ¼��ld����ܷ����ã�ע�����������ld��lrΪ0��������
    if((ld_>0 && File[curId].lds > ld_) || (lr_>0 && File[curId].lrs > lr_)) return false;
    File[curId].ld = ld_;
    File[curId].lr = lr_;
    return true;
}

int main(){
    //��Ŀ¼����
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