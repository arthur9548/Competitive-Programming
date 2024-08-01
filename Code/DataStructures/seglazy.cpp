template<class S>
struct LazySeg{using T = typename S::T; using L = typename S::L;
	int n; vi tgd;
	vector<T> seg;
	vector<L> tag;
	LazySeg(int s):n(s),tgd(2*n,0),seg(2*n,S::id),tag(2*n){}
	
	void prop(int p){
		if (not tgd[p])return;
		tgd[p] = 0;
		seg[p] = S::a