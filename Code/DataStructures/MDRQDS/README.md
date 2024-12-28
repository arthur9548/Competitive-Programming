## About my MDRQDS
This folder contains my implementation of Multidimensional Range Query Data Structures (MDRQDS). Please read the information regarding my 
[Data Structures code](https://github.com/arthur9548/Competitive-Programming/blob/main/Code/DataStructures/README.md) to understand how to use it.

[This blog](https://codeforces.com/blog/entry/64914) inspired me to think about multidimensionality in a broader way. 
I'm currently working on my own blog to explain the concepts and implementation details of MDRQDS.

The implementation looks like this:
```c++
#define MAs template<class... As>
template<int D, class S>
struct MRQ{ using T = typename S::T; //multidimensional case
  int n; vector<MRQ<D-1, S>> v;
  MAs MRQ(int s, As... ds):n(s),v(n,MRQ<D-1, s>(ds...)){}
  //{update or set and init methods}
  MAs T query(int l, int r, As... ps){return S::op(v[l...r].query(ps...));}
};
template<class S>
struct MRQ<0, S>{ using T = typename S::T; //base case (0D)
  T val = S::id;
  T query(){return val;}
};
//{some Algebraic Structure with the type T, identity id and operation op}

void usage{
  MRQ<3, AlgebraicStructure> ds(3, 4, 5); //3x4x5 data structure based on this Algebraic Structure
  //all points start with identity value
  
  //if MRQ works with static range queries:
  ds.set(val, x, y, z); //set (x, y, z) value to val
  ds.init() //ready to answer queries
  
  //if MRQ works with point updates:
  ds.update(val, x, y, z); //update (x, y, z) value to val

  //queries:
  cout << ds.query(x1, x2, y1, y2, z1, z2) << endl;
  //query of operation over all points (x, y, z) such that x1 <= x <= x2, y1 <= y <= y2 and z1 <= z <= z2
}
```
