/**
	* Title: Recursive Segment Tree
	* Description: custom range query and point update
	* Complexity:
		- Query: O(log(n) * op) ?
		- Update (set): O(log(n) * op)
		- Build: O(n * op)
		- Memory: O(n * (T + int))
	* Restrictions:
		- S must be a monoid (T, id, op)
	* Observations:
		- 1-indexed only in internal implementation
		- Query can be anything
	* Tested at:
		- Hotel Queries (CSES)
*/
		
template<class S>
struct RecSeg{using T = typename S::T;
	int n; vector<T> seg; vi lx, rx;
	int mx(int i){return lx[i]+(rx[i]-lx[i]+1)/2;}
	void calc(int i){seg[i] = S::op(seg[2*i], seg[2*i+1]);}
	RecSeg(vector<T> v):n(sz(v)),seg(2*n),lx(2*n),rx(2*n){
		assert(__builtin_popcount(n)==1);
		rep(i,0,n)seg[i+n] = v[i], lx[i+n] = rx[i+n] = i;
		repinv(i,n-1,1)calc(i), lx[i] = lx[2*i], rx[i] = rx[2*i+1];
	}
	void update(T x, int p){for(seg[p+=n]=x;p/=2;calc(p));}
	int query(T k, int no=1){ //leftmost position with value >= k
		if (seg[no]<k)return -1;
		if (lx[no]==rx[no])return no-n;
		int q = query(k, 2*no);
		if (q != -1)return q;
		return query(k, 2*no+1);
	}
};
struct MaximumMonoid{
	using T = int;
	static constexpr T id = 0;
	static T op(T a, T b){return max(a,b);}
};
