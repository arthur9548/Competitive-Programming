//Title: multidimensional Segment Tree (SegTree)
//Description: range query and point update
//Complexity: O(logn ^ D) query and update and O(n^D) memory
//Restrictions: elements must be of a Monoid (*, id)
//Observations:
//--- 1-indexed and half open in internal implementation only
//--- Constant factor of 2^D in memory and operations and D^2 in update
//Tested at: CSES-Dynamic Range Minimum Queries and CF-Valiant's New Map

#define MAs template<class... As> //multiple arguments
template<int D, class T>
struct SegTree{
	int n;
	vector<SegTree<D-1, T>> seg;
	MAs SegTree(int s, As... ds):n(s),seg(2*n, SegTree<D-1, T>(ds...)){}
	MAs T get(int p, As... ps){return seg[p+n].get(ps...);}
	MAs void update(T x, int p, As... ps){
		p+=n; seg[p].update(x, ps...);
		for(p>>=1;p>=1;p>>=1)
		seg[p].update(seg[2*p].get(ps...)*seg[2*p+1].get(ps...), ps...);
	}
	MAs T query(int l, int r, As... ps){
		T lv={T::id},rv={T::id};
		for(l+=n,r+=n+1;l<r;l>>=1,r>>=1){
			if (l&1)lv = lv*seg[l++].query(ps...);
			if (r&1)rv = seg[--r].query(ps...)*rv;
		}
		return lv*rv;
	}
};
 
template<class T>
struct SegTree<0, T>{
	T val={T::id};
	T get(){return val;}
	void update(T x){val=x;}
	T query(){return val;}
};
 
struct M{
	int v; static const int id = 0;
	M operator*(const M& o){return {v+o.v};}
};

void example(){
	SegTree<3, M> seg(3, 4, 5); //3x4x5 seg
	seg.update(M{1}, 0, 1, 2); //added 1 to point (0,1,2)
	cout << seg.query(0, 2, 0, 3, 0, 4).v << endl; //query of whole seg
}
