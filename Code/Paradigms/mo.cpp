/**
	* Title: Mo's Algorithm
	* Description: provides an order to efficiently answer range queries
	* Complexity:
		- Memory: O(q)
		- Time: O(sort(q))
		- Usual template: O((add + del) * (n * sqrt(q)) + q * calc)
		- No deletion: O(add * (n * sqrt(q)) + q * (calc + checkpoint))
	* Observations:
		- Queries can be [l1, r1], [l1, l2] or [r1, r2]
		- Change templates according to query and problem types
	* Tested at:
		- Distinct Value Queries (CSES)
		- Simultaneous Kagamimochi 2 (AC)
*/

vi mo_order(vector<pii>& qs){
	int q = sz(qs), n = 0;
	for(auto [l, r] : qs)n = max(n, max(l, r));
	int sq = (int)sqrt(q)+1, blk = (n+sq+1)/sq;
	vi order(q); iota(all(order), 0);
	auto cmp = [&](pii x){return pii(x.first/blk, x.second ^ -(x.first/blk & 1));};
	sort(all(order), [&](int i, int j){return cmp(qs[i]) < cmp(qs[j]);});
	return order;
}

/* Usual Mo template
vector mo_template(vector<pii>& qs){
	vi o = mo_order(qs);
	int l = 0, r = -1; //empty range for [l, r] queries
	prepare_to_answer_queries();
	vector ans(sz(qs));
	for(int i : o){
		auto [lq, rq] = qs[i];
		while(l > lq)add(--l, 0); //order may be different
		while(r < rq)add(++r, 1); //depending on the query
		while(l < lq)del(l++, 0); //type and problem
		while(r > rq)del(r--, 1); //structure
		ans[i] = calc();
	}
	return ans;
}
*/

pair<int, vector<vi>> mo_without_deletion(vector<pii>& qs){ //returns block size and queries by block
	int q = sz(qs), n = 0;
	for(auto [l, r] : qs)n = max(n, max(l, r));
	int sq = (int)sqrt(q)+1, blk = (n+sq+1)/sq;
	vector<vi> order((n+blk-1)/blk);
	rep(i,0,q)order[qs[i].first/blk].pb(i);
	for(auto& vq : order)sort(all(vq), [&](int i, int j){return qs[i].second < qs[j].second;});
	return {blk, order};
}

/* Mo without deletion
vector mo_template(vector<pii>& qs){
	auto [blk, o] = mo_order(qs);
	rep(i,0,sz(o)){
		auto& vq = o[i];
		int l = blk*i + blk, r = l-1; //we will assume the query will extrapolate the block
		prepare_to_answer_queries();
		for(int qi : vq){
			auto [ql, qr] = qs[qi];
			if (qr <= l){ //if it does not extrapolate
				rep(j,ql,qr+1)add(j, 1); //solving manually
				continue;
			}
			while(r < qr)add(++r, 1);
			int ml = l; //we will move l manually
			prepare_checkpoint();
			while(ml > ql)add(--ml, 0);
			ans[qi] = calc();
			revert_checkpoint(); //discard changes made by moving l
		}
	}
}
*/