/**
	* Title: Multidimensional Binary Indexed Tree (BIT)
	* Description: fast range query and point update
	* Complexity:
		- Query: O(op * (2 * log(n))^D + inv * (2 * log(n))^(D-1))
		- Add (update): O(log(n)^D * op)
		- Build: O(n^D)
		- Memory: O(n^D * T)
	* Restrictions:
		- S must be an abelian group (T, id, op, inv)
	* Observations:
		- 1-indexed and half-open only in internal implementation
		- Good constant factor
	* Tested at:
		- Dynamic Range Sum Queries (CSES)
		- Forest Queries II (CSES)
		- UFOs (Timus)
	* Based on: https://codeforces.com/blog/entry/64914
*/

#define MAs template<class... As> //multiple arguments
template<int D, class S> 
struct MBIT{ using T = typename S::T;
	int n; vector<MBIT<D-1, S>> bit;
	int lb(int x){return x&(-x);}
	MAs MBIT(int s, As... ds):n(s),bit(n+1, MBIT<D-1, S>(ds...)){}
	MAs void add(T x, int p, As... ps){
		for(p++;p<=n;p+=lb(p))bit[p].add(x, ps...);
	}
	MAs T query(int l, int r, As... ps){
		T lv=S::id,rv=S::id; r++;
		for(;r;r-=lb(r))rv=S::op(rv,bit[r].query(ps...));
		for(;l;l-=lb(l))lv=S::op(lv,bit[l].query(ps...));
		return S::op(rv,S::inv(lv));
	}
};

template<class S>
struct MBIT<0, S>{ using T = typename S::T; //base case 
	T val=S::id;
	void add(T x){val=S::op(val,x);}
	T query(){return val;}
};

struct SumGroup{
	using T = int;
	static constexpr T id = 0;
	static T op(T a, T b){return a+b;}
	static T inv(T a){return -a;}
};