//Title: multidimensional Segment Tree (SegTree)
//Description: range query and point update
//Complexity: O(logn ^ D) query and update and O(n^D) memory
//Restrictions: elements must be of a Monoid (*, id)
//Observations:
//--- 1-indexed and half open in internal implementation only
//--- Constant factor of D^2 (small dimensions are faster)
//Tested at: CSES-Dynamic Range Sum Queries and CSES-Forest Queries II

template<int D, class T>
struct SegTree{
	int n;
	vector<SegTree<D-1, T>> seg;
	template<class... A>
	SegTree(int s, A... ds):n(s),seg(2*n, SegTree<D-1, T>(ds...)){}
	template<class... A>
	T get(int p, A... ps){return seg[p+n].get(ps...);}
	template<class... A>
	void update(T x, int p, A... ps){
		p+=n; seg[p].update(x, ps...);
		for(p>>=1;p>=1;p>>=1)
		seg[p].update(seg[2*p].get(ps...)*seg[2*p+1].get(ps...), ps...);
	}
	template<class... A>
	T query(int l, int r, A... ps){
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
	void update(T x){val=x;}
	T query(){return val;}
	T get(){return val;}
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
