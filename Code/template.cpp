#include<bits/stdc++.h>
using namespace std;
//basic types:
#define int long long
#define float long double
//methods:
#define pb push_back
#define eb emplace_back
#define ppb pop_back
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define chf(a, f, b) a = f(a, b)
//loops:
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define repinv(i, a, b) for(int i = (a); i >= (b); i--)
//input/output:
template<class T> T read(){T a; cin >> a; return a;}
#define esp ' '
#define endl '\n'
#define debug(var) cout << #var << ": " << var << endl
template<class T> ostream& operator<<(ostream& os, vector<T> v){
	if (v.empty()) return os << "";
	rep(i, 0, sz(v)-1)os << v[i] << esp;
	return os << v.back();
}
template<class A, class B> ostream& operator<<(ostream& os, pair<A, B> p){
	os << p.first << esp << p.second; return os;
}
//using and typedef:
typedef vector<int> vi;
typedef pair<int, int> pii;
//constants:
constexpr int oo = (((unsigned int)-1)>>1);

void solvetestcase(){
	int n; cin >> n; cout << n;
}

signed main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t=1;
	//cin>>t;
	rep(i,0,t)solvetestcase();
}