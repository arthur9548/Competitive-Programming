//Segment Tree: 0-indexed iteractive update, custom query (O(log))
//easily customized: choose type of node, merge operation and query aspect
//iteractive is about 1.2 faster than recursive segtree

#define parent(pos) ((pos/2)-1+(pos&1))
template<typename type>
struct SegTree{
	using assoc_op = function<type(type, type)>;
	int n; //seg n, not original n
	vector<type> seg;
	assoc_op merge;
	type neutral;
	
	SegTree(vector<type> v, assoc_op op, type iden){
		int s = sz(v);
		if (__builtin_popcount(s)==1) n = s;
		else n = 1<<(1+__builtin_clz(1)-__builtin_clz(s));
		neutral = iden; merge = op;
		seg.assign(2*n-1, neutral);
		rep(i, 0, s)update(i, v[i]);
	}
	
	void update(int pos, type value){
		pos += n-1; seg[pos] = value;
		while(pos){
			pos = parent(pos);
			seg[pos] = merge(seg[2*pos+1], seg[2*pos+2]);
		}
	}
	
	type query(int l, int r){
		//return iquery(l, r); //if iteractive doesnt need interface
		return rquery(l, r+1, 0, 0, n);
	}
	
	type iquery(int l, int r){//[l,r]
		l+=n-1; r+=n-1; type res = neutral;
		while(l<=r){
			if (l%2==0)res = merge(seg[l++], res);
			if (r%2==1)res = merge(res, seg[r--]);
			l = parent(l); r = parent(r);
		}
		return res;
	}
	
	
	type rquery(int l, int r, int pos, int lx, int rx){//[l,r[
		if (r <= lx or l >= rx)return neutral;
		if (l <= lx and r >= rx)return seg[pos];
		int mid = lx+(rx-lx)/2;
		return merge(rquery(l,r,2*pos+1,lx,mid), rquery(l,r,2*pos+2,mid,rx));
	}
};
