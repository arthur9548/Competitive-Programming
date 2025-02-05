/**
	* Title: Sparse/Implicit/Dynamic Segment Tree
	* Description: sparse range query and point update
	* Complexity:
		- Query: O(log(n) * op)
		- Update: O(log(n) * op)
		- Build: O(1)
		- Memory: O(qnt_updt * log(n) * (2 * int + T))
	* Restrictions:
		- S must be a monoid (T, id, op)
		- I must be an integer type
	* Observations:
		- Node 0 is a "blank" node, the default child of any node
		- MXN should be qnt_updt * log(n)
	* Tested at:
		- Salary Queries (CSES)
*/

#define GET(a, x) a = x.a //avoid typos
#define midpoint(l, r) (l+(r-l)/2) //overriding stl in c++20
template<class I, class S> //index type and algebraic structure
struct SparseSeg{ 
	using P = int; //pointer type
	using T = typename S::T; //value type
	struct Node{P lc, rc; T val;};
	I n; vector<Node> v;
	P new_node(){return v.eb(0,0,S::id), sz(v)-1;}
	SparseSeg(I s): n(s){
		v.reserve(MXN); //faster node creation
		new_node(); //blank node
		new_node(); //root node
	}
	void update(T x, I p){return update(x, p, 1, 0, n-1);}
	void update(T x, I p, P i, I lx, I rx){
		if (lx==rx){v[i].val = x; return;}
		I mx = midpoint(lx, rx); 
		P GET(lc, v[i]), GET(rc, v[i]);
		if (p > mx){
			if (not rc)GET(rc, v[i]) = new_node();
			update(x, p, rc, mx+1, rx);
		}
		else{
			if (not lc)GET(lc, v[i]) = new_node();
			update(x, p, lc, lx, mx);
		}
		v[i].val = S::op(v[lc].val, v[rc].val); //blank's value is id
	} 
	T query(I l, I r){return query(l, r, 1, 0, n-1);}
	T query(I l, I r, P i, I lx, I rx){
		if (l <= lx and rx <= r)return v[i].val;
		if (lx > r or rx < l)return S::id;
		I mx = midpoint(lx, rx);
		return S::op(query(l, r, v[i].lc, lx, mx), query(l, r, v[i].rc, mx+1, rx));
		//for nonexisting nodes, it will (correctly) return id through blank's val
	} 
};

struct SumSpec{
	using T = int;
	static constexpr T id = 0;
	static T op(T a, T b){return a+b;}
};