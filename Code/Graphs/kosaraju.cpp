vector<vector<int>> g(MXN), gi(MXN);
bool visited[MXN];
int component[MXN];
vector<int> order;
 
int n, m;

void restart(){
	rep(i, 0, n)visited[i] = false;
}

void dfs1(int v){
	if (visited[v])return;
	visited[v] = true;
	for(int adj : g[v]) dfs1(adj);
	order.pb(v);
}
 
void dfs2(int v, int comp){
	if (visited[v])return;
	visited[v] = true;
	for(int adj : gi[v])dfs2(adj, comp);
	component[v] = comp;
}

void kosaraju(){
	rep(i, 0, n)dfs1(i);
	restart(); reverse(all(order));
	for(int v : order)dfs2(v, v);
	restart();
}