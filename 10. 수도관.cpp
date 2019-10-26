#include <bits/stdc++.h>
#define rep(i,x,n) for(int i=x; i<n; i++)
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	int N, e;
	cin>>N>>e;
	vector<pair<int, int>> A(N);
	for(auto&[y,x]:A) cin>>y>>x;
	sort(begin(A), end(A));
	int l=INT_MIN, r=INT_MAX, k=1;
	for(auto[y,x]:A) {
		l=max(l, x-e), r=min(r, x+e);
		if(l>r) l=x-e, r=x+e, k++;
	}
	cout<<k;
}