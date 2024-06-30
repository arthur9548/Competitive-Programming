//Title: Dijkstra algorithm
//Description: shortest distance from sources to all vertices
//Complexity: O((V+E)log(V+E)) usual, O(E+V^2) dense version
//Restrictions: distance unit should have +, > and conversion from 0 and oo
//Observations:
//--- can be used to generate shortest paths DAG
//Tested at: CSES-Shortest Routes I

#define V vector

template<class T>
V<T> dkstra(V<int> sources, V<V<pair<int, T>>> & g){
	int n = g.size(); V<bool> visited(n, false); 
	V<T> dists(n, T(oo)); //infinite distance
	using P = pair<T, int>; priority_queue<P, V<P>, greater<P>> pq;
	for(int s : sources)pq.push({dists[s]=T(0), s});
	while(not pq.empty()){
		auto [d, v] = pq.top(); pq.pop();
		if (visited[v])continue;
		visited[v] = true;
		for(auto [adj, nd] : g[v])
			if (dists[adj] > d+nd)
				pq.push({dists[adj]=d+nd, adj});
	}			//edge in spdag from v to adj
	return dists;
}

template<class T>
V<T> densedkstra(V<int> sources, V<V<pair<int, T>>> & g){
	int n = g.size(); V<bool> visited(n, false);
	V<T> dists(n, T(oo));
	for(int s : sources)dists[s] = T(0);
	int v = sources[0];
	while(v != -1){
		visited[v] = true;
		for(auto [adj, nd] : g[v])dists[adj] = min(dists[adj], dists[v]+nd);
		v = -1; 
		rep(i, 0, n){
			if (visited[i])continue;
			if (v==-1 or dists[v]>dists[i])v = i;
		}
	}
	return dists;
}