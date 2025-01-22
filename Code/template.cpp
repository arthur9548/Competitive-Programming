#include<bits/stdc++.h>
using namespace std;

//useful defines
//#define INTERACTIVE
//#define PRAGMAS
//#define WINDOWS

#ifdef PRAGMAS //pragmas
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif

#ifndef WINDOWS //ordered_set
#include<bits/extc++.h>
using namespace __gnu_pbds;
template<class T, class B = null_type> using ordered_set = tree<T, B, less<T>, rb_tree_tag,  tree_order_statistics_node_update>;
template<class T> struct ordered_multiset{
	ordered_set<pair<T, int>> o; int c;
	ordered_multiset():c(0){}
	unsigned order_of_key(T x){return o.order_of_key({x, -1});}
	const T* find_by_order(int p){return &(*o.find_by_order(p)).first;}
	void insert(T x){o.insert({x, c++});}
	void erase(T x){o.erase(o.lower_bound({x, 0}));}
	unsigned size(){return o.size();}
	const T* lower_bound(T x){return &(*o.lower_bound({x, 0})).first;}
	const T* upper_bound(T x){return &(*o.upper_bound({x, c})).first;}
};
#endif

//basic types:
//#define int long long
#define long long long
#define float long double

//methods:
#define pb push_back
#define eb emplace_back
#define ppb pop_back
#define fst first
#define snd second
#define unroll(p) p.first, p.second
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define chf(a, f, b) a = f((a), (b))

//loops:
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define repinv(i, a, b) for(int i = (a); i >= (b); i--)
#define for_each(x, c) for(auto x : c)

//debug:
#ifdef LOCAL
#define debug(var) cout << #var << ": " << (var) << endl
#define debug_mul(stuff...) debug((vector{stuff}))
#else
#define debug(var)
#define debug_mul(stuf...)
#endif

//io:
#define esp " "
#ifndef INTERACTIVE
#define endl '\n'
#endif
template<class T> T read(){T a; cin >> a; return a;}
template<class T> auto& operator<<(ostream& o, vector<vector<T>> v){
rep(i,0,sz(v)){o << v[i]; if (i<sz(v)-1)o << endl;} return o;}
template<class T> auto& operator<<(ostream& o, vector<T> v){
rep(i,0,sz(v)){o << v[i]; if (i<sz(v)-1)o << esp;} return o;}
template<class A, class B> auto& operator<<(ostream& o, pair<A, B> p){o << p.fst << esp << p.snd; return o;}
template<class T> auto& operator>>(istream& i, vector<T>& v){for_each(&x, v)i >> x; return i;}
template<class A, class B> auto& operator>>(istream& i, pair<A, B>& p){ i>> p.fst >> p.snd; return i;}

//using and typedef:
typedef vector<int> vi;
typedef pair<int, int> pii;

//constants:
using INF_TYPE = int;
constexpr INF_TYPE oo = (((unsigned INF_TYPE)-1)>>2);
constexpr int MOD = 998244353;

/*Draft
*/
/*Ideas
*/

void solvetestcase(){
}

signed main(){
	#ifndef INTERACTIVE
	ios_base::sync_with_stdio(0); cin.tie(0);
	#endif
	int t=1;
	cin>>t;
	while(t--)solvetestcase();
}

/*
FOCUS! Thinking is harder than coding
- read statement
- read and understand testcases
- understand problem and naive solution
- focus on solving the problem: it has a solution and you can solve it
- idea/form of solution is important
- test edge cases before submitting
- come up with cases to debug, like n = 10
*/
