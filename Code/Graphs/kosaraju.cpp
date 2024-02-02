//Kosaraju: algorithm to get strongly connected components 
//sorted by topological order in O(V+E)
//Structure contains info on condensed graph and components
struct Kosaraju{
	int n, totalcomps; //number of strongly connected components
	vvi g, gi; //graph structure
	vvi cdg, cdgi; //condensed graph
	vi component; //component of vertex (sorted by topological order)
	vvi comps; //component list
	
	Kosaraju(vvi& og){
		n = og.size(); totalcomps=0;
		g.resize(n); gi.resize(n);
		component.resize(n);
		rep(i, 0, n){
			for(int j : og[i]){
				gi[j].pb(i); g[i].pb(j);
			}
		}
		run(); //Kosaraju algorithm
	}
	
	void run(){
		vb visited(n, false);
		vi order, curvs;
		auto dfs1 = [&](auto self, int v){
			if (visited[v])return;
			visited[v] = true;
			for(int adj : g[v])self(self, adj);
			order.pb(v);
		};
		auto dfs2 = [&](auto self, int v, int curcomp){
			if (visited[v])return;
			visited[v] = true;
			component[v] = curcomp; curvs.pb(v);
			for(int adj : gi[v]){
				if (visited[adj] and component[adj]!=curcomp){
					int compadj = component[adj];
					cdg[compadj].pb(curcomp); cdgi[curcomp].pb(compadj);
				}
				else self(self, adj, curcomp);
			}
		};
		rep(i, 0, n)dfs1(dfs1, i);
		rep(i, 0, n)visited[i] = false;
		reverse(all(order));
		rep(i, 0, n){
			int v = order[i];
			if (visited[v])continue;
			cdg.pb(vi()); cdgi.pb(vi());
			dfs2(dfs2, v, totalcomps); totalcomps++;
			comps.pb(curvs); curvs.clear();
		}
	}
};
