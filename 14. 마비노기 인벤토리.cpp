#include <bits/stdc++.h>
#define rep(i,x,n) for(int i=x; i<n; i++)
using namespace std;

int D[18*18][1<<19], N, M, a, b;
char A[20*20];
int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	cin>>M>>N>>a>>b;
	rep(i, 0, N) rep(j, 0, M) cin>>A[j*M+M-i-1], A[j*M+M-i-1]=A[j*M+M-i-1]=='X';
	memset(D, -1, sizeof D);
	function<int(int, int)> f=[&](int i, int j) {
		if(i==N*M) return 0;
		int &x=D[i][j];
		if(x==-1) {
			int k=j<<1&(1<<M+1)-1;
			x=f(i+1, k|A[i]);
			if(!A[i] && i>M && i%M && !(j&(3<<M-1|1))) x=max(x, a+f(i+1, k|1<<M|3));
			if(!A[i] && i%M>=2 && !(j&3)) x=max(x, b+f(i+1, k|7));
		}
		return x;
	};
	vector<int> X, Y;
	function<void(int, int)> g=[&](int i, int j) {
		if(i==N*M) return;
		int x=D[i][j];
		int k=j<<1&(1<<M+1)-1;
		if(x==f(i+1, k|A[i]))
			g(i+1, k|A[i]);
		else if(!A[i] && i>M && i%M && !(j&(3<<M-1|1)) && x==a+f(i+1, k|1<<M|3))
			X.push_back(i), g(i+1, k|1<<M|3);
		else if(!A[i] && i%M>=2 && !(j&3) && x==b+f(i+1, k|7))
			Y.push_back(i), g(i+1, k|7);
	};
	cout<<f(0, 0)<<' ';
	g(0, 0);

	cout<<X.size()<<' '<<Y.size()<<endl;
	for(int x:X) cout<<M-x%M<<' '<<x/M<<endl;
	for(int x:Y) cout<<M-x%M<<' '<<x/M+1<<endl;
}