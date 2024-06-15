//Title: multidimensional Prefix/Partial/Cummulative Sum (Psum)
//Description: static range queries
//Complexity: O(n^D) build and memory, O(1) query
//Restrictions: elements must belong to a Group (+, -, id)
//Observations:
//--- 1-indexed in internal implementation only
//--- Query has a constant factor of 2^D
//--- Don't forget to "init" Psum before querying!
//Tested at: CSES-Static Range Sum Queries and CF-Counting Rectangles is Fun

#define MAs template<class... As> //multiple arguments
template<int D, class T>
struct Psum{
	int n;
	vector<Psum<D-1, T>> v;
	MAs Psum(int s, As... ds):n(s+1),v(n,Psum<D-1, T>(ds...)){}
	MAs void set(T x, int p, As... ps){v[p+1].set(x, ps...);}
	void push(auto p){rep(i, 1, n)v[i].push(p.v[i]);}
	void init(){rep(i, 1, n)v[i].init(),v[i].push(v[i-1]);}
	MAs T query(int l, int r, As... ps){return v[r+1].query(ps...)-v[l].query(ps...);}
};

template<class T>
struct Psum<0, T>{
	T val={T::id};
	void set(T x){val=x;}
	void push(auto a){val=a.val+val;}
	void init(){}
	T query(){return val;}
};

struct G{
	int v; static const int id = 0;
	G operator+(const G & o){return {v+o.v};}
	G operator-(const G & o){return {v-o.v};}
};

void example(){
	Psum<3, G> psum(3, 5, 4); //3d 3x5x4 psum
	psum.set(G{1}, 0, 0, 0); //origin has value 1
	psum.set(G{2}, 1, 2, 3);
	psum.init(); //important!
	cout << psum.query(0, 1, 0, 2, 0, 3).v << endl; //1+2=3
}
