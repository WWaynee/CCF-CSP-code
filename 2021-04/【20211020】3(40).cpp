# include <iostream>
# include <string>
# define NN 10005
using namespace std;
typedef long long ll;
//DHCP����������
int n = 0;//ip��ַ�ش�С
ll tdef,tmax,tmin;
string serverName;

//ip��ַ��
struct node{
    int state = 0;//0δ���� 1������ 2ռ�� 3����
    ll life = 0;//����ʱ��
    string onwer = "";//ռ����
} ips[NN];

//��ʼ��ĳ��ʱ�̵�ip��ַ��
void init(ll time){
    for(ll i=1;i<=n;i++){
        if(ips[i].life<=time && ips[i].life>0){
            //���ڴ�����״̬��ip�������ʱ�� -> ��Ϊδ���䣬ռ������գ�����ʱ������
            if(ips[i].state==1){
                ips[i].state = 0;
                ips[i].onwer = "";
            }//����ռ��״̬��ip�������ʱ�� -> ��Ϊ���ڣ�����ʱ������
            if(ips[i].state==2){
                ips[i].state = 3;
            }
            ips[i].life = 0;
        }
    }
}

void process(ll time,string sender,string receiver,string type,ll ip,ll expired){
    //��ʼ��timeʱ��ip�ص�״̬
    init(time);
    //�жϽ��������Ƿ�Ϊ����������Ϊ *�������ǣ����ж������Ƿ�Ϊ Request�������ǣ��򲻴���
    if(receiver!=serverName && receiver!="*" && type!="REQ") return ;
    //�����Ͳ��� Discover��Request ֮һ���򲻴���
    if(type!="REQ" && type!="DIS") return ;
    //����������Ϊ *�������Ͳ��� Discover������������Ǳ������������� Discover���򲻴���
    if((receiver=="*" && type!="DIS") || (receiver==serverName && type=="DIS")) return ;
    // ����discover����
    if(type=="DIS"){
        int choice = 0,i;//ѡ���ip��ַ
        // ����Ƿ���ռ����Ϊ���������� IP ��ַ
        for(i=1;i<=n;i++){
            if(ips[i].state==2 && ips[i].onwer==sender){
                // ѡȡ�� IP ��ַ
                choice = i;
                break;
            }
        }
        //���û�и�����ռ�õ�ip��ַ
        if(choice==0){
            //ѡȡ��С��״̬Ϊδ����� IP ��ַ
            for(i=1;i<=n;i++)
                if(ips[i].state==0){
                    choice = i; break;
                }
            //�������û�У���ѡȡ��С��״̬Ϊ���ڵ� IP ��ַ
            if(choice==0){
                for(i=1;i<=n;i++)
                    if(ips[i].state==3){
                        choice = i; break;
                    }
            }
            //�������û�У��������ģ��������
            if(choice==0) return ;
        }
        //���� IP ��ַ״̬����Ϊ�����䣬ռ��������Ϊ��������
        ips[choice].state = 1;
        ips[choice].onwer = sender;
        //���ù���ʱ��
        if(expired==0) ips[choice].life = time + tdef;
        else{
            //���ݱ����еĹ���ʱ�̺��յ����ĵ�ʱ�̼������ʱ��
            int gap = expired - time;
            //���ݳ����������Ϊ��������������
            if(gap>tmax) ips[choice].life = time + tmax;
            else if(gap<tmin) ips[choice].life = time + tmin;
            else ips[choice].life = expired;
        }
        //������������ Offer ����
        cout<<serverName<<' '<<sender<<' '<<"OFR"<<' '<<choice<<' '<<ips[choice].life<<endl;
        return ;
    }
    // ����request����
    else if(type=="REQ"){
        //�����������Ǳ���
        if(receiver!=serverName){
            for(int i=1;i<=n;i++){
                if(ips[i].onwer==sender && ips[i].state==1){
                    ips[i].state = 0;
                    ips[i].onwer = "";
                    ips[i].life = 0;
                }
            }
            return ;
        }
        //��鱨���е� IP ��ַ�Ƿ��ڵ�ַ���ڣ�����ռ����Ϊ���������������ǣ��������������� Nak ���ģ��������
        if(ip>n || ips[ip].onwer!=sender) {
            cout<<serverName<<' '<<sender<<' '<<"NAK"<<' '<<ip<<' '<<0<<endl;
            return ;
        }
        //���� IP ��ַ��״̬����Ϊռ��
        ips[ip].state = 2;
        //���� IP ��ַ�Ĺ���ʱ��
        int gap = expired - time;
        if(gap>tmax) ips[ip].life = time + tmax;
        else if(gap<tmin) ips[ip].life = time + tmin;
        else ips[ip].life = expired;
        //������������ Ack ����
        cout<<serverName<<' '<<sender<<' '<<"ACK"<<' '<<ip<<' '<<ips[ip].life<<endl;
        return ;
    }
}

int main(){
    cin>>n>>tdef>>tmax>>tmin>>serverName;
    int cmdNum;//��������
    cin>>cmdNum;
    ll time,ip,expired;
    string sender,receiver,type;
    while(cmdNum--){
        cin>>time>>sender>>receiver>>type>>ip>>expired;//���뱨��
        process( time, sender, receiver, type, ip, expired);
    }
    return 0;
}