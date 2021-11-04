# include <iostream>
# include <vector>
using namespace std;
int main(){
	int m,th = 0,max = 0,yi,resi;
	cin>>m;
	vector<int> y(m,0);
	vector<bool> res(m,false);
	for(int i=0;i<m;i++){
		cin>>yi>>resi;
		y[i] = yi;
		res[i] = resi; 
	}
	for(int i=0;i<m;i++){
		int num = y[i];
		int cnt = 0;
		for(int j=0;j<m;j++){
			if((y[j]>=num && res[j]) || (y[j]<num && !res[j]))
				cnt++;
		}
		if(cnt>=max){
			max = cnt;
			if(num>th) th = num;
		}
	}
	cout<<th;
	return 0;
}
