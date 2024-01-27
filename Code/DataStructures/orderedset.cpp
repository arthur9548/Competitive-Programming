//does not run on C++ Windows 
#include<bits/extc++.h> //include it before int long long
#define GNU __gnu_pbds
template<typename T, typename B = GNU::null_type>
using ordered_set = GNU::tree<T, B, less<T>, GNU::rb_tree_tag, 
GNU::tree_order_statistics_node_update>;

void example(ordered_set<int> oset){
  rep(i, 0, 5)if (i%2)oset.insert(i);
  int pos = oset.order_of_key(4); //==2, number of smaller elements in set
  int num = oset.find_by_order(2); //==5, acessing element by index
}
  
  
