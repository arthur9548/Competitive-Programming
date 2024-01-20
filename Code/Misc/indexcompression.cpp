//index compression (O(sort) or O(nlogn) if map)
//can be void if map is not necessary
map<int, int> compress(vi & v){
	int n = sz(v);
	vector<pii> els;
	rep(i, 0, n)els.pb({v[i], i});
	sort(all(els));
	map<int, int> trad; int val=1; // initial value
	rep(i, 0, n){
		val += (i and els[i].first != els[i-1].first);
		trad[v[els[i].second]] = val;
		v[els[i].second] = val;
	}
}