//Binary Indexed Tree (BIT): structure to perform prefix queries with update
//1-indexed!
//O(logn) query and update, about 1.5x faster than recursive segtree
struct BIT{
	int n; //BIT size
	vi bit, nums; //BIT array, original array

	BIT(int s){
		n = s; bit.assign(n+1, 0); nums.assign(n+1, 0);
	}

	BIT(vi v){
		n = sz(v); bit.assign(n+1, 0); nums.assign(n+1, 0);
		rep(i, 1, n+1)update(i, v[i-1]); //1-indexed
	}

	//Interface functions
	void update(int pos, int x){
		updt(pos, x-nums[pos]); nums[pos] = x;
	}
	
	int query(int l, int r){
		return qry(r)-qry(l-1);
	}

	//Real functions
	void updt(int pos, int x){
		while(pos <= n){
			bit[pos]+=x; pos += (1ll<<(__builtin_ctzll(pos)));
		}
	}
	
	int qry(int pos){
		int res = 0;
		while(pos){
			res += bit[pos]; pos -= (1ll<<(__builtin_ctzll(pos)));
		}
		return res;
	}
};

//BIT 2D: O(log^2 n query)
struct BIT2D{
	int n, m;
	vector<BIT> bit;
	vvi nums;
	
	BIT2D(int size1, int size2){
		n = size1; m = size2;
		nums.assign(n+1, vi(m+1, 0)); bit.assign(n+1, BIT(m)); //still 1-indexed
	}

	//Interface
	void update(int x, int y, int num){
		updt(x, y, num-nums[x][y]); nums[x][y] = num;
	}
	
	int query(int x1, int y1, int x2, int y2){
		x1--; y1--;
		int res = qry(x2,y2)+qry(x1,y1);
		res -= (qry(x1,y2)+qry(x2,y1));
		return res;
	}

	//Real
	void updt(int x, int y, int val){
		while(x <= n){
			bit[x].updt(y, val); x += (1ll<<(__builtin_ctzll(x)));
		}
	}
	
	int qry(int x, int y){
		int res=0;
		while(x){
			res += bit[x].qry(y); x -= (1ll<<(__builtin_ctzll(x)));
		}
		return res;
	}
};
