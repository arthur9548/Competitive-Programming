//1-indexed
//about 1.5x faster than recursive segtree
//class/struct/array is indiferent
struct BIT{
	int n;
	vi bit, nums;
	
	BIT(int s){
		n = s; bit.assign(n+1, 0); nums.assign(n+1, 0);
	}
	BIT(vi v){
		n = sz(v)-1; bit.assign(n+1, 0); nums.assign(n+1, 0);
		rep(i, 1, n+1)update(i, v[i]);
	}
	
	void update(int pos, int x){
		updt(pos, x-nums[pos]); nums[pos] = x;
	}
	
	int query(int l, int r){
		return qry(r)-qry(l-1);
	}
	
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

//quadratic memory, log square query
struct BIT2D{
	int n;
	vector<BIT> bit;
	matrix nums;
	
	BIT2D(int s){
		n = s; nums.assign(n+1, vi(n+1, 0)); bit.assign(n+1, BIT(n));
	}
	
	void update(int x, int y){
		updt(x, y, 1-2*nums[x][y]); nums[x][y] = 1-nums[x][y];
	}
	
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
	
	int query(int x1, int y1, int x2, int y2){
		x1--; y1--;
		int res = qry(x2,y2)+qry(x1,y1);
		res -= (qry(x1,y2)+qry(x2,y1));
		return res;
	}
};