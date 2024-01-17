vector<int> kmp(string& s){
	int n = s.size();
	vector<int> pi(n, 0);
	rep(i, 1, n){
		int j = pi[i-1];
		while(j > 0 and s[j]!=s[i])j = pi[j-1];
		j += (s[i]==s[j]);
		pi[i] = j;
	}
	return pi;
}

int aut[MXN][26]

void buildaut(string s){
	s.pb('#'); int n = s.size();
	auto p = kmp(s);
	rep(i, 0, n){
		rep(c, 0, 26){
			if (i > 0 and c+'a' != s[i])aut[i][c] = aut[p[i-1]][c];
			else aut[i][c] = i + (c+'a' == s[i]);
		}
	}
}
