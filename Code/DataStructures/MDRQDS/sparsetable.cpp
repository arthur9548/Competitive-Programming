/**
	* Title: Multidimensional Sparse Table
	* Description: static idempotent range queries
	* Complexity:
		- Query: O(op * 2^D)
		- Build: O(op * (n * log(n))^D)
		- Memory: O((n * log(n))^D)
	* Restrictions:
		- S must be an commutative idempotent monoid (T, id, op)
	* Observations:
		- Don't forget to "init" the Sparse Table before querying!
	* Tested at:
		- Static Range Minimum Queries (CSES)
		- Animals and Puzzles (CF)
*/

#define MAs template<class...As> //multiple arguments
template<int D, class S>
struct MSpTable{ using T = typename S::T;
	using isp = MSpTable<D-1, S>;
	int lg(signed x){return __builtin_clz(1)-__builtin_clz(x);}
	int n; vector<vector<isp>> tab;
	MAs MSpTable(int s, As... ds):n(s),
	tab(1+lg(n),vector<isp>(n,isp(ds...))){}
	MAs void set(T x, int p, As... ps){tab[0][p].set(x, ps...);}
	void join(MSpTable& a, MSpTable& b){
		rep(i, 0, 1+lg(n))rep(j, 0, n)
			tab[i][j].join(a.tab[i][j], b.tab[i][j]);
	}
	void init(){
		rep(i, 0, n)tab[0][i].init();
		rep(i, 0, lg(n))rep(j, 0, n-(1<<i))
			tab[i+1][j].join(tab[i][j], tab[i][j+(1<<i)]);
	}
	MAs T query(int l, int r, As... ps){
		int k = lg(r-l+1); r+=1-(1<<k);
		return S::op(tab[k][l].query(ps...),tab[k][r].query(ps...));
	}
};

template<class S>
struct MSpTable<0, S>{ using T = typename S::T; //base case
	T val=S::id;
	void set(T x){val=x;}
	void join(MSpTable& a, MSpTable& b){val=S::op(a.val,b.val);}
	void init(){}
	T query(){return val;}
};

struct MinimumMonoid{
	using T = int;
	static constexpr T id = oo;
	static T op(T a, T b){return min(a, b);}
};
