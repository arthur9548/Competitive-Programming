//Title: Hash Map
//Description: safe and efficient hash map based on unordered_map
//Complexity: O(1) operations on average
//Restrictions: elements must be convertible to long long
//Observations:
//--- If not using long long keys, create hash function from object to long long
//Tested at: -

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
  
void example(){
	hash_map<int, char> m;
	m[1] = 'a';
	m[2] = 'b';
	m[1] = 'c';
	m[-1] = 'a';
	cout << m.count(-1) << endl; // 1
	for(auto [a, b] : m){ //not in order
		cout << a << esp << b << endl;
	}
}