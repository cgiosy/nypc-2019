#include <bits/stdc++.h>
#define rep(i,x,n) for(int i=x; i<n; i++)
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	int N, y=INT_MAX;
	cin>>N;
	vector<int> A(N);
	rep(i, 0, N) cin>>A[i];
	rep(i, 0, N) {
		int x;
		cin>>x;
		y=min(y, x ? A[i]/x : INT_MAX);
	}
	cout<<y;
}