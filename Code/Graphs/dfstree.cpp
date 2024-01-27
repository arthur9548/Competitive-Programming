vi g[MXN];
bool visited[MXN];
int depth[MXN];
matrix aid(MXN); //support to multi edges
int tin[MXN];
int t=0;
int low[MXN];
int art[MXN]; //if is articulation point
bool bridge[MXN]; //if edge is bridge

void dfs(int v, int p, int oid){
	if (visited[v])return;
	visited[v] = true;
	depth[v] = depth[p]+1;
	low[v] = tin[v] = t++;
	rep(i, 0, g[v].size()){
		int adj = g[v][i];
		int id = aid[v][i];
		if (not visited[adj]){
			dfs(adj, v, id);
			low[v] = min(low[v], low[adj]);
			if (low[adj]>=tin[v])art[v]++;
		}
		else{
			if (adj==p)continue;
			if (depth[adj]>=depth[v])continue;
			low[v] = min(low[v], tin[adj]); //is backedge
		}
	}
	if (low[v]==tin[v] and v!=p)bridge[oid] = true;
	if (art[v] and v==p)art[v]--;
}
