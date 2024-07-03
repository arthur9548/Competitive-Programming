//Title: Two Sat solver
//Description: finds existing solution to system of implications
//Complexity: O(N+M), N=variables, M=implications
//Restrictions: none
//Observations:
//--- Depends on Kosaraju structure!
//--- If system is not solvable returns empty value vector
//--- More logic functions can be implemented using "implies"
//Tested at: CSES-Giant Pizza

struct TwoSAT{
	int n; vector<vi> g;
	TwoSAT (int s):n(s),g(2*n){}
	void implies(int a, bool isa, int b, bool isb){g[2*a+isa].pb(2*b+isb);}
	void addor(int a, bool isa, int b, bool isb){
		implies(a,1^isa,b,isb); implies(b,1^isb,a,isa);
	}
	
	vi solve(){
		Kosaraju kos(g);
		rep(i, 0, n)if (kos.cid[2*i]==kos.cid[2*i+1])return vi();
		vi values(n, -1);
		for(auto& c : kos.comps)for(int a : c){
			if (values[a/2]!=-1)continue;
			else values[a/2] = (a&1)^1;
		}
		return values;
	}
};
