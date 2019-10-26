#include <bits/stdc++.h>
#define rep(i,x,n) for(int i=x; i<n; i++)
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	string a, s;
	cin>>a;
	int M=a.size();
	rep(i, 0, M) s+='#', s+=a[i];
	rep(i, 0, M) s+='#', s+=a[i];
	s+='#';

	int N=s.size();
	vector<int> A(N);
	int r=-1, k=-1;
	for(int i=0; i<N; i++) {
		if(i<=r) A[i]=min(r-i, A[2*k-i]);
		while(0<=i-A[i]-1 && i+A[i]+1<N && s[i-A[i]-1]==s[i+A[i]+1]) A[i]++;
		if(r<i+A[i]) r=i+A[i], k=i;
	}
	int x=0;
	rep(i, M, M*3)
		x+=M%2 ? s[i]!='#' && A[i]+1>=M: s[i]=='#' && A[i]>=M;
	cout<<x;
}
