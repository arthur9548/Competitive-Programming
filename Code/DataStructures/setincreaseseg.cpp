//seg with set and increase operations
//about 1.25 slower compared to normal lazy seg

#define type int
#define neutral 0ll

type merge(type a, type b){
	return a+b;
}

int parent(int pos){
	return pos/2 - (1-pos%2);
}

struct LazySegTree{
	int n;
	vector<type> seg;
	vector<int> lazy;
	vector<bool> op;
	
	LazySegTree(vector<type> v){
		int s = sz(v);
		if (__builtin_popcount(s)==1)n = s;
		else n = 1<<(1+__builtin_clz(1)-__builtin_clz(s));
		seg.assign(2*n-1, neutral);
		lazy.assign(2*n-1, 0ll);
		op.assign(2*n-1, true);
		rep(i, 0, s)update(i, i, v[i]);
	}
	
	void prop(int pos, int lx, int rx){
		if (op[pos]){
			if (lazy[pos]==0ll)return;
			seg[pos] += (rx-lx)*lazy[pos];
			if ((rx-lx)>1){
				lazy[2*pos+1]+=lazy[pos];
				lazy[2*pos+2]+=lazy[pos];
			}
			lazy[pos] = 0ll;
		}
		else{
			seg[pos] = (rx-lx)*lazy[pos];
			if ((rx-lx)>1){
				lazy[2*pos+1]=lazy[2*pos+2]=lazy[pos];
				op[2*pos+1]=op[2*pos+2]=false;
			}
			lazy[pos]=0ll; op[pos] = true;
		}
	}
	
	void updt(int l, int r, int value, int pos, int lx, int rx, bool inc){
		prop(pos, lx, rx);
		if (r <= lx or l >= rx)return;
		if (l <= lx and r >= rx){
			lazy[pos] = value; op[pos] = inc; prop(pos, lx, rx); return;
		}
		int mid = lx+(rx-lx)/2;
		updt(l,r,value,2*pos+1,lx,mid,inc); updt(l,r,value,2*pos+2,mid,rx,inc);
		seg[pos] = merge(seg[2*pos+1], seg[2*pos+2]);
	}
	
	type qry(int l, int r, int pos, int lx, int rx){
		prop(pos,lx,rx);
		if (r <= lx or l >= rx)return neutral;
		if (l <= lx and r >= rx)return seg[pos];
		int mid = lx+(rx-lx)/2;
		return merge(qry(l,r,2*pos+1,lx,mid), qry(l,r,2*pos+2,mid,rx));
	}
	
	void update(int l, int r, int value, bool inc=false){
		updt(l,r+1,value,0,0,n,inc);
	}
	
	type query(int l, int r){
		return qry(l,r+1,0,0,n);
	}
};