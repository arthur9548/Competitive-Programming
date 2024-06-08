//Title: Binary Indexed Tree (BIT)
//Description: fast range query and point update
//Restrictions: elements must be of a abelian group
//Observations: 1-indexed!
//Complexity: O(logn) query and update, about 1.5x faster than recursive segtree

inline int lastbit(int pos){return pos&(-pos);}

template<int dim, typename type>
struct BIT{
	int n;
	vector<BIT<dim-1, type>> bit;
	template<typename... Args>
	BIT(int s, Args... args):n(s+1),bit(n, BIT<dim-1, type>(args...)){}
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
