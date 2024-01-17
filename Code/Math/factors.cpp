int lp[MXN];

void buildsieve(){
	rep(i, 2, MXN){
		if (lp[i])continue;
		repstep(j, i, MXN, i)lp[j] = i;
	}
}

//O(MXNlog(log(MXN))) + O(log(n))
map<int, int> factors1(int n){
	map<int, int> facts;
	while(n > 1){
		int cp = lp[n];
		while(n%cp == 0){
			n/=cp; facts[cp]++;
		}
	}
	return facts;
}

vector<int> divs[MXN];

void buildlist(){
	rep(i, 1, MXN){
		repstep(j, i, MXN, i)divs[j].pb(i);
	}
}

//O(MXNlog(MXN)) + O(1)
vector<int> divisors1(int n){
	return divs[n];
}

//O(sqrt(n))
vector<int> divisors2(int n){
	set<int> res;
	int mx = sqrt(n)+2;
	rep(i, 1, mx){
		if (res%i == 0){
			res.insert(i); res.insert(n/i);
		}
	}
	vector<int> ans;
	for(int x : res)ans.pb(x);
	return ans;
}

map<int, int> factors2(int n){
	map<int, int> ans;
	int d=2;
	while(n > 1 and d*d <= n){
		while(n%d and d*d <= n)d++;
		while(n%d==0){
			ans[d]++; n/= d;
		}
	}
	if (n>1)ans[n]++;
	return ans;
}