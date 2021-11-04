// 1.discover报文的ip地址为0
// 2.nak报文过期时刻为0
// 3.服务器收到request报文如果选择的不是本服务器的ip则解除ip占用
# include <iostream>
# include <string>
# define NN 10005
using namespace std;
//DHCP服务器配置
int n = 0;//ip地址池大小
int tdef,tmax,tmin;
string serverName;

int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}

//ip地址池
struct node{
    int state = 0;//0未分配 1待分配 2占用 3过期
    int life = 0;//过期时刻
    string owner = "";//占用者
} ips[NN];

//初始化某个时刻的ip地址池
void init(int time){
    for(int i=1;i<=n;i++){
        if(ips[i].life<=time && ips[i].life>0){
            //处于待分配状态的ip到达过期时刻 -> 变为未分配，占用者清空，过期时刻清零
            if(ips[i].state==1){
                ips[i].state = 0;
                ips[i].owner = "";
            }//处于占用状态的ip到达过期时刻 -> 变为过期，过期时刻清零
            if(ips[i].state==2){
                ips[i].state = 3;
            }
            ips[i].life = 0;
        }
    }
}

//查找第一个状态为n为ip地址
int findIpByState(int state){
    for(int i=1;i<=n;i++){
        if(ips[i].state==state) return i;
    }
    return 0;//没有则返回0
}

//查找占用者为owner的ip地址
int findIpByOwner(string owner){
    for(int i=1;i<=n;i++){
        if(ips[i].owner==owner) return i;
    }
    return 0;//没有则返回0
}

void process(int time,string sender,string receiver,string type,int ip,int expired){
    //初始化time时刻ip池的状态
    //判断接收主机是否为本机，或者为 *，若不是，则判断类型是否为 Request，若不是，则不处理
    if(receiver!=serverName && receiver!="*" && type!="REQ") return ;
    //若类型不是 Discover、Request 之一，则不处理
    if(type!="REQ" && type!="DIS") return ;
    //若接收主机为 *，但类型不是 Discover，或接收主机是本机，但类型是 Discover，则不处理
    if((receiver=="*" && type!="DIS") || (receiver==serverName && type=="DIS")) return ;
    init(time);
    // 处理discover报文
    if(type=="DIS"){
        int choice = findIpByOwner(sender);
        //如果没有该主机占用的ip地址
        //选取最小的状态为未分配的 IP 地址
        if(!choice) choice = findIpByState(0);
        //如果上面没有，就选取最小的状态为过期的 IP 地址
        if(!choice) choice = findIpByState(3);
        //如果还是没有，不处理报文，处理结束
        if(!choice) return ;
        //将该 IP 地址状态设置为待分配，占用者设置为发送主机
        ips[choice].state = 1;
        ips[choice].owner = sender;
        //设置过期时间
        if(!expired) ips[choice].life = time + tdef;
        else{
            //根据报文中的过期时刻和收到报文的时刻计算过期时间
            //根据超限情况设置为允许的最早或最晚
            ips[choice].life = time + min(max(tmin,expired-time),tmax);
        }
        //向发送主机发送Offer报文
        cout<<serverName<<' '<<sender<<' '<<"OFR"<<' '<<choice<<' '<<ips[choice].life<<endl;
        return ;
    }
    // 处理request报文
    else if(type=="REQ"){
        //接收主机不是本机
        if(receiver!=serverName){
            for(int i=1;i<=n;i++){
                if(ips[i].owner==sender && ips[i].state==1){
                    ips[i].state = 0;
                    ips[i].owner = "";
                    ips[i].life = 0;
                }
            }
            return ;
        }
        //检查报文中的 IP 地址是否在地址池内，且其占用者为发送主机，若不是，则向发送主机发送 Nak 报文，处理结束
        if(ip>n || ip<1 || ips[ip].owner!=sender) {
            cout<<serverName<<' '<<sender<<' '<<"NAK"<<' '<<ip<<' '<<0<<endl;
            return ;
        }
        //将该 IP 地址的状态设置为占用
        ips[ip].state = 2;
        //设置 IP 地址的过期时刻
        if(expired==0) ips[ip].life = time + tdef;
        else ips[ip].life = time + min(max(tmin,expired-time),tmax);
        //发送主机发送 Ack 报文
        cout<<serverName<<' '<<sender<<' '<<"ACK"<<' '<<ip<<' '<<ips[ip].life<<endl;
        return ;
    }
}

int main(){
    cin>>n>>tdef>>tmax>>tmin>>serverName;
    int cmdNum;//命令数量
    cin>>cmdNum;
    int time,ip,expired;
    string sender,receiver,type;
    while(cmdNum--){
        cin>>time>>sender>>receiver>>type>>ip>>expired;//输入报文
        process(time,sender,receiver,type,ip,expired);
    }
    return 0;
}