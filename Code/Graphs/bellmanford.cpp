//Bellman-Ford algorithm: shortest paths from source in O(V*E)
//Also detects and identifyes negative cycle in graph
//Can be multisource if needed
vi bellmanford(int n, int source, vector<pair<int, pii>> & edges){
	vi dists(n, oo); //distances from source
	dists[source] = 0;
	vi path(n, -1); //if path recover is needed, like functional graph
	bool worked = true;
	rep(i, 0, n){
		for(auto e : edges){
			int c = e.first, a = e.second.first, b = e.second.second;
			if (dists[a]==oo)continue;
			if (dists[a]+c < dists[b]){
				path[b] = a;
				if (i<(n-1))dists[b] = dists[a]+c;
				else worked = false; //negative cycle can be retrieved
			}
		}
	}
	if (not worked)dists.clear(); //negative cycle
	return dists;
}


//Optimized Bellman-Ford
//O(E*V), but is closer to O(E) in random graphs
vi spfa(int n, vector<vector<pii>> & g, int source){
	vi dists(n, oo); //distances from source
	vector<bool> inqueue(n, false);
	vi visited(n, 0); //counter to stop infinite loop
	queue<int> q; //spfa queue and functions
	auto enqueue = [&](int v){
		if (inqueue[v])return;
		q.push(v); inqueue[v] = true;
	};
	auto dequeue = [&]()->int{
		int v = q.front(); q.pop();
		inqueue[v] = false; return v;
	};
	enqueue(source); dists[source] = 0;
	while(not q.empty()){
		int v = dequeue();
		if (visited[v]>n)return vector<int>() //negative cycle
		for(auto edge : g[v]){
			int adj = edge.first, d = edge.second;
			if (dists[adj] > dists[v]+d){
				dists[adj] = dists[v]+d;
				enqueue(adj); visited[adj]++;
			}
		}
	}
	return dists;
}
