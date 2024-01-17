vector<vector<int>> g(MMXN), gi(MMXN), scc(MMXN), scci(MMXN), comps(MMXN);
bool visited[MMXN];
bool active[MMXN];
int component[MMXN];
int degree[MMXN];
int value[MXN];
vector<int> order;
 
int n, m;

#define ai(x) (MXN+x)
#define nai(x) (MXN-x)
#define id(x) (-(MXN-x))
 
void restart(){
	rep(i, 0, MMXN)visited[i] = false;
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
	component[v] = comp;
	comps[comp].pb(v);
	for(int adj : gi[v]){
		if (visited[adj] and component[adj] != comp){
			int adjp = component[adj]; scc[adjp].pb(comp); scci[comp].pb(adjp);
			degree[adjp]++;
		}
		else dfs2(adj, comp);
	}
}
 
void kosaraju(){
	rep(i, 0, MMXN)if (active[i])dfs1(i);
	restart(); reverse(all(order));
	for(int v : order)dfs2(v, v);
	restart();
}

void addedge(int n1, int n2){
	g[nai(n1)].pb(ai(n2)); g[nai(n2)].pb(ai(n1));
	gi[ai(n2)].pb(nai(n1)); gi[ai(n1)].pb(nai(n2));
}

vector<int> kahn(){
	queue<int> q; vector<int> comps;
	rep(i, 0, MMXN)if (active[i] and component[i] == i and degree[i] == 0)q.push(i);
	while(not q.empty()){
		int v = q.front(); q.pop();
		comps.pb(v);
		for(int adj : scci[v]){
			degree[adj]--; if (degree[adj] == 0)q.push(adj);
		}
	}
}

void run(){
	rep(i, 1, n+1){
		active[ai(i)] = active[nai(i)] = true;
	}
	kosaraju();
	rep(i, 1, n+1){
		if (component[ai(i)] == component[nai(i)]){
			cout << IMP; return;
		}
	}
	order = kahn();
	for(int v : order){
		for(int el : comps[v]){
			int var = id(el);
			if (not value[abs(var)])value[abs(var)] = var > 0 ? 1 : -1;
		}
	}
}