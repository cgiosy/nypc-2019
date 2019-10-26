#include <bits/stdc++.h>
#define rep(i,x,n) for(int i=x; i<n; i++)
using namespace std;

struct dset {
	vector<int> P, R;
	dset(const int N) : P(N), R(N, 1) { iota(begin(P), end(P), 0); };
	int root(const int i) {
		return P[i]!=i ? P[i]=root(P[i]) : i;
	}
	int merge(int i, int j) {
		i=root(i), j=root(j);
		if(i==j) return 0;
		if(R[i]<R[j]) swap(i, j);
		P[j]=i;
		return R[i]+=R[j];
	}
};
int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	int N, Q, m=1;
	cin>>N>>Q;
	dset ds(N);
	vector<int> A(N), B(N), C(N), X(N), Y(N);
	while(Q--) {
		int x, y;
		cin>>x>>y; --x, --y;
		X[x]++, Y[y]++;
		m=max(m, ds.merge(x, y));
	}
	rep(i, 0, N) {
		int g=ds.root(i);
		if(A[g]<X[i] || A[g]==X[i] && B[g]>Y[i])
			A[g]=X[i], B[g]=Y[i], C[g]=i;
	}
	int k=N;
	rep(i, 0, N) if(ds.R[ds.root(i)]==m) k=min(k, C[ds.root(i)]);
	cout<<k+1;
}