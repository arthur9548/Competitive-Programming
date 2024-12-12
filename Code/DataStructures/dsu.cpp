/**
	* Title: Disjoint Set Union (DSU) / Union Find Structure
	* Description: efficient localization and merging of disjoint components
	* Complexity:
		- Repr and Merge: amortized O(~1) with path compression or O(log(n))
		- Memory: O(n)
	* Observations:
		- Merge can be customized or changed depeding on the problem
	* Tested at:
		- Road Construction (CSES)
*/

struct DSU {
	vi cr, rnk; //current representatives and level in dsu tree
	DSU(int n):cr(n),rnk(n, 0){rep(i, 0, n)cr[i] = i;}
	int repr(int a){return cr[a]==a?a:cr[a]=repr(cr[a]);}
	//use repr(a) instead of cr[a] for getting representative
	pii merge(int a, int b){ //returns merged components
		a = repr(a); b = repr(b); if (rnk[b]>rnk[a])swap(a, b);
		pii reps = {a, b}; if (a==b)return reps;
		rnk[a] += (rnk[a]==rnk[b]); //or +=rnk[b] to remove compression
		cr[b] = a; return reps;
	}
};