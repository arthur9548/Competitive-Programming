/Functional Graph and auxiliary structures definition
//Binary Liftling in O(log max query)
//Distance between vertices in O(VlogV) build, O(logV) query
//Complete information about cycles and underlying trees

int lg2(int x){
	return __builtin_clzll(1ll)-__builtin_clzll((long long)x);
	//log2 in O(1)
}

struct BinLift{ //binary lifting table of a functional graph
	int n, lg;
	vvi bl;
	
	BinLift(){}
	BinLift(vi& fn, int maxq){
		n = fn.size(); lg = lg2(maxq)+2; //set max query beforehand
		bl.assign(lg+1, vi(n, -1));
		rep(i, 0, n){
			bl[0][i] = i;
			bl[1][i] = fn[i];
		}
		rep(k, 2, lg+1){
			rep(i, 0, n){
				int prev = bl[k-1][i];
				bl[k][i] = bl[k-1][prev];
			}
		}
	}
	
	int lift(int v, int qup){ //qup-th ancestor of v
		int cur = v;
		rep(i, 0, lg) if (qup & (1ll<<i))cur = bl[i+1][cur];
		return cur;
	}
};

struct FunctComp{ //component of a functional graph
	int n, csize; //number of vertices and size of its cycle
	unordered_map<int, int> ids, trad; //conversion between graph ids and component ids
	vi parent, incycle, treehead; //comp info
	vi treedepth, cycledepth; //more comp info
	vvi ginv; //directed cactus
	
	FunctComp(vi& vs, vi& fn){
		n = vs.size(); parent.assign(n, -1);
		int cid=0; 
		for(int x : vs) {
			trad[cid] = x; ids[x] = cid++;
		}
		for(int x : vs) parent[ids[x]] = ids[fn[x]];
		floyd(); buildtree(); //building for distance queries
	}
	
	//conversion functions
	int getid(int a){
		return ids[a];
	}
	int getreal(int a){
		return trad[a];
	}
	
	void floyd(){ //all cycle related info
		cycledepth.assign(n, 0);
		incycle.assign(n, 0);
		int l=0, r=0;
		l = parent[l]; r = parent[parent[r]];
		while(l != r){
			l = parent[l]; r = parent[parent[r]];
		}
		incycle[l] = true; l = parent[l];
		csize = 1;
		while(l != r){
			cycledepth[l] = csize++;
			incycle[l] = true; l = parent[l]; 
		}
	}
	
	int cycledist(int a, int b){
		return (csize + cycledepth[b] - cycledepth[a])%csize;
	}
	
	void buildtree(){ //all tree related info
		treedepth.assign(n, 0);
		treehead.assign(n, 0);
		ginv.resize(n);
		rep(i, 0, n)ginv[parent[i]].pb(i);
		auto dfs = [&](auto self, int v, int h, int d)->void{
			treehead[v] = h; treedepth[v] = d++;
			for(int adj : ginv[v]){
				if (incycle[adj])continue;
				self(self, adj, h, d);
			}
		};
		rep(i, 0, n)if (incycle[i])dfs(dfs, i, i, 0);
	}
};	

struct FunctGraph{ //main graph structure
	int n, compssize; //number of vertices and components
	vi parent, component; //acess to parent and component of vertex
	vvi g; //undirected graph
	vector<FunctComp> comps; //component array (subgraph)
	BinLift binlift; //binary lifting
	
	FunctGraph(vi& fn){
		n = fn.size(); parent.resize(n); g.resize(n);
		rep(i, 0, n){
			parent[i] = fn[i];
			g[i].pb(fn[i]); g[fn[i]].pb(i);
		}
		binlift = BinLift(parent, 2*n); //set maxquery beforehand
		createcomps();
	}
	
	void createcomps(){ //set all components of graph
		component.resize(n);
		compssize = 0; vi curcomp;
		vi visited(n, 0);
		auto dfs = [&](auto self, int v){
			if (visited[v])return;
			visited[v] = true; curcomp.pb(v);
			for(int adj : g[v])self(self, adj);
		};
		rep(i, 0, n){
			if (visited[i])continue;
			dfs(dfs, i); comps.pb(FunctComp(curcomp, parent));
			for(int x : curcomp)component[x] = compssize;
			compssize++; curcomp.clear();
		}
	}
	
	FunctComp& getcomp(int a){ //direct acess to subgraph, should be received with auto&
		return comps[component[a]];
	}
	
	int getdist(int a, int b){
		if (component[a]!=component[b]){
			//different components
			return -1;
		}
		auto& comp = getcomp(a);
		a = comp.getid(a); b = comp.getid(b);
		if (comp.incycle[a]){
			if (not comp.incycle[b]){
				//a in cycle and b is not
				return -1;
			}
			else return comp.cycledist(a, b);
		}
		else{
			if (comp.incycle[b])return comp.cycledist(comp.treehead[a], b)+comp.treedepth[a];
			else{
				if (comp.treedepth[b] > comp.treedepth[a]){
					//a is upper in tree
					return -1;
				}
				int v = binlift.lift(comp.getreal(a), comp.treedepth[a]-comp.treedepth[b]);
				if (comp.getid(v)!=b){
					//not ancestor in tree
					return -1;
				}
				else return comp.treedepth[a]-comp.treedepth[b];
			}
		}
	}
};