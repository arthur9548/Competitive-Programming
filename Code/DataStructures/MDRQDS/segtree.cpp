/**
	* Title: Multidimensional Segment Tree
	* Description: range query and point update
	* Complexity:
		- Query: O(op * (2 * log(n))^D)
		- Update (set): O(op * (log(n)^D)) 
		- Build: O((2 * n)^D)
		- Memory: O((2 * n)^D * T)
	* Restrictions:
		- S must be a monoid (T, id, op)
	* Observations:
		- 1-indexed and half-open only in internal implementation
	* Tested at:
		- Dynamic Range Minimum Queries (CSES)
		- Valiant's New Map (CF)
*/

#define MAs template<class... As> //multiple arguments
template<int D, class S>
struct MSegTree{ using T = typename S::T;
	int n; vector<MSegTree<D-1, S>> seg;
	MAs MSegTree(int s, As... ds):n(s),seg(2*n, MSegTree<D-1, S>(ds...)){}
	MAs T get(int p, As... ps){return seg[p+n].get(ps...);}
	MAs void update(T x, int p, As... ps){
		seg[p+=n].update(x, ps...); for(p/=2; p; p/=2)
		seg[p].update(S::op(seg[2*p].get(ps...),seg[2*p+1].get(ps...)), ps...);
	}
	MAs T query(int l, int r, As... ps){
		T lv=S::id,rv=S::id;
		for(l+=n, r+=n+1; l < r; l/=2, r/=2){
			if (l&1)lv = S::op(lv, seg[l++].query(ps...));
			if (r&1)rv = S::op(seg[--r].query(ps...), rv);
		} return S::op(lv,rv);
	}
};
 
template<class S>
struct MSegTree<0, S>{ using T = typename S::T; //base case
	T val=S::id;
	T get(){return val;}
	void update(T x){val=x;}
	T query(){return val;}
};
 
struct MinimumMonoid{
	using T = int;
	static constexpr T id = oo;
	static T op(T a, T b){return min(a,b);}
};