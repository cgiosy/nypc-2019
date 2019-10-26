#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main() {
	ios_base::sync_with_stdio(false);cin.tie(nullptr);
	ll a, b, x=0;
	cin>>a>>b; --a;
	for(ll i=1, j; i<=b; i+=j) x+=(b/i)*(j=b/i?(b%i)/(b/i)+1:1);
	for(ll i=1, j; i<=a; i+=j) x-=(a/i)*(j=a/i?(a%i)/(a/i)+1:1);
	cout<<x;
}