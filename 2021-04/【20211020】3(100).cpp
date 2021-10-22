// 1.discover���ĵ�ip��ַΪ0
// 2.nak���Ĺ���ʱ��Ϊ0
// 3.�������յ�request�������ѡ��Ĳ��Ǳ���������ip����ipռ��
# include <iostream>
# include <string>
# define NN 10005
using namespace std;
//DHCP����������
int n = 0;//ip��ַ�ش�С
int tdef,tmax,tmin;
string serverName;

int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}

//ip��ַ��
struct node{
    int state = 0;//0δ���� 1������ 2ռ�� 3����
    int life = 0;//����ʱ��
    string owner = "";//ռ����
} ips[NN];

//��ʼ��ĳ��ʱ�̵�ip��ַ��
void init(int time){
    for(int i=1;i<=n;i++){
        if(ips[i].life<=time && ips[i].life>0){
            //���ڴ�����״̬��ip�������ʱ�� -> ��Ϊδ���䣬ռ������գ�����ʱ������
            if(ips[i].state==1){
                ips[i].state = 0;
                ips[i].owner = "";
            }//����ռ��״̬��ip�������ʱ�� -> ��Ϊ���ڣ�����ʱ������
            if(ips[i].state==2){
                ips[i].state = 3;
            }
            ips[i].life = 0;
        }
    }
}

//���ҵ�һ��״̬ΪnΪip��ַ
int findIpByState(int state){
    for(int i=1;i<=n;i++){
        if(ips[i].state==state) return i;
    }
    return 0;//û���򷵻�0
}

//����ռ����Ϊowner��ip��ַ
int findIpByOwner(string owner){
    for(int i=1;i<=n;i++){
        if(ips[i].owner==owner) return i;
    }
    return 0;//û���򷵻�0
}

void process(int time,string sender,string receiver,string type,int ip,int expired){
    //��ʼ��timeʱ��ip�ص�״̬
    //�жϽ��������Ƿ�Ϊ����������Ϊ *�������ǣ����ж������Ƿ�Ϊ Request�������ǣ��򲻴���
    if(receiver!=serverName && receiver!="*" && type!="REQ") return ;
    //�����Ͳ��� Discover��Request ֮һ���򲻴���
    if(type!="REQ" && type!="DIS") return ;
    //����������Ϊ *�������Ͳ��� Discover������������Ǳ������������� Discover���򲻴���
    if((receiver=="*" && type!="DIS") || (receiver==serverName && type=="DIS")) return ;
    init(time);
    // ����discover����
    if(type=="DIS"){
        int choice = findIpByOwner(sender);
        //���û�и�����ռ�õ�ip��ַ
        //ѡȡ��С��״̬Ϊδ����� IP ��ַ
        if(!choice) choice = findIpByState(0);
        //�������û�У���ѡȡ��С��״̬Ϊ���ڵ� IP ��ַ
        if(!choice) choice = findIpByState(3);
        //�������û�У��������ģ��������
        if(!choice) return ;
        //���� IP ��ַ״̬����Ϊ�����䣬ռ��������Ϊ��������
        ips[choice].state = 1;
        ips[choice].owner = sender;
        //���ù���ʱ��
        if(!expired) ips[choice].life = time + tdef;
        else{
            //���ݱ����еĹ���ʱ�̺��յ����ĵ�ʱ�̼������ʱ��
            //���ݳ����������Ϊ��������������
            ips[choice].life = time + min(max(tmin,expired-time),tmax);
        }
        //������������Offer����
        cout<<serverName<<' '<<sender<<' '<<"OFR"<<' '<<choice<<' '<<ips[choice].life<<endl;
        return ;
    }
    // ����request����
    else if(type=="REQ"){
        //�����������Ǳ���
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
        //��鱨���е� IP ��ַ�Ƿ��ڵ�ַ���ڣ�����ռ����Ϊ���������������ǣ��������������� Nak ���ģ��������
        if(ip>n || ip<1 || ips[ip].owner!=sender) {
            cout<<serverName<<' '<<sender<<' '<<"NAK"<<' '<<ip<<' '<<0<<endl;
            return ;
        }
        //���� IP ��ַ��״̬����Ϊռ��
        ips[ip].state = 2;
        //���� IP ��ַ�Ĺ���ʱ��
        if(expired==0) ips[ip].life = time + tdef;
        else ips[ip].life = time + min(max(tmin,expired-time),tmax);
        //������������ Ack ����
        cout<<serverName<<' '<<sender<<' '<<"ACK"<<' '<<ip<<' '<<ips[ip].life<<endl;
        return ;
    }
}

int main(){
    cin>>n>>tdef>>tmax>>tmin>>serverName;
    int cmdNum;//��������
    cin>>cmdNum;
    int time,ip,expired;
    string sender,receiver,type;
    while(cmdNum--){
        cin>>time>>sender>>receiver>>type>>ip>>expired;//���뱨��
        process(time,sender,receiver,type,ip,expired);
    }
    return 0;
}