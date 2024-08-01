//Title: Lazy Iteractive Segment Tree (Lazy Seg)
//Description: range update and query
//Complexity: O(logn) query and update, O(n) memory
//Restrictions:
//--- Seg operation must be monoidal (id, op)
//--- Lazy updates must distribute over operations
//--- Lazy composition must be compositional (obviously)
//Observations: 
//--- 1-indexed and half-open in internal implementation only 
//--- Default initialization is with id value
//Tested at: CSES-Prefix Sum Queries

template<class S>
struct LazySeg{ using T = typename S::T; using L = typename S::L;
	int ilog(signed x){return __builtin_clz(1)-__builtin_clz(x);}
	int n, h; 
	vector<T> seg; 
	vector<L> lz;
	vector<bool> ig;
	LazySeg(int s):n(s),h(1+ilog(n)),seg(2*n,S::id),lz(n),ig(n,1){}
	void fix(int p, int s){
		seg[p] = ig[p]?S::op(seg[p<<1],seg[p<<1|1]):S::ch(seg[p],lz[p],s);
	}
	void apply(L v, int p, int s){
		seg[p] = S::ch(seg[p], v, s);
		if (p < n)lz[p] = ig[p]?v:S::cmp(lz[p],v), ig[p]=0;
	}
	void push(int p){
		for(int k=h,s=1<<h;k;k--){
			s>>=1; int i = (p+n)>>k; if (ig[i])continue;
			apply(lz[i],i<<1,s); apply(lz[i],i<<1|1,s); ig[i]=1;
		}
	}	
	void update(L v, int l, int r){
		push(l); push(r);
		int cl=0,cr=0,s=1;
		for(l+=n,r+=n+1;l<r;l>>=1,r>>=1,s<<=1){
			if (cl)fix(l-1,s);
			if (cr)fix(r,s);
			if (l&1)apply(v,l++,s),cl=1;
			if (r&1)apply(v,--r,s),cr=1;
		}
		for(l--;r;l>>=1,r>>=1,s<<=1){
			if (cl)fix(l,s);
			if (cr and ((not cl) or (l != r)))fix(r, s);
		}
	}
	T query(int l, int r){
		push(l); push(r);
		T vl=S::id,vr=S::id;
		for(l+=n,r+=n+1;l<r;l>>=1,r>>=1){
			if (l&1)vl = S::op(vl, seg[l++]);
			if (r&1)vr = S::op(seg[--r], vr);
		}
		return S::op(vl, vr);
	}
};

struct Spec{ //max with sum update
	using T = int;
	using L = int;
	static constexpr T id = -oo; //everyone will start with this value
	static T op(T a, T b){return max(a, b);}
	static T ch(T past, L upd, int s){return past+upd;} //ch(op(a,b),x)=op(ch(a,x),ch(b,x))
	static L cmp(L cur, L upd){return cur+upd;} //ch(a,cmp(x,y))=ch(ch(a,x),y)
};

void example(){
	LazySeg seg(3); //seg = {-oo, -oo, -oo}
	seg.update(oo+1, 0, 2); //seg = {1, 1, 1}
	seg.update(1, 2, 2); //seg = {1, 1, 2}
	cout << seg.query(0, 2) << endl; // = 2