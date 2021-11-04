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
        vector<int> adjList[NN];//邻接表
        int func[NN] = {0};//器件功能
        vector<pair<char,int> > conn[NN];//与器件相连的器件或信号
        vector<int> ans[MAXN];//每一次运行的结果
        int inputs[MAXN] = {0};//单次输入信号的值
        int ind[NN] = {0};//入度
        vector<int> processQ;//处理顺序
        queue<int> checkQ;//检测环路
        //第一部分的输入
        int M,N;
        string s;
        int k;
        cin>>M>>N;
        for(int i=1;i<=N;i++){
            cin>>s;//器件功能
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
        //检测环路
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
        //存在环路
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
            //第二部分的输入
            int S,nx,ny;
            cin>>S;
            for(int i=1;i<=S;i++){
                for(int j=0;j<=N;j++)
                    ans[i].push_back(0);
                //接收输入信号的值
                for(int j=1;j<=M;j++)
                    cin>>inputs[j];
                //计算结果
                for(int j=0;j<N;j++){
                    int curId = processQ[j];//当前处理的器件
                    int res = 0;
                    if(conn[curId][0].first=='I') res = inputs[conn[curId][0].second];
                    else res = ans[i][conn[curId][0].second];
                    if(func[curId]==1){//NOT
                        res = !res;
                    }else if(func[curId]==2){//AND
                        for(int l=1;l<conn[curId].size();l++) {
                            char src = conn[curId][l].first;//器件来源
                            int seq = conn[curId][l].second;//来源序号
                            if(src=='I') res &= inputs[seq];
                            else res &= ans[i][seq];
                        }
                    }else if(func[curId]==3){//OR
                        for(int l=1;l<conn[curId].size();l++) {
                            char src = conn[curId][l].first;//器件来源
                            int seq = conn[curId][l].second;//来源序号
                            if(src=='I') res |= inputs[seq];
                            else res |= ans[i][seq];
                        }
                    }else if(func[curId]==4){//XOR
                        for(int l=1;l<conn[curId].size();l++) {
                            char src = conn[curId][l].first;//器件来源
                            int seq = conn[curId][l].second;//来源序号
                            if(src=='I') res ^= inputs[seq];
                            else res ^= ans[i][seq];
                        }
                    }else if(func[curId]==5){//NAND
                        for(int l=1;l<conn[curId].size();l++) {
                            char src = conn[curId][l].first;//器件来源
                            int seq = conn[curId][l].second;//来源序号
                            if(src=='I') res &= inputs[seq];
                            else res &= ans[i][seq];
                        }
                        res = !res;
                    }else{//NOR
                        for(int l=1;l<conn[curId].size();l++) {
                            char src = conn[curId][l].first;//器件来源
                            int seq = conn[curId][l].second;//来源序号
                            if(src=='I') res |= inputs[seq];
                            else res |= ans[i][seq];
                        }
                        res = !res;
                    }
                    ans[i][curId] = res;
                }
            }
            //全部处理完了按要求输出
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