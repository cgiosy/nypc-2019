#include <bits/stdc++.h>
#define X(x,y) {cout<<(x)<<' '<<(y);return 0;}
#define rep(i,x,n) for(int i=x; i<n; i++)
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	int N, K;
	cin>>N>>K; --K;
	if(N*N-1==K) X(N/2+N%2, N/2+1);
	for(int i=0; K>=0; i++) {
		int x=(N-i*2-1)*4;
		if(x>K) {
			x=N-i*2-1;
			if(K<x) X(i+K+1, i+1);
			if(K<2*x) X(N-i, i+K-x+1);
			if(K<3*x) X(N-i-K+2*x, N-i);
			if(K<4*x) X(i+1, N-i-K+3*x);
		}
		K-=x;

	}
}