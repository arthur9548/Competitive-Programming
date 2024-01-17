constexpr int LG = 25;

int lg(int x){
	return __builtin_clzll(1ll) - __builtin_clzll(x);
}

int sptable[LG][MXN];
int v[MXN];
int n;

void buildtable(){
	rep(i, 0, n)sptable[0][i] = v[i];
	rep(i, 1, LG){
		rep(j, 0, n-(1ll<<(i-1))){
			sptable[i][j] = min(sptable[i-1][j], sptable[i-1][j+(1ll<<(i-1))]);
		}
	}
}

int query(int l, int r){
	if (r < l)return 0;
	int k = lg(r-l+1);
	return min(sptable[k][l], sptable[k][r+1-(1ll<<k)]);
}