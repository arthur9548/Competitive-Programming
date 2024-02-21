//Scaling maxflow: algorithm to get maxflow in E*log(maxflow)*(V or E)
//depending on option of Dinic or DFS Ford-Fulkerson
//Can be used for matchings and mincuts
//In case of non-integer values, remove scaling property
//(mxbound=EPS), with a V factor instead of log in complexity

struct Edge{
	int a, b, w, ow; //vertices and weight (capacity left)
	bool is_reverse;
	Edge(int aa, int bb, int ww, bool isrev){
		a = aa; b = bb; w = ww; ow = ww; is_reverse = isrev;
	}	
};

struct Scaling{ //Scaling maxflow
	int n, m, mxbound;
	vvi g;
	vector<Edge> edges;
	
	Scaling(int n_){
		g.resize(n_); n = n_; m = 0; mxbound = 1;
	}
	
	void add_edge(int a, int b, int w){
		g[a].pb(m); g[b].pb(m+1); m += 2;
		edges.pb(Edge(a, b, w, false)); edges.pb(Edge(b, a, 0, true));
		while(w >= mxbound)mxbound <<= 1;
	}
	
	void restore(){ //restoring edges' capacity
		for(auto& e : edges)e.w = e.ow;
	}
	
	int ffmaxflow(int source, int sink){ //scaling ford-fulkerson maxflow
		int flow = 0;
		vb visited(n, false); int cbound=mxbound;
		auto dfs = [&](auto self, int v, int mn)->int{
			if (visited[v])return -1;
			visited[v] = true;
			if (v == sink)return mn;
			for(int eidx : g[v]){
				auto& e = edges[eidx];
				if (e.w < cbound)continue;
				int res = self(self, e.b, min(mn, e.w));
				if (res > 0){
					e.w -= res;
					edges[eidx^1].w += res;
					return min(mn, res);
				}
			}
			return -1;
		};
		while(cbound){ //attempts to get flow increase of at least curf
			int res = dfs(dfs, source, oo);
			rep(i, 0, n)visited[i] = false;
			if (res == -1)cbound /= 2;
			else flow += res; //keep increasing while possible
		}
		//restore();
		//uncomment if needs to restore edges capacity after algorithm
		return flow;
	}
	
	int dinicmaxflow(int source, int sink){ //scaling dinic
		int res = 0, cbound = mxbound;
		vi cedge(n, 0); vi level(n, -1);
		auto make_dag = [&](int bound)->bool{ //dinic dag
			level.assign(n, -1); level[source] = 0;
			queue<int> q; q.push(0);
			while(not q.empty()){
				int v = q.front(); q.pop();
				for(int eidx : g[v]){
					auto& e = edges[eidx];
					if (e.w < bound or level[e.b]!=-1)continue;
					level[e.b] = level[v]+1; q.push(e.b);
				}
			}
			return level[sink]!=-1;
		};
		auto eok = [&](Edge& edge)->bool{ //conditions for edge use
			if (level[edge.b] != level[edge.a]+1)return false;
			if (edge.w == 0)return false;
			return true;
		};
		auto push_flow = [&](auto self, int v, int flow)->int{
			if (v == sink)return flow;
			int pushed = 0; //flow pushed to sink so far
			for(int& i = cedge[v]; i < sz(g[v]); i++){ //avoid reusing edges
				int eidx = g[v][i]; auto& e = edges[eidx];
				if (not eok(e))continue;
				int f = self(self, e.b, min(flow, e.w));
				flow -= f; pushed += f;
				e.w -= f; edges[eidx^1].w += f;
				if (flow==0)return pushed; //early exit
			}
			return pushed;
		};
		
		while(cbound){ //max flow increase is of at least cbound
			while(make_dag(cbound)){ //dinic procedure
				cedge.assign(n, 0);
				while(int cf = push_flow(push_flow, source, oo)) res += cf;
			}
			cbound >>= 1;
		}
		//restore();
		//uncomment if needs to restore edges capacity after algorithm
		return res;
	}
	
	vi mincut(int source, int sink){ //default mincut
		ffmaxflow(source, sink); //changeable
		vb visited(n,false);
		auto dfs = [&](auto self, int v){
			if (visited[v])return;
			visited[v] = true;
			for(int eidx : g[v]){
				if (edges[eidx].w)self(self, edges[eidx].b);
			}
		};
		dfs(dfs, source);
		vi ans;
		rep(i, 0, edges.size()){
			auto e = edges[i];
			if (visited[e.a] and not visited[e.b] and e.w == 0 and not e.is_reverse){
				ans.pb(i);
			}
		}
		return ans;
	}
};
