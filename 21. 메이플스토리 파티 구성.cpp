#include <bits/stdc++.h>
#define rep(i,x,n) for(int i=x; i<n; i++)
using namespace std;
constexpr int SQRT=316;

struct query {
	int l, r, i;
	bool operator<(const query b) const {
		int x=l/SQRT, y=b.l/SQRT;
		return x<y || (x==y && r<b.r);
	}
};
int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	int N, Q;
	cin>>N>>Q;
	vector<int> A(N), C(N);
	vector<query> B(Q*2);
	vector<size_t> D(Q*2);
	bitset<100096> V;
	hash<decltype(V)> h;
	rep(i, 0, N) cin>>A[i], --A[i];
	rep(i, 0, Q*2) cin>>B[i].l>>B[i].r, --B[i].l, --B[i].r, B[i].i=i;
	sort(begin(B), end(B));
	int u=0, v=0;
	C[A[0]]++, V.set(A[0]);
	for(auto[l,r,k]:B) {
		for(int i=u; i-->l;) if(int x=A[i]; !C[x]++) V.set(x);
		for(int i=v; i++<r;) if(int x=A[i]; !C[x]++) V.set(x);
		for(int i=u; i<l; i++) if(int x=A[i]; !--C[x]) V.reset(x);
		for(int i=v; i>r; i--) if(int x=A[i]; !--C[x]) V.reset(x);
		u=l, v=r;
		D[k]=h(V);
	}
	rep(i, 0, Q) cout<<(D[i*2]==D[i*2+1] ? "YES" : "NO")<<'\n';
}