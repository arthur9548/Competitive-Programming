int fact[MXN];
int ifact[MXN];
 
int fexp(int a, int b){
	if (b == 0)return 1;
	int res = (fexp(a, b/2))%MOD; res = (res*res)%MOD;
	if (b%2) res = (res*a)%MOD;
	return res;
}

void buildfact(){
	fact[0] = 1;
	rep(i, 1, MXN)fact[i] = (fact[i-1]*i)%MOD;
	ifact[MXN-1] = fexp(fact[MXN-1], MOD-2);
	repinv(i, MXN-2, 0)ifact[i] = ((i+1)*ifact[i+1])%MOD;
}

int bino(int n, int k){
	return (((fact[n]*ifact[k])%MOD)*ifact[n-k])%MOD;
}

template<typename num> struct Combinatorics{
	vector<num> fact, ifact;
	Combinatorics(int mxn){
		fact.resize(mxn); ifact.resize(mxn);
		fact[0] = num(1);
		rep(i, 1, mxn)fact[i] = fact[i-1]*num(i);
		ifact[mxn-1] = num(1)/fact[mxn-1];
		repinv(i, mxn-2, 0)ifact[i] = ifact[i+1]*num(i+1);
	}
	
	num choose(int n, int k){
		return fact[n]*ifact[k]*ifact[n-k];
	}
};