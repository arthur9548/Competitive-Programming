vector<vector<int>> g(MXN);
vector<pii> edges(4*MXN);
bool visited[MXN];

int n, m, x;
 
int rev(int idx){
	if (idx >= 2*MXN) return idx-2*MXN;
	else return 2*MXN+idx;
}
 
void restart(){
	rep(i, 0, n)visited[i] = false;
}
 
int dfs(int v, int mn){
	if (visited[v])return -1;
	if (v == n-1)return mn;
	visited[v] = true;
	for(int idx : g[v]){
		if (visited[edges[idx].first] or edges[idx].second < x)continue;
		int res = dfs(edges[idx].first, min(mn, edges[idx].second));
		if (res != -1){
			edges[idx].second -= res; edges[rev(idx)].second += res; return res;
		}
	}
	return -1;
}

void addedge(int idx, int a, int b, int c){
	if (b == 0 or a == n-1)continue;
	edges[idx] = {b, c}; edges[rev(idx)] = {a, c};
	g[a].pb(idx); g[b].pb(rev(idx));
}

int scalingff(){
	int maxflow = 0; x = oo;
	while(x){
		restart(); int res = dfs(0, oo);
		if (res != -1)maxflow += res;
		else x /= 2;
	}
	return maxflow;
}

void filldfs(int v){
	if (visited[v])return;
	visited[v] = true;
	for(int idx : g[v])if(edges[idx].second>0)filldfs(edges[idx].first);
}
 
vector<pii> mincut(){
	vector<pii> res; 
	int ignore = scalingff();
	restart(); filldfs(0);
	rep(i, 0, n){
		if (not visited[i])continue;
		for(int idx : g[i]){
			if (visited[edges[idx].first])continue;
			if (edges[idx].second == 0)res.pb({i, edges[idx].first});
		}
	}
	return res;
}