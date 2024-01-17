vector<vector<int>> g(MXN);
bool visited[MXN];
int depth[MXN];
pii spt[LG][2*MXN];
pii vs[2*MXN];
int ids[MXN];
 
int cur = 0;
int n, q;
 
int lg(int x){
	if (not x)return 0;
	return __builtin_clz(1) - __builtin_clz(x);
}
 
void restart(){
	rep(i, 0, MXN)visited[i] = false;
	cur = 0;
}
 
void depthdfs(int v){
	if (visited[v])return;
	visited[v] = true; depth[v] = cur; cur++;
	for(int adj : g[v])depthdfs(adj);
	cur--;
}
 
void eulertour(int v){
	if (visited[v])return;
	visited[v] = true; vs[cur] = {depth[v], v}; ids[v] = cur; cur++;
	for(int adj : g[v]){
		eulertour(adj); vs[cur] = {depth[v], v}; cur++;
	}
}
 
void buildsp(){
	rep(i, 0, 2*MXN){
		spt[0][i] = vs[i];
	}
	rep(i, 1, LG){
		rep(j, 0, 2*MXN-(1<<(i-1))){
			spt[i][j] = min(spt[i-1][j], spt[i-1][j+(1<<(i-1))]);
		}
	}
}

void buildlca(){
	depthdfs(0); restart(); eulertour(0); restart(); buildsp();
	//now ready to answer queries
}
 
int query(int v1, int v2){
	int p1 = ids[v1], p2 = ids[v2];
	if (p2<p1)swap(p1, p2);
	int k = lg(p2-p1+1);
	pii ans = min(spt[k][p1], spt[k][p2+1-(1<<(k))]);
	return ans.second;
}