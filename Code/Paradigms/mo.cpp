void calcinclude(int pos, int ans){
	return;
}

void calcexclude(int pos, int ans){
	return;
}

vi mo(int n, int q, vector<pii> queries){
	vi results(q);
	int sq = sqrt(q)+1;
	int b = (n+sq-1)/sq;
	vector<pair<pii, pii>> moqueries;
	rep(i, 0, q){
		int l = queries[i].first, r = queries[i].second;
		moqueries.pb({l/b, r}, {l, i});
	}
	sort(all(moqueries));
	int cl=0, cr=0;
	for(auto info : moqueries){
		int idx = info.second.second;
		int l = info.second.first, r = info.first.second;
		int ans = 0;
		while(cr < r){
			cr++ calcinclude(cr, ans);
		}
		while(cl > l){
			cl--; calcinclude(cl, ans);
		}
		while(cl < l){
			calcexclude(cl, ans); cl++;
		}
		while(cr > r){
			calc(exclude(cr, ans)); cr--;
		}
		results[i] = ans;
	}
	return results;
}