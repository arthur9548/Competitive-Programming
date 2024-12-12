//Title: multidimensional Segment Tree (SegTree)
//Description: range query and point update
//Complexity: O(logn ^ D) query and update and O(n^D) memory
//Restrictions: elements must be of a Monoid (op, id)
//Observations:
//--- 1-indexed and half open in internal implementation only
//--- Constant factor of 2^D in memory and operations and D^2 in update
//Tested at: CSES-Dynamic Range Minimum Queries and CF-Valiant's New Map

#define MAs template<class... As> //multiple arguments
template<int D, class S>
struct SegTree{ using T = typename S::T;
	int n;
	vector<SegTree<D-1, S>> seg;
	MAs SegTree(int s, As... ds):n(s),seg(2*n, SegTree<D-1, S>(ds...)){}
	MAs T get(int p, As... ps){return seg[p+n].get(ps...);}
	MAs void update(T x, int p, As... ps){
		p+=n; seg[p].update(x, ps...);
		for(p>>=1;p>=1;p>>=1)
		seg[p].update(S::op(seg[2*p].get(ps...),seg[2*p+1].get(ps...)), ps...);
	}
	MAs T query(int l, int r, As... ps){
		T lv=S::id,rv=S::id;
		for(l+=n,r+=n+1;l<r;l>>=1,r>>=1){
			if (l&1)lv = S::op(lv,seg[l++].query(ps...));
			if (r&1)rv = S::op(seg[--r].query(ps...),rv);
		}
		return S::op(lv,rv);
	}
};
 
template<class S>
struct SegTree<0, S>{ using T = typename S::T;
	T val=S::id;
	T get(){return val;}
	void update(T x){val=x;}
	T query(){return val;}
};
 
struct M{
	using T = int;
	static constexpr T id = oo;
	static T op(T a, T b){return min(a,b);}
};

void example(){
	SegTree<3, M> seg(3, 4, 5); //3x4x5 seg with oo in all points
	seg.update(1, 0, 1, 2); //set point (0,1,2) to 1
	cout << seg.query(0, 2, 0, 3, 0, 4).v << endl; //query of whole seg
}
