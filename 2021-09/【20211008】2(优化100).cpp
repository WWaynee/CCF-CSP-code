# include <iostream>
# include <vector>
# include <map>
using namespace std;
int main(){
    int size;//���鳤��
    cin>>size;
    vector<int> a(size,0);//ԭʼ��B����
    map<int,vector<int> > m;//���ּ����������е���������map
    vector<bool> filled(size,false);//filled[i]��ʾa[i]�Ƿ���Ϊ0
    //ͳ�Ƴ�ʼ���Ӽ�����
    bool flag = false; int count = 0,res = 0;
    for(int i=0;i<size;i++){//�����������ͳ���Ӽ�����
        cin>>a[i];
        m[a[i]].push_back(i);
        if(a[i]==0) filled[i] = true;//��ֵΪ0Ĭ���ѱ���Ϊ0
        if(flag && a[i]>0) continue;
        else if(!flag && a[i]>0) {
            flag = true;
            count++;
        }else flag = false;
    }
    if(size==1) return count;//���鳤��Ϊ1ʱֱ�ӷ���
    res = count;
    //���������Ӽ�����������
    map<int,vector<int> >::iterator it;
    for(it=m.begin();it!=m.end();it++){
        int key = (*it).first;//��ֵ
        if(key==0) continue;
        vector<int> index = (*it).second;//��������
        int len = index.size();
        //������������
        for(int i=0;i<len;i++){
            //�ڿ�ͷ
            if(index[i]==0){
                //����Ҳ��Ѿ�����Ϊ0
                if(filled[index[i]+1]) count--;
            }
            //��ĩβ
            else if(index[i]==size-1){
                //�������Ѿ�����Ϊ0
                if(filled[index[i]-1]) count--;
            }
            //���ڲ�
            else{
                //���Ҿ�����
                if(filled[index[i]-1] && filled[index[i]+1]) count--;
                //���Ҿ�û����
                else if(!filled[index[i]-1] && !filled[index[i]+1]) count++;
            }
            filled[index[i]] = true;
        }
        if(res<count) res = count;
    }
    cout<<res;
    return 0;
}