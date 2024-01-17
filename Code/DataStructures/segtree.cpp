#define type int
#define neutral 0ll
//0-indexed iteractive update, custom query segtree
//easily customized: choose type of node, merge operation and query aspect
//iteractive is about 1.25 faster than recursive segtree

type merge(type a, type b){
	return a+b;
}

int parent(int pos){
	return pos/2 - (1-pos%2);
}

struct SegTree{
	int n;
	vector<type> seg;
	SegTree(vector<type> v){
		int s = sz(v);
		if (__builtin_popcount(s)==1)n = s;
		else{
			n = 1<<(1+__builtin_clz(1)-__builtin_clz(s));
		}
		seg.assign(2*n-1, neutral);
		rep(i, 0, s)update(i, v[i]);
	}
	
	void update(int pos, type value){
		pos += n-1;
		seg[pos] = value;
		while(pos){
			pos = parent(pos);
			seg[pos] = merge(seg[2*pos+1], seg[2*pos+2]);
		}
	}
	
	//[l,r]
	type iquery(int l, int r){
		l+=n-1; r+=n-1;
		type res = neutral;
		while(l<=r){
			if (l%2==0){ 
			//l is right children, left brother should not be included in res
				res = merge(res, seg[l]); l++;
			}
			if (r%2==1){
			//r is left children, right brother should not be included in res
				res = merge(res, seg[r]); r--;
			}
			l = parent(l); r = parent(r);
		}
		return res;
	}
	
	//[l,r[
	type rquery(int l, int r, int pos=0, int lx=0, int rx=n){
		if (r <= lx or l >= rx)return neutral;
		if (l <= lx and r >= rx)return seg[pos];
		int mid = lx+(rx-lx)/2;
		return merge(rquery(l,r,2*pos+1,lx,mid), rquery(l,r,2*pos+2,mid,rx));
};