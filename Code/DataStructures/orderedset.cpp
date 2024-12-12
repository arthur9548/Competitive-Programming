/**
	* Title: Ordered (Indexed) Set / Multiset
	* Description: set with index access
	* Complexity:
		- Access and operations: O(log(n))
		- Memory: O(n)?
	* Restrictions:
		- Elements must be comparable (< operator)
	* Observations:
		- Requires extc++.h (usually doesn't run on Windows)
		- Very bad constant factor in time and memory
		- Erases single element by erase call
		- Method find_by_order finds element as in sorted vector with duplicates
	* Tested at:
		- Salary Queries (CSES)
		- List Removals (CSES)
*/

#include<bits/extc++.h> //include it before any defines
#define GNU __gnu_pbds
template<class T, class B = GNU::null_type>
using ordered_set = GNU::tree<T, B, less<T>, GNU::rb_tree_tag, 
GNU::tree_order_statistics_node_update>;

template<class T>
struct ordered_multiset{
	ordered_set<pair<T, int>> o; int c;
	ordered_multiset():c(0){}
	unsigned order_of_key(T x){return o.order_of_key({x, -1});}
	const T* find_by_order(int p){return &(*o.find_by_order(p)).first;}
	void insert(T x){o.insert({x, c++});}
	void erase(T x){o.erase(o.lower_bound({x, 0}));}
	unsigned size(){return o.size();}
	const T* lower_bound(T x){return &(*o.lower_bound({x, 0})).first;}
	const T* upper_bound(T x){return &(*o.upper_bound({x, c})).first;}
};