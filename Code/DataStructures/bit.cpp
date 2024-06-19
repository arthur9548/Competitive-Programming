//Title: multidimensional Binary Indexed Tree (BIT)
//Description: fast range query and point update
//Complexity: O(logn ^ D) query and update, O(n^D) memory
//Restrictions: elements must be of a abelian group (op, inv, id)
//Observations: 
//--- 1-indexed only in implementation, interface is 0-indexed
//--- Very good constant factor
//Tested at: CSES-Dynamic Range Sum Queries and Timus-UFOs

#define MAs template<class... As> //multiple arguments
template<int D, class S> 
struct BIT{ using T = typename S::T;
	int n;
	vector<BIT<D-1, S>> bit;
	MAs BIT(int s, As... ds):n(s),bit(n+1, BIT<D-1, S>(ds...)){}
	inline int lastbit(int x){return x&(-x);}
	MAs void add(T x, int p, As... ps){
		for(p++;p<=n;p+=lastbit(p))bit[p].add(x, ps...);
	}
	MAs T query(int l, int r, As... ps){
		T lv=S::id,rv=S::id; r++;
		for(;r>=1;r-=lastbit(r))rv=S::op(rv,bit[r].query(ps...));
		for(;l>=1;l-=lastbit(l))lv=S::op(lv,bit[l].query(ps...));
		return S::op(rv,S::inv(lv));
	}
};

template<class S>
struct BIT<0, S>{ using T = typename S::T;
	T val=S::id;
	void add(T x){val=S::op(val,x);}
	T query(){return val;}
};

struct AG{ //abelian group analogous to int addition
	using T = int;
	static constexpr T id = 0;
	static T op(T a, T b){return a+b;}
	static T inv(T a){return -a;}
};

void example(){
	BIT<3, AG> bit(3, 4, 5); //3D 3x4x5 bit
	bit.add(5, 0, 0, 0); //added 5 at first point
	cout << bit.query(0, 2, 0, 3, 0, 4) << endl; //query of whole bit
}
