/**
	* Title: Lazy Update Segment Tree
	* Description: range query and range update
	* Complexity:
		- Query: O(log(n) * (op + ch + cmp))
		- Update: O(log(n) * (op + ch + cmp))
		- Build: O(n * op)
		- Memory: O(n * (T + bool + signed))
	* Restrictions:
		- S must be a monoid (T, id, op)
		- S must also have lazy info (L, ch, cmp)
		- Lazy updates must distribute over operation:
			ch(op(a, b), x) = op(ch(a, x), ch(b, x))
		- Lazy composition must follow:
			ch(a, cmp(x, y)) = ch(ch(a, x), y)
	* Observations:
		- 1-indexed and half-open only in internal implementation
		- Runtime can be increased removing lx and rx when possible
	* Tested at:
		- Range Updates and Sums (CSES)
		- Polynomial Queries (CSES)
	* Based on: https://codeforces.com/blog/entry/18051
*/
		
#define V vector
#define UT(s, x) using x = typename s::x
template<class S> 
struct LazySeg{ UT(S, T); UT(S, L);
	signed n, h; V<T> seg; V<L> lz; V<bool> ig; V<signed> lx,rx;
	LazySeg(V<T> v):n(sz(v)),seg(2*n,S::id),lz(n),ig(n,1),lx(2*n),rx(2*n){
		h = 1+__builtin_clz(1)-__builtin_clz(n);
		rep(i,0,n)seg[i+n] = v[i], lx[i+n] = rx[i+n] = i;
		repinv(i,n-1,1)calc(i), lx[i] = lx[2*i], rx[i] = rx[2*i+1];
	}
	void calc(int i){seg[i] = S::op(seg[2*i], seg[2*i+1]);}
	void ch(L v, int i){seg[i] = S::ch(seg[i], v, lx[i], rx[i]);}
	void fix(int p){ig[p] ? calc(p) : ch(lz[p],p);}
	void apply(L v, int p){ 
		ch(v, p); if (p < n)
		lz[p] = ig[p] ? v : S::cmp(lz[p],v), ig[p]=0;
	}
	void push(int p){
		for(int k = h; k; k--){
			int i = (p+n)>>k; if (ig[i])continue;
			apply(lz[i], 2*i); apply(lz[i], 2*i+1); ig[i]=1;
		}
	}	
	void update(L v, int l, int r){
		push(l); push(r);
		int cl=0,cr=0;
		for(l+=n, r+=n+1; l < r; l/=2, r/=2){
			if (cl)fix(l-1);
			if (cr)fix(r);
			if (l&1)apply(v, l++),cl=1;
			if (r&1)apply(v, --r),cr=1;
		}
		for(l--; r; l/=2, r/=2){
			if (cl)fix(l);
			if (cr and ((not cl) or (l != r)))fix(r);
		}
	}
	T query(int l, int r){
		push(l); push(r);
		T vl=S::id,vr=S::id;
		for(l+=n, r+=n+1; l < r; l/=2, r/=2){
			if (l&1)vl = S::op(vl, seg[l++]);
			if (r&1)vr = S::op(seg[--r], vr);
		}
		return S::op(vl, vr);
	}
};

struct Sum_of_AP{ //E = sum of
	using T = pii; //{E cof0, E cof1}
	using L = pii; //{cof0, cof1}
	static constexpr T id = {0,0};
	static T op(T a, T b){return {a.first+b.first, a.second+b.second};}
	static T ch(T past, L upd, int lx, int rx){
		int s = rx-lx+1;
		past.first += s*upd.first;
		past.second += ((lx+rx)*(s)/2)*upd.second;
		return past;
	}
	static L cmp(L cur, L upd){
		auto [b, a] = cur;
		auto [d, c] = upd;
		return {d+b, c+a};
	}
	int ans(T x){return x.first+x.second;}
};