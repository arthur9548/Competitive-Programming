//Title: Binary Lifting
//Description: static path queries in functional graph
//Complexity: O(n logq) build, O(logq) query
//Restrictions: works under Monoid (op, id)
//Observations:
//--- Calculate log(max query) beforehand, important for constant factor
//Tested at: CSES-Planet Queries I and CSES-New Roads Queries

template<class S>
struct BinLift{ using T = typename S::T;
	int n, q; vector<vector<pair<int, T>>> up;
	BinLift(vi& fn, vector<T>& val, int logmaxq)
		:n(sz(fn)),q(logmaxq),up(q+1,vector<pair<int, T>>(n)){
		rep(i, 0, n)up[0][i] = {i, S::id};
		rep(i, 0, n)up[1][i] = {fn[i], val[i]};
		rep(i, 1, q)rep(j, 0, n){
			auto& [prev, pval] = up[i][j]; 
			auto& [nxt, nval] = up[i][prev];
			up[i+1][j] = {nxt, S::op(pval, nval)};
		}
	}
	pair<int, T> query(int v, int qup){
		int dest = v; T res = S::id;
		rep(i, 0, q){
			if ((1ll<<i)&qup){
				auto& [cur, val] = up[i+1][dest];
				dest = cur; res = S::op(res, val);
			}
		}
		return {dest, res};
	}
};

struct VoidSpec{
	using T = int;
	constexpr static T id = 0;
	static T op(T a, T b){return a;}
};