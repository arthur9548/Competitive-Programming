//Topological sorting of graph in O(V+E)
//Dificult to make alterations on the algorithm itself,
//but alterations in graph and final order can be useful
//Reverse order of reverse graph is different from normal order!
vi kahn(vvi & g){
	int n = g.size();
	vi deg(n, 0);
	rep(i, 0, n)for(int adj : g[i])deg[adj]++;
	queue<int> q; rep(i, 0, n)if (not deg[i])q.push(i);
	//should be priority_queue if lexicographical order is wanted
	vi ans;
	while(not q.empty()){
		int v = q.front(); q.pop();
		ans.pb(v);
		for(int adj : g[v]){
			deg[adj]--; if (not deg[adj])q.push(adj);
      //doesn't support multiedges
		}
	}
	if (ans.size()!=n)ans.clear(); //empty vector if isn't dag
	return ans;
}
