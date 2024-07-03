//Title: Functional Graph structure
//Description:
//--- Contains usual information on Functional Graphs
//--- Reverse graph (gr), Directed Forest (fo), Tree Head (head),
//--- Cycle ID (cid) and Component Cycles (cycles)
//Complexity: O(n)
//Restrictions: must be functional graph
//Observations: reverse graph contains cycle edges (while Forest does not)
//Tested at: CSES-Planet Queries II

struct FunctGraph{
	int n; vi head, cid;
	vector<vi> gr, fo, cycles;
	
	FunctGraph(vi& fn):
		n(sz(fn)), head(n, -1), cid(n, -1), gr(n), fo(n){
		rep(i, 0, n)gr[fn[i]].pb(i);
		vi visited(n, 0);
		auto dfs = [&](auto rec, int v, int c)->void{
			head[v] = c; visited[v] = 1;
			for(int f : gr[v])if (head[f]!=f)fo[v].pb(f),rec(rec, f, c);
		};
		rep(i, 0, n){
			if (visited[i])continue;
			int l=fn[i], r=fn[fn[i]]; //Floyd algorithm
			while(l!=r) l=fn[l],r=fn[fn[r]];
			vi cur = {r}; l = fn[l];
			while(l!=r)cur.pb(l),l=fn[l];
			for(int x : cur)head[x]=x,cid[x]=sz(cycles);
			for(int x : cur)dfs(dfs, x, x);
			cycles.pb(cur);
		}
	}
};