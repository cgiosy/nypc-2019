#include <bits/stdc++.h>
#define rep(i,x,n) for(int i=x; i<n; i++)
using namespace std;

struct iii {
	int k, i, j;
	bool operator<(const iii b) const { return k>b.k; }
};
int A[1000][1000], D[4][1000][1000];
int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	memset(D, 0x3f, sizeof D);
	int N, M, K, sy, sx;
	cin>>N>>M>>K>>sy>>sx;
	rep(i, 0, N) rep(j, 0, M) cin>>A[i][j];
	priority_queue<iii> q;
	q.push({D[K%4][sy][sx]=K, sy, sx});
	while(!q.empty()) {
		auto[k,i,j]=q.top(); q.pop();
		const int dy[4]={0, -1, 0, 1}, dx[4]={1, 0, -1, 0};
		rep(t, 0, 4) if(int di=(A[i][j]+k+t)%4, y=i+dy[di], x=j+dx[di]; y>=0 && x>=0 && y<N && x<M) {
			int &z=D[(k+t+1)%4][y][x];
			if(k+t+1<z) q.push({z=k+t+1, y, x});
		}
	}
	rep(i, 0, N) {
		rep(j, 0, M) cout<<min({D[0][i][j], D[1][i][j], D[2][i][j], D[3][i][j]})<<' ';
		cout<<'\n';
	}
}