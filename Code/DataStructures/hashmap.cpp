/**
	* Title: Safe Hash Map
	* Description: safe and efficient hash map based on unordered_map
	* Complexity:
		- Access and operations: O(~1) (log(n) on average?)
		- Memory: O(n)
	* Restrictions:
		- Keys must be convertible to uint64_t
	* Observations:
		- Use .reserve(MXN) to improve constant factor
		- Bad constant factor in memory and time
	* Tested at:
		- Word Combinations (CSES)
	* Based on: https://codeforces.com/blog/entry/62393
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