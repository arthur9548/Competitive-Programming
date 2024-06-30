//Title: Bellman-Ford and SPFA algorithms
//Description: shortest distance from sources and negative cycle detection
//Complexity: O(V*E), SPFA is O(E) in random graphs
//Restrictions: distance unit should have +, < and conversion to 0 and oo
//Observations:
//--- Functions return empty vector in case of negative cycle
//--- The latter can be retrieved by path recover
//Tested at: CSES-High Score

template<class T>
vector<T> bellmanford(vi sources, vector<vector<pair<int, T>>> & g){
	int n = sz(g); vector<T> dists(n, T(oo));
	for(int s : sources)dists[s] = T(0);
	bool worked = true;
	vector<tuple<T, int, int>> edges;
	rep(a, 0, n)for(auto [b, c] : g[a])edges.pb({c, a, b});
	rep(i, 0, n+1){
		for(auto [c, a, b] : edges){
			if (dists[a]==T(oo))continue;
			if (dists[a]+c < dists[b]){
				if (i<n)dists[b] = dists[a]+c;
				else worked = false;
			}
		}
	}
	if (not worked)dists.clear(); //negative cycle
	return dists;
}

template<class T>
vector<T> spfa(vi sources, vector<vector<pair<int, T>>> & g){
	int n = sz(g); vector<T> dists(n, T(oo));
	vector<bool> inq(n, false); vi visited(n, 0);
	queue<int> q;
	for(int s : sources){
		q.push(s); inq[s] = true; dists[s] = T(0);
	}
	while(not q.empty()){
		int v = q.front(); q.pop(); inq[v] = false;
		if (visited[v]>n)return vector<T>();
		for(auto [adj, d] : g[v]){
			if (dists[adj]>dists[v]+d){
				dists[adj] = dists[v]+d;
				if (not inq[adj])q.push(adj); 
				inq[adj] = true; visited[adj]++;
			}
		}
	}
	return dists;
}