//does not run on C++ Windows 
#include<bits/extc++.h> //include it before int long long
#define GNU __gnu_pbds
template<typename T, typename B = GNU::null_type>
using ordered_set = GNU::tree<T, B, less<T>, GNU::rb_tree_tag, 
GNU::tree_order_statistics_node_update>;

