#include <bits/stdc++.h>
#define rep(i,x,n) for(int i=x; i<n; i++)
using namespace std;
constexpr int MAX=1e6, MOD=1e9+7;

int add(int x, int y) { return x+y-(x+y>=MOD)*MOD; }
int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	int N, id=0;
	cin>>N;
	vector<string> A(N);
	rep(i, 0, N) cin>>A[i];

	array<array<int, 26>, MAX> T;
	array<vector<int>, MAX> P;
	array<int, MAX> F;
	for(string& s:A) {
		int p=0;
		for(char c:s) p=T[p][c-'A']=T[p][c-'A']?:++id;
		P[p].push_back(s.size());
	}
	queue<int> q;
	rep(c, 0, 26) if(T[0][c]) q.push(T[0][c]);
	while(!q.empty()) {
		int x=q.front(); q.pop();
		for(int c=0; c<26; c++) if(T[x][c]) {
			int p=F[x], y=T[x][c];
			while(p && !T[p][c]) p=F[p];
			F[y]=p=T[p][c];
			P[y].insert(end(P[y]), begin(P[p]), end(P[p]));
			q.push(y);
		}
	}

	int p=0;
	string s;
	cin>>s;
	N=s.size();
	vector<int> D(N);
	rep(i, 0, N) {
		char c=s[i]-'A';
		while(p && !T[p][c]) p=F[p];
		p=T[p][c];
		for(int j:P[p]) D[i]=add(D[i], i-j<0 ?: D[i-j]);
	}
	cout<<D.back();
}