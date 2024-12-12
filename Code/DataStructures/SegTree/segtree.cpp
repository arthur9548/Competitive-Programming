/**
	* Title: Iterative Segment Tree
	* Description: range query and point update
	* Complexity:
		- Query: O(log(n) * op)
		- Update (set): O(log(n) * op)
		- Build: O(n * op)
		- Memory: O(n * T)
	* Restrictions:
		- S must be a monoid (T, id, op)
	* Observations:
		- 1-indexed and half-open only in internal implementation
	* Tested at:
		- Dynamic Range Minimum Queries (CSES)
	* Based on: https://codeforces.com/blog/entry/18051
*/
		
template<class S>
struct SegTree{using T = typename S::T;
	int n; vector<T> seg;
	void calc(int i){seg[i] = S::op(seg[2*i], seg[2*i+1]);}
	SegTree(vector<T> v):n(sz(v)),seg(2*n){
		rep(i,0,n)seg[i+n] = v[i];
		repinv(i,n-1,1)calc(i);
	}
	void update(T x, int p){for(seg[p+=n]=x;p/=2;calc(p));}
	T query(int l, int r){
		T vl=S::id, vr=S::id;
		for(l+=n,r+=n+1;l<r;l/=2,r/=2){
			if (l&1)vl = S::op(vl, seg[l++]);
			if (r&1)vr = S::op(seg[--r], vr);
		} return S::op(vl, vr);
	}
};

struct MinimumMonoid{
	using T = int;
	static constexpr T id = oo;
	static T op(T a, T b){return min(a,b);}
};
