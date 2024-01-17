set<int> lis;

int onlinelis(vector<int> v){
	rep(i, 0, v.size()){
		int cur = v[i];
		if (lis.empty()){
			lis.insert(cur); continue;
		}
		auto it = lis.lower_bound(cur);
		if (it == lis.end()){
			lis.insert(cur); continue;
		}
		int sub = min(cur, *it);
		lis.erase(it); lis.insert(sub);
	}
	return lis.size();
}