//Sparse Table: RMQ in O(nlogn) build, O(1) query
//Customizable type and operations

int lg(int x){
	return __builtin_clzll(1ll) - __builtin_clzll((long long)x);
	// log2(x) in O(1)
}

#define type int
#define spop max

struct SpTable{
	int n, logn;
	vector<type> values; //original values, not needed besides constructor
	vector<vector<type>> table;
	
	SpTable(vector<type> & v){
		n = v.size(); logn = lg(n)+1;
		values = v; table.assign(logn, vector<type>(n));
		rep(i, 0, n)table[0][i] = values[i];
		rep(i, 1, logn){
			rep(j, 0, n-(1ll<<(i-1))){
				table[i][j] = spop(table[i-1][j], table[i-1][j+(1ll<<(i-1))]);
			}
		}
	}
	
	type query(int l, int r){
		assert l<=r;
		int k = lg(r-l+1);
		return spop(table[k][l], table[k][r+1-(1ll<<k)]);
	}
};
	
	
