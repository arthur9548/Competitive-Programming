//persistent dynamic segtree
//time complexity is equal, but memory suffer O(qlogn) increase

struct node{
	int value, lx, rx;
	node *lc, *rc;
	node(int val, int l, int r, node * ln, node * rn){
		value = val; lx = l; rx = r; lc = ln; rc = rn;
	}
};

struct PerSegTree{
	int n;
	vector<node*> roots;
	
	PerSegTree(vi v){
		int s = sz(v);
		if (__builtin_popcountll(s)==1) n = s;
		else n = 1ll<<(1+__builtin_clzll(1ll)-__builtin_clzll(s));
		node * root = build(0, n);
		rep(i, 0, s)root = updt(i, v[i], root);
		roots.pb(root);
	}
	
	node* build(int lx, int rx){
		if ((rx-lx)==1){
			return new node(0, lx, rx, 0, 0);
		}
		int mid = lx+(rx-lx)/2;
		node* l = build(lx, mid);
		node* r = build(mid, rx);
		return new node(0, lx, rx, l, r);
	}
	
	node* updt(int pos, int val, node* no){
		int lx = no->lx, rx = no->rx;
		if (pos < lx or pos >= rx)return no;
		if ((rx-lx)==1){
			return new node(val, lx, rx, no->lc, no->rc);
		}
		node* l = updt(pos, val, no->lc);
		node* r = updt(pos, val, no->rc);
		return new node(l->value + r->value, lx, rx, l, r);
	}
	
	void update(int idx, int pos, int value){
		roots[idx] = updt(pos, value, roots[idx]);
	}
	
	int qry(int l, int r, node* no){
		int lx = no->lx, rx = no->rx;
		if (l >= rx or r <= lx)return 0;
		if (l <= lx and r >= rx)return no->value;
		return qry(l, r, no->lc) + qry(l, r, no->rc);
	}
	
	int query(int idx, int l, int r){
		return qry(l, r, roots[idx]);
	}
	
	void copy(int idx){
		node* proot = roots[idx];
		node* nroot = new node(proot->value, 0, n, proot->lc, proot->rc);
		roots.pb(nroot);
	}
};