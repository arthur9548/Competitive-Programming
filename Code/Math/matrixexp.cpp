matrix iden(int n){
	matrix res(n, vi(n, 0));
	rep(i, 0, n)res[i][i] = 1;
	return res;
}

matrix mmul(matrix a, matrix b){
	matrix res(a.size(), vi(b[0].size(), 0));
	rep(i, 0, a.size()){
		rep(j, 0, b[0].size()){
			rep(k, 0, b.size()){
				res[i][j] += (a[i][k]*b[k][j]);
			}
		}
	}
	return res;
}

matrix mexp(matrix m, int b){
	if (b==0)return iden(m.size());
	matrix res = mexp(m, b/2); res = mmul(res, res);
	if (b%2)res = mmul(res, m);
	return res;
}