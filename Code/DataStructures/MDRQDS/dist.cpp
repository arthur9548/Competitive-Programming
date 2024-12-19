/**
	* Title: Multidimensional Disjoint Sparse Table (DiST)
	* Description: static range queries
	* Complexity:
		- Query: O(op * 2^D)
		- Build: O(op * (2 * n * log(n))^D)
		- Memory: O((2 * n * log(n))^D * T)
	* Restrictions:
		- S must be a commutative monoid (T, id, op)
	* Observations:
		- Worse constant than normal sparse table (n = 1<<(ceil(log2(n)))
		- Don't forget to "init" the DiST before querying!
	* Tested at:
		- Static Range Sum Queries (CSES)
		- Animals and Puzzle (CF)
*/

#define MAs template<class...As>
template<int D, class S>
struct MDiST{ using T = S::T;
	int n, h; vector<vector<MDiST<D-1, S>>> t;
	int lg(signed x){return __builtin_clz(1)-__builtin_clz(x);}
	MAs MDiST(int s, As... ds):n(1<<(lg(s)+(s!=(1<<lg(s))))), 
	h(lg(n)), t(h+(n==1), vector(n, MDiST<D-1, S>(ds...))){}
	MAs void set(T x, int p, As... ps){t[0][p].set(x, ps...);}
	void join(MDiST& a, MDiST& b){
		rep(d,0,h)rep(i,0,n)t[d][i].join(a.t[d][i], b.t[d][i]);
	}
	void init(){
		rep(i,0,n)t[0][i].init();
		for(int d = 1, s = 2; d < h; d++, s *= 2)
		for(int m = s; m < n; m += 2*s){
			t[d][m] = t[0][m]; t[d][m-1] = t[0][m-1];
			rep(i, m+1, m+s)t[d][i].join(t[d][i-1], t[0][i]);
			repinv(i, m-2, m-s)t[d][i].join(t[0][i], t[d][i+1]);
		}
	}
	MAs T query(int l, int r, As... ps){
		if (l==r)return t[0][l].query(ps...);
		int k = lg(l^r);
		return S::op(t[k][l].query(ps...), t[k][r].query(ps...));
	}
};

template<class S>
struct MDiST<0, S>{ using T = typename S::T;
	T val = S::id;
	void set(T x){val = x;}
	void join(MDiST& a, MDiST& b){val = S::op(a.val, b.val);}
	void init(){}
	T query(){return val;}
};

struct MaximumMonoid{
	using T = int;
	static constexpr T id = 0;
	static T op(T a, T b){return max(a, b);}
};
