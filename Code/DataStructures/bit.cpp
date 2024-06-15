//Title: multidimensional Binary Indexed Tree (BIT)
//Description: fast range query and point update
//Complexity: O(logn ^ D) query and update, O(n^D) memory
//Restrictions: elements must be of a abelian group (+=, -=, id)
//Observations: 
//--- 1-indexed only in implementation, interface is 0-indexed
//--- Very good constant factor
//Tested at: CSES-Dynamic Range Sum Queries and Timus-UFOs

#define MAs template<class... As> //multiple arguments
template<int D, class T> 
struct BIT{
	int n;
	vector<BIT<D-1, T>> bit;
	MAs BIT(int s, As... ds):n(s),bit(n+1, BIT<D-1, T>(ds...)){}
	inline int lastbit(int x){return x&(-x);}
	MAs void add(T x, int p, As... ps){
		for(p++;p<=n;p+=lastbit(p))bit[p].add(x, ps...);
	}
	MAs T query(int l, int r, As... ps){
		T res={T::id}; r++;
		for(;r>=1;r-=lastbit(r))res+=bit[r].query(ps...);
		for(;l>=1;l-=lastbit(l))res-=bit[l].query(ps...);
		return res;
	}
};

template<class T>
struct BIT<0, T>{
	T val={T::id};
	void add(T x){val+=x;}
	T query(){return val;}
};

struct AG{ //abelian group analogous to int addition
	int v; static const int id = 0;
	AG& operator+=(const AG& o){v+=o.v;return *this;}
	AG& operator-=(const AG& o){v-=o.v;return *this;}
};

void example(){
	BIT<3, AG> bit(3, 4, 5); //3D 3x4x5 bit
	bit.add(AG{5}, 0, 0, 0); //added 5 at first point
	cout << bit.query(0, 2, 0, 3, 0, 4).v << endl; //query of whole bit
}
