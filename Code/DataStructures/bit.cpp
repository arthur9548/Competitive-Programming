/**
	* Title: Binary Indexed Tree (BIT) / Fenwick Tree
	* Description: fast range query and point update
	* Complexity:
		- Query: O(log(n) * op + inv)
		- Add (update): O(log(n) * op)
		- Build: O(n * op)
		- Memory: O(n * T)
	* Restrictions:
		- S must be an abelian group (T, id, op, inv)
	* Observations:
		- 1-indexed and half-open only in internal implementation
		- Very good constant factor
	* Tested at:
		- Dynamic Range Sum Queries (CSES)
	* Based on: https://codeforces.com/blog/entry/63064
*/
		
template<class S>
struct BIT{using T = typename S::T;
	int n; vector<T> bit;
	int lb(int x){return x&(-x);}
	BIT(vector<T> v):n(sz(v)),bit(1+n,S::id){
		for(int i = 1; i <= n; i++){ 
			chf(bit[i], S::op, v[i-1]);
			if (i+lb(i)<=n)chf(bit[i+lb(i)], S::op, bit[i]);
		}
	}
	void add(T x, int p){for(p++;p<=n;p+=lb(p))chf(bit[p],S::op,x);}
	T query(int l, int r){
		T lv=S::id, rv=S::id; r++;
		for(;r>=1;r-=lb(r))chf(rv,S::op,bit[r]);
		for(;l>=1;l-=lb(l))chf(lv,S::op,bit[l]);
		return S::op(rv,S::inv(lv));
	}
};

struct SumGroup{
	using T = int;
	static constexpr T id = 0;
	static T op(T a, T b){return a+b;}
	static T inv(T a){return -a;}
};
