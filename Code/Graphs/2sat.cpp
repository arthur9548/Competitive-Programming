//Two SAT: model to solve boolean equation in O(N+M), where
//N is the number of variables and M is the number of AND clauses
//Clauses should contain only two variables (reduction to implications)
struct TwoSAT{
	int n; //number of variables
	vvi g; //implication graph
	Kosaraju kos; //needs Kosaraju structure (only comps are needed)
	vi values; //values of variables (empty if impossible)
	//1 = true, 0 = false
	
	TwoSAT (int s){
		n = s; g.resize(2*n);
	}
	
	int idx(int a, bool value){
		return 2*a + value;
	}
	
	//boolean functions (add more)
	void addor(int a, bool isa, int b, bool isb){
		a = idx(a, isa); b = idx(b, isb);
		g[a^1].pb(b); g[b^1].pb(a);
	}
	
	//run Kosaraju to get values by implications
	void run(){
		kos = Kosaraju(g);
		repstep(i, 0, 2*n, 2)if (kos.component[i]==kos.component[i+1])return;
		values.assign(n, -1);
		for(auto& v : kos.comps){
			for(int val : v){
				if (values[val>>1]!=-1)continue;
				values[val>>1] = 1-val%2;
			}
		}
	}
};
