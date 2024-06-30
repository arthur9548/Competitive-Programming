//Title: Disjoint Set Union (DSU) / Union Find Structure
//Description: eficient merging of disjoint components
//Complexity: amortized O(~1) merging and component identification
//Restrictions: none
//Observations:
//--- merge operation will return representatives of merged components for
//    aditional calculations
//Tested at: CSES-Road Construction

struct DSU {
	vi cr, rnk; //current representatives and level in dsu tree
	DSU(int n):cr(n),rnk(n, 0){rep(i, 0, n)cr[i] = i;}
	int repr(int a){return cr[a]==a?a:cr[a]=repr(cr[a]);}
	//use repr(a) instead of cr[a] for getting representative
	pii merge(int a, int b){
		a = repr(a); b = repr(b); if (rnk[b]>rnk[a])swap(a, b);
		pii reps = {a, b}; if (a==b)return reps;
		rnk[a] += (rnk[a]==rnk[b]); 
		cr[b] = a; return reps;
	}
};