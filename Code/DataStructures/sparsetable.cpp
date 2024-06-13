//Title: multidimensional Sparse Table
//Description: static idempotent range queries
//Complexity: O((nlogn)^D) build and memory, O(1) query
//Restrictions: elements must be of an Idempotent Monoid (^, id)
//Observations:
//--- Query has a constant factor of 2^D
//--- Don't forget to "init" the Sparse Table before querying!
//Tested at: CSES-Static Range Mininum Queries and CF-Valiant's New Map (MLE)

template<int D, class T>
struct SpTable{
	using itab = vector<SpTable<D-1, T>>;
	int n;
	vector<itab> tab;
	inline int lg(signed x){return __builtin_clz(1)-__builtin_clz(x);}
	template<class... A>
	SpTable(int s, A... ds):n(s),
	tab(1+lg(n),itab(n,SpTable<D-1, T>(ds...))){}
	template<class... A>
	void set(T x, int p, A... ps){tab[0][p].set(x, ps...);}
	void join(auto a, auto b){
		rep(i, 0, 1+lg(n))rep(j, 0, n)
			tab[i][j].join(a.tab[i][j], b.tab[i][j]);
	}
	void init(){
		rep(i, 0, n)tab[0][i].init();
		rep(i, 0, lg(n))rep(j, 0, n-(1<<i))
			tab[i+1][j].join(tab[i][j], tab[i][j+(1<<i)]);
	}
	template<class... A>
	T query(int l, int r, A... ps){
		int k = lg(r-l+1); r+=1-(1<<k);
		return tab[k][l].query(ps...)^tab[k][r].query(ps...);
	}
};

template<class T>
struct SpTable<0, T>{
	T val={T::id};
	void set(T x){val=x;}
	void join(auto a, auto b){val=a.val^b.val;}
	void init(){}
	T query(){return val;}
};

struct IM{
	int v; static const int id = oo;
	IM operator^(const IM & o){return {min(v,o.v)};}
};

void example(){
	SpTable<3, IM> sp(4, 5, 3); //4x5x3 3D sparse table
	sp.set(IM{1}, 0, 2, 1); //point (0,2,1) has now value 1
	sp.init();
	cout << sp.query(0, 3, 0, 4, 0, 2).v << endl; // = "1" by id value
}
