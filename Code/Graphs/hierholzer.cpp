//Hierholzer: algorithm to get Eulerian path/circuit
//if it is guaranteed to exist in O(E) time O(DFS) memory
vi hierholzer(int n, vector<pii>& edges){
	vi ans; int m = edges.size();
	if (check(n, edges)){
		//a function should be created to check conditions
		//acording to type of graph and problem restrictions on
		//the path type and enpoints
		//base conditions: edge connectivity and vertex degree
		return ans; //empty vector if impossible
	}
	vvi g(n);
	rep(i, 0, m){
		int a = edges[i].first, b = edges[i].second;
		g[a].pb(i); g[b].pb(i); //remove the latter if it's directed
	}
	vb used(m, false);
	//algorithm with 0 as initial vertex
	vi st; st.pb(0);
	while(not st.empty()){
		int v = st.back();
		while(not g[v].empty() and used[g[v].back()])g[v].ppb();
		if (g[v].empty()){
			st.ppb(); ans.pb(v);
		}
		else {
			int idx = g[v].back(); g[v].ppb();
			auto e = edges[idx]; used[idx] = true;
			int adj = (v==e.first ? e.second : e.first);
			st.pb(adj);
		}
	}
	reverse(all(ans));
	return ans;
}

//Complete Hierholzer structure to all types of paths and graphs
//Same complexity and covers all cases, check if needed
struct Hierholzer {
	int n, m;
	bool directed;
	vvi g;
	vi indeg;
	vector<pii> edges;
	
	Hierholzer(int s, bool is_directed){
		n = s; directed = is_directed;
		g.resize(n); indeg.assign(n, 0);
		m = 0;
	}
	
	void add_edge(int a, int b){
		edges.pb({a, b});
		g[a].pb(m); indeg[b]++;
		if (not directed){
			g[b].pb(m); indeg[a]++;
		}
		m++;
	}
	
	int getadj(int a, int eidx){
		auto e = edges[eidx];
		return (a==e.first ? e.second : e.first);
	}
	
	bool checkconnect(int source=0){
		vb visited(n, false);
		auto dfs = [&](auto self, int v){
			if (visited[v])return;
			visited[v] = true;
			for(int eidx : g[v])self(self, getadj(v, eidx));
		};
		dfs(dfs, source);
		rep(v, 0, n)if (not visited[v] and indeg[v])return false;
		return true;
	}
	
	bool specialcase(int v){ //may be endpoints of noncircular path
		if (not directed)return sz(g[v])%2;
		else return sz(g[v])!=indeg[v];
	}
	
	bool endpointscheck(vi & v){
		vb isend(2, false);
		rep(i, 0, 2){
			int a = v[i];
			if (indeg[a]+1==sz(g[a]))isend[i] = false;
			else if (indeg[a]==sz(g[a])+1)isend[i] = true;
			else return false;
		}
		if (isend[0]==isend[1])return false;
		if (isend[0])swap(v[0], v[1]); //non circular path with start and end
		return true;
	}
	
	pii possible(bool circuit, int start){
		pii res = {-1, -1};
		if (not checkconnect(start))return res;
		vi special;
		rep(v, 0, n)if (specialcase(v))special.pb(v);
		if (not circuit and sz(special)!=2)return res;
		if (circuit and sz(special)!=0)return res;
		if (not circuit){
			if (directed and not endpointscheck(special))return res;
			else res = {special[0], special[1]};
		}
		else res = {0, 0}; 
		return res;
	}
	
	vi path(bool circuit, int start=0, int end=-1){
		vi res;
		pii base = possible(circuit, start);
		if (base.first!=start)return res;
		if (not circuit and base.second!=end)return res;
		vb used(m, false);
		vi st; st.pb(start);
		while(not st.empty()){
			int v = st.back();
			while(not g[v].empty() and used[g[v].back()])g[v].ppb();
			if (g[v].empty()){
				st.ppb(); res.pb(v);
			}
			else {
				int idx = g[v].back(); g[v].ppb();
				auto e = edges[idx]; used[idx] = true;
				int adj = (v==e.first ? e.second : e.first);
				st.pb(adj);
			}
		}
		reverse(all(res));
		return res;
	}
};
