int len[MXN];
int lnk[MXN];
int firstpos[MXN];
int endpos[MXN];
int aut[MXN][26];
int paths[MXN];
int reppaths[MXN];
int cz, last;
string aux = "";
 
void sa_add(char sc){
	int c = sc-'a';
	int cur = cz++;
	len[cur] = len[last]+1;
	endpos[cur] = 1;
	firstpos[cur] = len[cur]-1;
	int v = last;
	while(v != -1 and not aut[v][c]){
		aut[v][c] = cur; v = lnk[v];
	}
	last = cur;
	if (v == -1){
		lnk[cur] = 0;
	}
	else{
		int u = aut[v][c];
		if (len[u] == len[v]+1){
			lnk[cur] = u;
		}
		else{
			int clone = cz++; 
			len[clone] = len[v]+1; lnk[clone] = lnk[u];
			firstpos[clone] = firstpos[u];
			rep(i, 0, 26)aut[clone][i] = aut[u][i];
			while(v != -1 and aut[v][c]==u){
				aut[v][c] = clone;
				v = lnk[v];
			}
			lnk[cur] = lnk[u] = clone;
		}
	}
}
 
int dp(int v){
	if (paths[v])return paths[v];
	paths[v] = 1;
	rep(i, 0, 26)if (aut[v][i])paths[v] += dp(aut[v][i]);
	return paths[v];
}

int repdp(int v){
	if (reppaths)return reppaths[v];
	reppaths[v] = endpos[v];
	rep(i, 0, 26)if (aut[v][i])reppaths[v] += repdp(aut[v][i]);
	return reppaths[v];
}
 
void buildaut(string s){
	lnk[0] = -1; cz = 1; last = 0;
	rep(i, 0, s.size())sa_add(s[i]);
	vector<pii> states;
	rep(i, 0, cz)states.pb({len[i], i});
	sort(all(states));
	repinv(i, cz-1, 0){
		int v = states[i].second; if (not v)continue;
		endpos[lnk[v]] += endpos[v];
	}
	endpos[0] = 0; dp(0); repdp(0);
}
 
int vertex(string & t){
	int v = 0;
	rep(i, 0, t.size()){
		int c = t[i]-'a';
		if (not aut[v][c])return 0;
		v = aut[v][c];
	}
	return v;
}

string t = "#";
void travel(int v){
	cout << t << esp << endpos[v] << esp << paths[v] << endl;
	rep(i, 0, 26){
		if (aut[v][i]){
			t.pb('a'+i); travel(aut[v][i]); t.ppb();
		}
	}
}

 
void lexdfs(int v, int k, char c){
	if (k==paths[v]){
		aux.pb(c); return;
	}
	repinv(i, 25, 0){
		int nv = aut[v][i];
		if (not nv)continue;
		if (paths[nv] >= k){
			dfs(nv, k, 'a'+i);
			aux.pb(c); return;
		}
		k -= paths[nv];
	}
}

string kthlex(int k){
	k = paths[0]-k;
	dfs(0, k, 'a');
	string res = aux; aux = "";
	res.ppb(); reverse(all(res));
	return res;
}


void replexdfs(int v, int k, char c){
	if (k<=endpos[v]){
		aux.pb(c); return;
	}
	k -= endpos[v];
	rep(i, 0, 26){
		int nv = aut[v][i];
		if (not nv)continue;
		if (reppaths[nv] >= k){
			dfs(nv, k, 'a'+i);
			aux.pb(c); return;
		}
		k -= reppaths[nv];
	}
}

string repkthlex(int k){
	dfs(0, k, 'a');
	string res = aux; aux = "";
	res.ppb(); reverse(all(res));
	return res;
}