#include <bits/stdc++.h>
#define rep(i,x,n) for(int i=x; i<n; i++)
using namespace std;

template<class T> struct segtree {
	int N, M;
	vector<T> A;
	segtree(const int sz) : N(sz-1), M(1<<32-__builtin_clz(N)+1), A(M) {}
	segtree(const vector<T> &B) : segtree(B.size()) { build(B, 0, N, 1); }
	inline T f(const T &x, const T &y) const { return x^y; }
	T build(const vector<T> &B, int s, int e, int i) {
		if(s==e) return A[i]=B[s];
		int m=s+e>>1;
		return A[i]=f(build(B, s, m, i*2), build(B, m+1, e, i*2+1));
	}
	T get(int l, int r, int s, int e, int i) const {
		if(e<l || r<s) return 0;
		if(l<=s && e<=r) return A[i];
		int m=s+e>>1;
		return f(get(l, r, s, m, i*2), get(l, r, m+1, e, i*2+1));
	}
	T get(int l, int r) const { return get(l, r, 0, N, 1); }
	T set(int p, T x, int s, int e, int i) {
		if(p<s || e<p) return A[i];
		if(p==s && p==e) return A[i]=x;
		int m=s+e>>1;
		return A[i]=f(set(p, x, s, m, i*2), set(p, x, m+1, e, i*2+1));
	}
	T set(int p, T x) { return set(p, x, 0, N, 1); }
};
int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	int N, Q;
	cin>>N>>Q;
	vector<int> A(N);
	rep(i, 0, N) cin>>A[i];
	segtree t(A);
	while(Q--) {
		int a, x, y;
		cin>>a>>x>>y;
		if(a==1) t.set(x-1, y);
		else cout<<t.get(x-1, y-1)<<'\n';
	}
}