//Title: Binary Indexed Tree (BIT)
//Description: fast range query and point update
//Restrictions: elements must be of a abelian group (+=, -=, 0)
//Observations: 1-indexed only in implementation, interface is 0-indexed
//Complexity: O(logn) query and update, about 1.5x faster than recursive segtree
//Tested at: CSES-Dynamic Range Sum Queries and CSES-Forest Queries II

template<int dim, typename type>
struct BIT{
	int n;
	vector<BIT<dim-1, type>> bit; //or map<int, BIT<dim-1, type>> if sparse
	template<typename... Args>
	BIT(int s, Args... args):n(s+1),bit(n, BIT<dim-1, type>(args...)){}
	inline int lastbit(int pos){return pos&(-pos);}
	template<typename...Args>
	void add(int pos, Args... args){
		for(pos++;pos<=n;pos+=lastbit(pos))bit[pos].add(args...);
	}
	template<typename...Args>
	type query(int l, int r, Args... args){
		type res(0); r++;
		for(;r>=1;r-=lastbit(r))res+=bit[r].query(args...);
		for(;l>=1;l-=lastbit(l))res-=bit[l].query(args...);
		return res;
	}
};

template<typename type>
struct BIT<0, type>{
	type val = type(0);
	void add(type nval){val+=nval;}
	type query(){return val;}
};

void example(){
	BIT<3, int> bit(3, 4, 5); //3D 3x4x5 bit
	bit.add(0, 0, 0, 5); //added 5 at first point
	cout << bit.query(0, 2, 0, 3, 0, 4) << endl; //query of whole bit
}
