#include <bits/stdc++.h>
#define rep(i,x,n) for(int i=x; i<n; i++)
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	int N, M, p, k=0;
	cin>>N>>M>>p; --p;
	vector<int> A(N);
	while(M--) {
		int x, y;
		cin>>x>>y; --x;
		if(y) {
			if(A[p]) A[p]--;
			else k++;
			A[x]++;
		}
		p=x;
	}
	cout<<k;
}