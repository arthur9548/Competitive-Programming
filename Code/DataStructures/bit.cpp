//Title: Binary Indexed Tree (BIT)
//Description: fast range query and point update
//Restrictions: elements must be of a abelian group (+=, -=, 0)
//Observations: 1-indexed only in implementation, interface is 0-indexed
//Complexity: O(logn) query and update, about 1.5x faster than recursive segtree
//Tested at: CSES-Dynamic Range Sum Queries and CSES-Forest Queries II

template<int D, class T> 
struct BIT{
	int n;
	vector<BIT<D-1, T>> bit;
	template<class... A>
	BIT(int s, A... ds):n(s),bit(n+1, BIT<D-1, T>(ds...)){}
	inline int lastbit(int x){return x&(-x);}
	template<class... A> 
	void add(int pos, A... ps){
		for(pos++;pos<=n;pos+=lastbit(pos))bit[pos].add(ps...);
	}
	template<class... A>
	T query(int l, int r, A... ps){
		T res(0); r++;
		for(;r>=1;r-=lastbit(r))res+=bit[r].query(ps...);
		for(;l>=1;l-=lastbit(l))res-=bit[l].query(ps...);
		return res;
	}
};

template<class T>
struct BIT<0, T>{
	T val = T(0);
	void add(T nval){val+=nval;}
	T query(){return val;}
};

void example(){
	BIT<3, int> bit(3, 4, 5); //3D 3x4x5 bit
	bit.add(0, 0, 0, 5); //added 5 at first point
	cout << bit.query(0, 2, 0, 3, 0, 4) << endl; //query of whole bit
}
