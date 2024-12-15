/**
	* Title: Multidimensional Prefix/Partial/Cummulative Sum
	* Description: static range queries
	* Complexity:
		- Query: O((op + inv) * 2^D)
		- Build: O(D * op * n^D)
		- Memory: O(n^D * T)
	* Restrictions:
		- S must be an abelian group (T, id, op, inv)
	* Observations:
		- 1-indexed and half-open only in internal implementation
		- Don't forget to "init" the Psum before querying!
	* Tested at:
		- Static Range Sum Queries (CSES)
		- Forest Queries (CSES)
		- Counting Rectangles is Fun (CF)
*/

#define MAs template<class... As> //multiple arguments
template<int D, class S>
struct MPsum{ using T = typename S::T;
	int n; vector<MPsum<D-1, S>> v;
	MAs MPsum(int s, As... ds):n(s+1),v(n,MPsum<D-1, S>(ds...)){}
	MAs void set(T x, int p, As... ps){v[p+1].set(x, ps...);}
	void push(MPsum& p){rep(i, 1, n)v[i].push(p.v[i]);}
	void init(){rep(i, 1, n)v[i].init(),v[i].push(v[i-1]);}
	MAs T query(int l, int r, As... ps){
		return S::op(v[r+1].query(ps...),S::inv(v[l].query(ps...)));
	}
};

template<class S>
struct MPsum<0, S>{ using T = typename S::T; //base case
	T val=S::id;
	void set(T x){val=x;}
	void push(MPsum& a){val=S::op(a.val,val);}
	void init(){}
	T query(){return val;}
};

struct SumGroup{
	using T = int;
	static constexpr T id = 0;
	static T op(T a, T b){return a+b;}
	static T inv(T a){return -a;}
};