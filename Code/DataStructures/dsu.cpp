//DSU: structure to unite disjoint sets
//Total time is ~O(n) (slightly worse)
struct DSU {
	int components; //number of components
	vi cur_rep, level; //representatives and level in dsu tree
	vi szs; //size of each component
	
	DSU(int n){
		cur_rep.resize(n); level.assign(n, 0); szs.assign(n, 1);
		rep(i, 0, n)cur_rep[i] = i;
		components = n;
	}
	
	int find_rep(int a){
		if (cur_rep[a]==a)return a;
		else return cur_rep[a] = find_rep(cur_rep[a]);
	}
	
	void merge(int a, int b){
		a = find_rep(a); b = find_rep(b);
		if (a==b)return;
		if (level[b]>level[a])swap(a, b);
		cur_rep[b] = a; 
		level[a] += (level[a]==level[b]);
		szs[a] += szs[b];
		components--;
	}
};
