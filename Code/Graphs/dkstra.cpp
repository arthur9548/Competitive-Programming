//Dijsktra: menores caminhos de todos os vertices em relação a
//um vertice ou um conjunto deles (multisource)
vi dkstra(int root, vector<vector<pii>> & g){
	int n = g.size();
	vector<bool> visited(n, false);
	vi dists(n, oo);
	dists[root] = 0;
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push({0, root});
	while(not pq.empty()){
		auto p = pq.top(); pq.pop();
		int v = p.second, d = p.first;
		if (visited[v])continue;
		visited[v] = true;
		for(auto p2 : g[v]){
			int adj=p2.first, nd=p2.second;
			if (dists[adj] > d+nd){ //optimizes memory and runtime
				dists[adj] = d+nd;
				pq.push({d+nd, adj});
			}
		}
	}
	return dists; //default returning
}