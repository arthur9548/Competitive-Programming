//does not run on C++ Windows 
#include<bits/extc++.h> //include it before int long long
#define GNU __gnu_pbds
template<typename T, typename B = GNU::null_type>
using ordered_set = GNU::tree<T, B, less<T>, GNU::rb_tree_tag, 
GNU::tree_order_statistics_node_update>;

void example(ordered_set<int> oset){
  rep(i, 0, 6)if (i%2)oset.insert(i);
  int pos = oset.order_of_key(4); //==2, number of smaller elements in set
  int num = oset.find_by_order(2); //==5, acessing element by index
}

template<typename T>
struct ordered_multiset{
	ordered_set<pair<T, int>> oset;
	int c;
	ordered_multiset(){
		c = 0;
	}
	int order_of_key(T data){
		return oset.order_of_key({data, oo});
	}
	const T* find_by_order(int pos){
		return &(*oset.find_by_order(pos)).first;
	}
	void insert(T data){
		oset.insert({data, c++});
	}
	void erase(T data){
		oset.erase(oset.lower_bound({data, 0}));
	}
	int size(){
		return oset.size();
	}
  const T* lower_bound(T data){
    return &(*oset.lower_bound({data, 0})).first;
  }
  const T* upper_bound(T data){
    return &(*oset.upper_bound({data, oo})).first;
  }
};
  
  
