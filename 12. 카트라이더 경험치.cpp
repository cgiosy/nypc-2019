#include <bits/stdc++.h>
#define clz(x) (31-__builtin_clz(x))
#define rep(i,x,n) for(int i=x; i<n; i++)
using namespace std;

int A[15][15], D[1<<15], W[1<<15][15];
int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	int N;
	cin>>N;
	rep(i, 0, N) rep(j, 0, N) cin>>A[i][j];
	rep(i, 1, 1<<N) rep(j, 0, N) W[i][j]=W[i^1<<clz(i)][j]+A[j][clz(i)];
	rep(i, 1, 1<<N) rep(j, 0, N) if(i>>j&1) D[i]=max(D[i], D[i^1<<j]+W[i][j]);
	cout<<D[(1<<N)-1];
}