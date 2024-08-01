//Title: minimal size iteractive segtree
//Same functionality of Multidimensional seg, but 1-D and shorter

template<class S>
struct SegTree{ using T = S::T;
	int n; vector<T> seg;
	ISegTree(int s):n(s),seg(2*n,S::id){}
	void update(T v, int p){
		for(seg[p+=n]=v;p>>=1;)seg[p]=S::op(seg[p<<1],seg[p<<1|1]);
	}
	T query(int l, int r){
		T vl=S::id,vr=S::id;
		for(l+=n,r+=n+1;l<r;l>>=1,r>>=1){
			if (l&1)vl = S::op(vl, seg[l++]);
			if (r&1)vr = S::op(seg[--r], vr);
		} return S::op(vl, vr);
	}
};
struct Spec{using T = pii; static constexpr T id = {0,0}; 
	static T op(T a, T b){return {a.first+b.first,a.second+b.second};}
};