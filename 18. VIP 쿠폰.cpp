#include <bits/stdc++.h>
#define rep(i,x,n) for(int i=x; i<n; i++)
#define repr(i,n,x) for(int i=n; i-->x;)
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	int N, M=0, r=0;
	cin>>N;
	vector<pair<int, int>> A(N);
	for(auto&[a,b]:A) cin>>a>>b, M=max(M, a);
	sort(begin(A), end(A), [&](auto &x, auto &y) {
		return x.first+x.second<y.first+y.second;
	});
	if(M<=100000) {
		bitset<100032> V;
		V.set(0);
		rep(k, 0, N) {
			auto[a,b]=A[k];
			repr(i, a, 0) if(V[i]) {
				int x=i+b;
				r=max(r, x);
				if(x<M) V.set(x);
			}
		}
	} else {
		set<int> p;
		vector<int> q;
		p.insert(0);
		for(auto[a,b]:A) {
			for(int i:p) if(i<a) {
				int x=i+b;
				r=max(r, x);
				if(x<M) q.push_back(x);
			}
			for(int i:q) p.insert(i);
			q.clear();
		}
	}
	cout<<r;
}
