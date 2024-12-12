/**
	* Title: Sparse Table
	* Description: static idempotent range queries
	* Complexity:
		- Query: O(op)
		- Build: O(n * log(n) * op)
		- Memory: O(n * log(n) * T)
	* Restrictions:
		- S must be an idempotent monoid (T, id, op)
	* Tested at:
		- Static Range Minimum Queries (CSES)
*/
		
template<class S>
struct SpTable{using T = typename S::T;
	int n; vector<vector<T>> tab;
	int lg(signed x){return __builtin_clz(1)-__builtin_clz(x);}
	SpTable(vector<T> v):n(sz(v)),tab(1+lg(n),vector<T>(n,S::id)){
		rep(i,0,n)tab[0][i] = v[i];
		rep(i,0,lg(n))rep(j,0,n-(1<<i))
			tab[i+1][j] = S::op(tab[i][j], tab[i][j+(1<<i)]);
	}
	T query(int l, int r){
		int k = lg(++r-l);
		return S::op(tab[k][l], tab[k][r-(1<<k)]);
	}
};

struct MinimumMonoid{
	using T = int;
	static constexpr T id = oo;
	static T op(T a, T b){return min(a,b);}
};