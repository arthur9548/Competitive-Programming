/**
	* Title: Safe Hash Map and Hash Table
	* Description: safe hash map based on unordered_map and hash table based on gp_hash_table
	* Complexity:
		- Access and operations: O(~1) (consider ~log(n) for calculations?)
		- Memory: O(n)
	* Restrictions:
		- Keys must be convertible to uint64_t
		-> Create a conversion and maybe a new hash structure for non-integer types
	* Observations:
		- Use .reserve(MXN) or .resize(MXN) to improve constant factor
		- Maybe it's needed to use hash table .swap instead of std::swap
		- Hash table uses ~1.5x memory, but is ~3x faster than hash map in general
		- Hash map itself has bad memory and time constant factor
	* Tested at:
		- Word Combinations (CSES)
  		- Terytoria (LOJ)
	* Based on: 
		- https://codeforces.com/blog/entry/62393
		- https://codeforces.com/blog/entry/60737
		- https://usaco.guide/gold/hashmaps?lang=cpp
*/

struct custom_hash{
	using T = uint64_t;	
	static T splitmix64(T x){
		x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(T x)const{ //if keys are not T type, conversion is necessary
    	static const T r = chrono::steady_clock::now().time_since_epoch().count();
    	return splitmix64(x+r);
    }
};
template<class A, class B>
using hash_map = unordered_map<A, B, custom_hash>;

//needs #include<bits/extc++.h> and using GNU::__gnu_pbds
template<class A, class B>
using hash_table = GNU::gp_hash_table<A, B, custom_hash, equal_to<A>,
GNU::direct_mask_range_hashing<>, GNU::linear_probe_fn<>, 
GNU::hash_standard_resize_policy<GNU::hash_exponential_size_policy<>, 
GNU::hash_load_check_resize_trigger<>, true>>;

