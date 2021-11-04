# include <iostream>
# include <vector>
# include <string>
# include <map>
# include <queue>
using namespace std;
const int NN = 505;
const int MAXN = 10005;
int getInt(string s){
    int res = 0;
    for(int i=1;i<s.length();i++){
        res *= 10;
        res += (s[i]-48);
    }
    return res;
}

int main(){
    int Q;
    cin>>Q;
    while(Q--){
        map<string,int> m;
        m["NOT"] = 1;m["AND"] = 2;m["OR"] = 3;m["XOR"] = 4;m["NAND"] = 5;m["NOR"] = 6;
        vector<int> adjList[NN];//�ڽӱ�
        int func[NN] = {0};//��������
        vector<pair<char,int> > conn[NN];//�������������������ź�
        vector<int> ans[MAXN];//ÿһ�����еĽ��
        int inputs[MAXN] = {0};//���������źŵ�ֵ
        int ind[NN] = {0};//���
        vector<int> processQ;//����˳��
        queue<int> checkQ;//��⻷·
        //��һ���ֵ�����
        int M,N;
        string s;
        int k;
        cin>>M>>N;
        for(int i=1;i<=N;i++){
            cin>>s;//��������
            func[i] = m[s];
            cin>>k;
            for(int j=1;j<=k;j++){
                cin>>s;
                int seq = getInt(s);
                if(s[0]=='I') conn[i].push_back({'I',seq});
                else{
                    conn[i].push_back({'O',seq});
                    ind[i]++;
                    adjList[seq].push_back(i);
                }
            }
        }
        //��⻷·
        for(int i=1;i<=N;i++)
            if(ind[i]==0){
                checkQ.push(i);
            }
        while(!checkQ.empty()){
            int key = checkQ.front();
            checkQ.pop();
            processQ.push_back(key);
            for(int i=0;i<adjList[key].size();i++){
                ind[adjList[key][i]]--;
                if(ind[adjList[key][i]]==0) checkQ.push(adjList[key][i]);
            }
        }
        //���ڻ�·
        if(processQ.size()!=N){
            int s,fakem,faken;
            cin>>s;
            for(int i=1;i<=s;i++){
                for(int j=1;j<=M;j++)
                    cin>>fakem;
            }
            for(int i=1;i<=s;i++){
                cin>>fakem;
                for(int i=1;i<=fakem;i++)
                    cin>>faken;
            }
            cout<<"LOOP"<<endl;
        }else{
            //�ڶ����ֵ�����
            int S,nx,ny;
            cin>>S;
            for(int i=1;i<=S;i++){
                for(int j=0;j<=N;j++)
                    ans[i].push_back(0);
                //���������źŵ�ֵ
                for(int j=1;j<=M;j++)
                    cin>>inputs[j];
                //������
                for(int j=0;j<N;j++){
                    int curId = processQ[j];//��ǰ���������
                    int res = 0;
                    if(conn[curId][0].first=='I') res = inputs[conn[curId][0].second];
                    else res = ans[i][conn[curId][0].second];
                    if(func[curId]==1){//NOT
                        res = !res;
                    }else if(func[curId]==2){//AND
                        for(int l=1;l<conn[curId].size();l++) {
                            char src = conn[curId][l].first;//������Դ
                            int seq = conn[curId][l].second;//��Դ���
                            if(src=='I') res &= inputs[seq];
                            else res &= ans[i][seq];
                        }
                    }else if(func[curId]==3){//OR
                        for(int l=1;l<conn[curId].size();l++) {
                            char src = conn[curId][l].first;//������Դ
                            int seq = conn[curId][l].second;//��Դ���
                            if(src=='I') res |= inputs[seq];
                            else res |= ans[i][seq];
                        }
                    }else if(func[curId]==4){//XOR
                        for(int l=1;l<conn[curId].size();l++) {
                            char src = conn[curId][l].first;//������Դ
                            int seq = conn[curId][l].second;//��Դ���
                            if(src=='I') res ^= inputs[seq];
                            else res ^= ans[i][seq];
                        }
                    }else if(func[curId]==5){//NAND
                        for(int l=1;l<conn[curId].size();l++) {
                            char src = conn[curId][l].first;//������Դ
                            int seq = conn[curId][l].second;//��Դ���
                            if(src=='I') res &= inputs[seq];
                            else res &= ans[i][seq];
                        }
                        res = !res;
                    }else{//NOR
                        for(int l=1;l<conn[curId].size();l++) {
                            char src = conn[curId][l].first;//������Դ
                            int seq = conn[curId][l].second;//��Դ���
                            if(src=='I') res |= inputs[seq];
                            else res |= ans[i][seq];
                        }
                        res = !res;
                    }
                    ans[i][curId] = res;
                }
            }
            //ȫ���������˰�Ҫ�����
            for(int i=1;i<=S;i++){
                cin>>nx;
                for(int j=1;j<=nx;j++){
                    cin>>ny;
                    cout<<ans[i][ny]<<' ';
                }
                cout<<endl;
            }
        }
    }
    return 0;
}