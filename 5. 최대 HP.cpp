#include <bits/stdc++.h>
#define rep(i,x,n) for(int i=x; i<n; i++)
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	int H, T, s=0;
	cin>>H>>T;
	rep(i, 0, T) {
		int t, x;
		cin>>t>>x;
		if(t==1) H-=x;
		else H+=x;
		s=max(s, H);
	}
	cout<<s;
}