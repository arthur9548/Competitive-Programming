/**
	* Title: Value/Coordinate/Index compression
	* Description: compression of values in vector to the range [0, n)
	* Complexity: 
		- Time: O(sort)
		- Memory: O(n)
	* Restrictions:
		- T must be assignable to int in in_place version
	* Observations:
		- Hash table can be changed to hash map (change .resize to .reserve) or map
	* Tested at:
		- Distinct Value Queries (CSES)
*/

template<class T> void in_place_compression(vector<T>& v, int inic = 0){
	int n = sz(v); vi o(n); iota(all(o), 0);
	sort(all(o), [&](int i, int j){return v[i] < v[j];});
	for(int pv, cv, p, x = inic, i = 0; i < n; p = o[i], 
		cv = v[p], x += i++ && pv != cv, pv = cv, v[p] = x);
}

template<class T> hash_table<T, int> mapped_compression(vector<T> v, int inic=0){
	hash_table<T, int> c; c.resize(sz(v));
	sort(all(v)); v.erase(unique(all(v)), v.end());
	for(int i : v){c[i] = inic++;} return c;
}