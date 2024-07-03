//Title: Hierholzer algorithm
//Description: constructs an Eulerian path/cycle
//Complexity: O(V+E)
//Restrictions: path/cycle must exist (check beforehand)
//Observations: check comment on existence check
//Tested at: CSES-Mail Delivery and CSES-Teleporters Path

//On existence of Eulerian paths and cycles:
//--- Graph must be edge-connected
//--- If indegree==outdegree / degree%2==0 for all vertices:
//    -> All Eulerian paths are cycles
//--- If not for one pair, each with +/- 1 of degree:
//    -> There is an Eulerian path between these two and no cycles

vi hierholzer(int n, vector<pii>& edges, bool directed, int inic=0){
	int m = sz(edges); vi used(m, false); vector<vi> g(n);
	rep(i, 0, m){
		auto [a, b] = edges[i]; g[a].pb(i); 
		if (not directed) g[b].pb(i);
	}
	vi ans, st = {inic};
	while(not st.empty()){
		int v = st.back();
		while(not g[v].empty() and used[g[v].back()])g[v].pop_back();
		if (g[v].empty())st.pop_back(), ans.pb(v);
		else {
			int idx = g[v].back(); g[v].pop_back();
			used[idx] = true; auto [a, b] = edges[idx];
			st.pb((v==a ? b : a));
		}
	}
	reverse(all(ans)); return ans;
}