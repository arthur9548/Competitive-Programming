//Dijsktra: shortest paths from source to all other vertices in O(V + ElogV)
//Assumes positive weights in all edges
//Can be adapted to creat shortest path DAG from root
//Easily modified to be multisource
vi dkstra(int source, vector<vector<pii>> & g){
	int n = g.size();
	vb visited(n, false); //vertices visited only once
	vi dists(n, oo);
	dists[source] = 0;
	priority_queue<pii, vector<pii>, greater<pii>> pq; //min heap
	pq.push({0, source});
	while(not pq.empty()){
		auto p = pq.top(); pq.pop();
		int v = p.second, d = p.first;
		if (visited[v])continue;
		visited[v] = true;
		for(auto edge : g[v]){
			int adj=edge.first, nd=edge.second;
			if (dists[adj] > d+nd){ //optimizes memory and runtime
				dists[adj] = d+nd;
				pq.push({d+nd, adj});
				//space to add the resulting edge in SPDAG
			}
		}
	}
	return dists; //default returning
}

//For dense graphs, a V*V approach is faster than ElogV, 
//since E = O(V*V)
vi densedkstra(int source, vector<vector<pii>> & g){
	int n = g.size();
	vb visited(n, false);
	vi dists(n, oo);
	dists[source] = 0;
	auto get_min = [&]()->int{
		int best = -1;
		rep(v, 0, n){
			if (visited[v])continue;
			if (best==-1)best = v;
			else if (dists[v] < dists[best])best = v;
		}
		return best;
	};
	int v = source;
	while(v != -1){
		visited[v] = true;
		for(auto edge : g[v]){
			int adj = edge.first, nd = edge.second;
			if (dists[adj] > dists[v]+nd){
				dists[adj] = dists[v]+nd;
			}
		}
		v = get_min();
	}
	return dists;
}
