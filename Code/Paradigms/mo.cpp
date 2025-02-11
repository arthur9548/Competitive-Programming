/**
	* Title: Mo's Algorithm
	* Description: provides an order to efficiently answer range queries
	* Complexity:
		- Memory: O(q)
		- Time: O(sort(q))
		- Template: O((add + del) * (n * sqrt(q) + q * sqrt(n)) + q * calc)
	* Observations:
		- Queries can be [l1, r1], [l1, l2] or [r1, r2]
		- Change template according to query and problem types
	* Tested at:
		- Distinct Value Queries (CSES)
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
/*
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