struct Query{
	int l, r, lx, idx;
	Query(int ql, int qr, int qidx, int qb){
		l = ql; r = qr; idx = qidx; lx = l/qb;
	}
	bool operator<(const Query& o){
		return make_pair(lx, r) < make_pair(o.lx, o.r);
	}
};

vi mo(int n, vector<pii> queries){
	int q = queries.size();
	int sq = sqrt(q)+1, b = (n+sq-1)/sq;
	vector<Query> moqueries;
	rep(i, 0, q)moqueries.pb(Query(queries[i].first, queries[i].second, i, b));
	sort(all(moqueries));
	vi ans(q);
	int cl=0, cr=0, cans=0;
	auto include = [&](int pos)->void{
		return;
	};
	auto exclude = [&](int pos)->void{
		return;
	};
	include(0);
	for(auto qry : moqueries){
		while(cr < qry.r){
			cr++; include(cr);
		}
		while(cl > qry.l){
			cl--; include(cl);
		}
		while(cl < qry.l){
			exclude(cl); cl++;
		}
		while(cr > qry.r){
			exclude(cr); cr--;
		}
		ans[q.idx] = cans;
	}
	return ans;
}
