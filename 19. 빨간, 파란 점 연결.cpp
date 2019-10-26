#include <bits/stdc++.h>
#define rep(i,x,n) for(int i=x; i<n; i++)
using namespace std;
using ll=long long;
constexpr ll INF=1e12;

struct pi { int x, y; bool t; };
int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	int N, M;
	cin>>N>>M; swap(N, M+=N);
	vector<pi> A(N);
	rep(i, 0, M) cin>>A[i].x>>A[i].y, A[i].t=false;
	rep(i, M, N) cin>>A[i].x>>A[i].y, A[i].t=true;

	int p=0;
	rep(i, 1, N) if(A[i].x==A[p].x ? A[i].y<A[p].y : A[i].x<A[p].x) p=i;
	swap(A[0], A[p]);
	sort(begin(A)+1, end(A), [&](pi a, pi b) {
		return A[0].x*ll(a.y)+a.x*ll(b.y)+b.x*ll(A[0].y)<A[0].y*ll(a.x)+a.y*ll(b.x)+b.y*ll(A[0].x);
	});

	auto f=[&](int i, int j) {
		if(A[i].t==A[j].t) return INF;
		return abs(A[i].x-A[j].x)+ll(abs(A[i].y-A[j].y));
	};
	vector<vector<ll>> D(N, vector<ll>(N, INF));
	rep(i, 0, N) D[i][i]=0;
	rep(i, 0, N-1) D[i][i+1]=f(i, i+1);
	rep(k, 2, N) rep(i, 0, N-k) rep(j, i, i+k)
		D[i][i+k]=min({D[i][i+k], D[i][j]+D[j][i+k], D[i][j]+D[j+1][i+k]+f(i, i+k)});
	ll r=D[0][N-1];
	cout<<(r<INF ? r : -1);
}
