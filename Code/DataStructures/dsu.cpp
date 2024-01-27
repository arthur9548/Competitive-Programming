struct DSU {
	vi cur_rep, level;
	
	DSU(int n){
		cur_rep.resize(n); level.assign(n, 0);
		rep(i, 0, n)cur_rep[i] = i;
	}
	
	int find_rep(int el){
		if (cur_rep[a]==a)return a;
		else return cur_rep[a] = find_rep(cur_rep[a]);
	}
	
	void merge(int a, int b){
		a = find_rep(a); b = find_rep(b);
		if (a==b)return;
		if (level[b]>level[a])swap(a, b);
		cur_rep[b] = a; level[a] += (level[a]==level[b]);
	}
};
