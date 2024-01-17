vector<int> zfunction(string& s){
	int n = s.size();
	vector<int> z(n, 0);
	int l=0, r=0;
	rep(i, 1, n){
		int j = (i <= r) * min(r-i+1, z[i-l]);
		while(j < n and s[j] == s[i+j])j++;
		if (i+j-1 > r){
			r = i+j-1; l = i;
		}
		z[i] = j;
	}
	z[0] = n;
	return z;
}
