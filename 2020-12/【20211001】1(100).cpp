# include <iostream>
using namespace std;
int main(){
	int n,w,score,sum = 0;
	cin>>n;
	while(n--){
		cin>>w>>score;
		sum += (w*score);
	}
	if(sum>0) cout<<sum;
	else cout<<0;
	return 0;
}
