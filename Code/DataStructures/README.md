## About my Data Structures
This section contains implementations of general use and range query data structures.

The code is my implementation, but the main idea of the design or optimization may not be mine. I have added a "Based on" field in my files to acknowledge the original resource where I found the idea (when possible).

I usually implement RQDS (Range Query Data Structures) as something similar to:
```c++
template<class S>
struct DataStructure{ using T = typename S::T;
  int n; vector<T> v;
  DataStructure(vector<T> base_vector):n(sz(base_vector)), v(base_vector){}
  void update(T x, int pos){v[pos] = x;}
  T query(int l, int r){return S::op(v[l],...,v[r]);}
};

struct AlgebraicStructure{
  using T = some_type;
  static constexpr T id = operation_identity;
  static T op(T a, T b){return operation(a, b);}
};

void usage(){
  DataStructure<AlgebraicStructure> ds(my_vector);
  ds.update(new_value, position); //0-indexed
  cout << ds.query(left_pos, right_pos) << endl; //inclusive-inclusive ([l, r])
}
```

I chose to separate my implementations of Segment Trees and MDRQDS (Multidimensional Range Query Data Structures) in separate folders for better organization.
