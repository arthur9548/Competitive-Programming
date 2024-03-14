//Min cost max flow: getting max flow in graph with minimum cost, 
//complexity is difficult to state but is related to F (max flow value),
//C (max cost unit/edge), V and E
//Algorithm uses potentials to calculate shortests paths with adaptative
//dijkstra (O(V*V) for dense graphs and O((V+E)logE) for sparse graphs)
//Both Dinic MCMF and usual greedy MCMF (similar to Edmonds-Karp) are supported


int lg2(int n){ //used solely for adaptative dijkstra
	return __builtin_popcountll(1ll)-__builtin_popcountll(n);
}

struct Edge{
	int a, b, w, c; //w = capacity left, c = cost per unit
	Edge(int aa, int bb, int ww, int cc){
		a = aa; b = bb; c = cc; w = ww;
	}
};
 
struct MCMF{
	int n, m, rm; //rm = number of unblocked edges
	vvi g;
	vector<Edge> edges;
	vi dists, pots; //current distances and potentials
	
	MCMF(int n_){
		n = n_; m = 0;
		g.resize(n); dists.resize(n); pots.resize(n);
	}
	
	void add_edge(int a, int b, int w, int c){
		g[a].pb(m); g[b].pb(m+1); m += 2;
		edges.eb(a, b, w, c); edges.eb(b, a, 0, -c);
	}
	
	int pot_cost(Edge& e){
		return pots[e.a]-pots[e.b]+e.c; //edge "distance" with potentials
	}
	
	void dists_init(int source){ //SPFA, to be used only if g has any c<0
		dists.assign(n, oo);
		vb inqueue(n, false);
		queue<int> q; q.push(source);
		inqueue[source] = true; dists[source] = 0;
		while(not q.empty()){
			int v = q.front(); q.pop();
			inqueue[v] = false;
			for(int eidx : g[v]){
				auto& e = edges[eidx];
				if (not e.w)continue;
				int adj = e.b, d = e.c;
				if (dists[adj] > dists[v]+d){
					dists[adj] = dists[v]+d;
					if (not inqueue[adj]){
						q.push(adj); inqueue[adj] = true;
					}
				}
			}
		}
	}
	
	vi dists_calc(int source){ //Dijkstra with potentials
		rep(v, 0, n)if (pots[v]<oo)pots[v] += dists[v]; //setting potentials
		bool sparse = ((n+rm)*lg2(rm)) <= (n*n); //complexity decision
		//sparse = true; //usually graphs are very sparse
		dists.assign(n, oo);
		vb visited(n, false);
		vi path(n, -1);
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		auto get_best = [&]()->int{
			int best = -1;
			if (sparse){
				if (pq.empty())return best;
				else{ best = pq.top().second; pq.pop(); return best;}
			}
			else{
				rep(v, 0, n){
					if (visited[v])continue;
					if (best==-1)best = v;
					else if (dists[v] < dists[best])best = v;
				}
				return best;
			}
		};
		auto process = [&](int v){
			if (sparse)pq.push({dists[v], v});
		};
		dists[source] = 0;
		int v = source; process(v);
		while(v != -1){ //algorithm is adapted to current state
			if (not visited[v]){
				visited[v] = true;
				for(int eidx : g[v]){
					auto& e = edges[eidx];
					if (not e.w)continue;
					if (dists[e.b] > dists[v]+pot_cost(e)){
						dists[e.b] = dists[v]+pot_cost(e);
						path[e.b] = eidx;
						process(e.b);
					}
				}
			}
			v = get_best();
		}
		return path;
	}
 
	pii simplemcmf(int source, int sink){
		rm = m;
		int flow = 0, cost = 0; 
		//dists_init(source); //comment if all cs>0, SPFA becomes redundant
		while(true){
			vi path = dists_calc(source); //getting a shorstest path
			if (path[sink]==-1)return {flow, cost};
			int v = sink, cf=oo, cc=0;
			while(v != source){ //using it to increase flow
				auto& e = edges[path[v]];
				cf = min(cf, e.w);
				v = e.a;
			}
			v = sink;
			while(v != source){
				auto& e = edges[path[v]];
				auto& re = edges[path[v]^1];
				cc += cf*e.c;
				e.w -= cf; 
				if (cf and e.w==0)rm--;
				if (cf and re.w==0)rm++;
				re.w += cf;
				v = e.a;
			}
			flow += cf; cost += cc;
		}
		return {flow, cost};
	}
	
	pii dinicmcmf(int source, int sink){
		rm = m;
		int res = 0, cost = 0; 
		vi cedge(n, 0); vb online(n, false);
		auto in_spdag = [&](Edge& e)->bool{
			if (not e.w)return false;
			return (dists[e.b]-dists[e.a]==pot_cost(e));
		};
		auto push_flow = [&](auto self, int v, int flow)->int{//Dinic DFS
			if (v == sink)return flow;
			online[v] = true;
			int pushed = 0;
			for(int& i = cedge[v]; i < sz(g[v]); i++){
				int eidx = g[v][i]; auto& e = edges[eidx];
				if (not in_spdag(e))continue;
				if (online[e.b])continue; //avoids cycle with 0 cost
				int f = self(self, e.b, min(flow, e.w));
				flow -= f; pushed += f;
				e.w -= f; 
				if (f and e.w==0)rm--;
				if (edges[eidx^1].w==0 and f)rm++; 
				edges[eidx^1].w += f;
				cost += e.c*f;
				if (flow==0){
					online[v] = false; return pushed;
				}
			}
			online[v] = false;
			return pushed;
		};
		
		//dists_init(source); //comment if all cs>0, SPFA becomes redundant
		while(true){
			dists_calc(source); //uses s.p. DAG as Dinic DAG
			if (dists[sink]==oo)break; //sink is unreachable
			cedge.assign(n, 0);
			while(int cf = push_flow(push_flow, source, oo)) res += cf;
		}
		return {res, cost};
	}
};	
