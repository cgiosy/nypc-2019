#include <bits/stdc++.h>
#define rep(i,x,n) for(int i=x; i<n; i++)
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--) {
		string s;
		cin>>s;
		bool f=false, g=false;
		for(char c:s) {
			if(f=!(isalpha(c) || isdigit(c) || c=='-' || c=='.' || !g && c=='@')) break;
			if(c=='@') g=true;
		}
		f|=!g || s.front()=='@' || s.back()=='@';
		cout<<(f ? "No" : "Yes")<<'\n';
	}
}