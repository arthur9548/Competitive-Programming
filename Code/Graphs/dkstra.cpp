//Dijsktra: shortest paths from source to all other vertices in O(logV(E+V))
//Assumes positive weights in all edges
//Can be adapted to creat shortest path DAG from root
//Easily modified to be multisource
vi dkstra(int source, vector<vector<pii>> & g){
	int n = g.size();
	vector<bool> visited(n, false); //vertices visited only once
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
