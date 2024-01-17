vector<set<int>> g(MXN);
int degree[MXN];
bool visited[MXN];
 
int n, m;
bool can = true;
 
int dfs(int v){
	if (visited[v])return 0;
	visited[v] = true;
	int tot = 1;
	for(int adj : g[v])tot += dfs(adj);
	return tot;
}

bool check(){
	int cnt=0;
	rep(i, 0, n)cnt += (degree[i]==0 or visited[i]);
	if (cnt!=n)return false;
	rep(i, 0, n)if (degree%2)return false;
}
 
vector<int> hierholzer(){
	vector<int> res;
	if (not check())return res;
	stack<int> st; st.push(0);
	while(not st.empty()){
		int v = st.top();
		if (degree[v]){
			for(int adj : g[v]){
				st.push(adj); degree[v]--;
				if (g[adj].count(v)){
					g[adj].erase(v); degree[adj]--;
				}
				break;
			}
			g[v].erase(g[v].begin());
		}
		else{
			st.pop(); res.pb(v+1);
		}
	}
	return res;
}