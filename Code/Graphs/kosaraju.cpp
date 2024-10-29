//Title: Kosaraju algorithm
//Description: strongly connected components topologically sorted
//Complexity: O(V+E)
//Restrictions: none
//Observations:
//--- Contains component ID of vertices (cid), condensed graph (cdg)
//    of components and their list sorted in topological order
//Tested at: CSES-Planet and Kingdoms

struct Kosaraju{
	int n; vi cid; 
	vector<vi> cdg, comps;
	
	Kosaraju(vector<vi>& g):n(sz(g)), cid(n, -1){
		vector<vi> gi(n); rep(i, 0, n)for(int j : g[i])gi[j].pb(i);
		vi vis(n, 0), order;
		auto dfs1 = [&](auto rec, int v)->void{
			if (vis[v])return; 
			vis[v] = true;
			for(int adj : g[v])rec(rec, adj);
			order.pb(v);
		};
		rep(i, 0, n)dfs1(dfs1, i);
		reverse(all(order)); vis = vi(n, 0);
		auto dfs2 = [&](auto rec, int v)->void{
			if (vis[v])return;
			vis[v] = true; cid[v] = sz(comps)-1;
			comps.back().pb(v); 
			for(int adj : gi[v]){
				if (not vis[adj])rec(rec, adj);
				else if (cid[adj]!=cid[v])cdg[cid[adj]].pb(cid[v]);
			}
		};
		for(int v : order){
			if (vis[v])continue;
			cdg.pb(vi()); comps.pb(vi());
			dfs2(dfs2, v);
		}
	}
};