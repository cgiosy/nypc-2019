#include <bits/stdc++.h>
#define invalid {cout<<"invalid";return 0;}
#define rep(i,x,n) for(int i=x; i<n; i++)
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	string s;
	cin>>s;
	if(s.size()<8 || s.size()>15) invalid;
	int f=0;
	for(char c:s)
		if(isalpha(c)) f|=1<<(c>96);
		else if(isdigit(c)) f|=4;
		else f|=8;
	if(f!=15) invalid;
	cout<<"valid";
}