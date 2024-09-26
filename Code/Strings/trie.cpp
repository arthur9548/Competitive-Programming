template<class T>
struct Trie{
	vector<hash_map<T, int>> g; vi cnt;
	Trie():g(1),cnt(1,0){}
	int new_node(){g.pb(hash_map<T, int>()); cnt.pb(0); return sz(g)-1;}
	template<class S> void insert(const S & s){
		int cur = 0;
		for(T c : s){
			if (g[cur].count(c))cur = g[cur][c];
			else cur = g[cur][c] = new_node();
		}
		cnt[cur]++;
	}
};