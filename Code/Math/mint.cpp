using ll = long long;
struct mint{
	signed v;
	mint(int val=0){v = (val>=MOD ? (val%MOD) : val);}
	static mint fexp(mint a, int b){
		mint res = 1;
		while(b){
			if (b%2)res = res*a;
			b /= 2; a = a*a;
		}
		return res;
	}
	static mint proot(int n){
		return fexp(3, (MOD-1)/n);
	}
	mint operator+(const mint & o)const{
		signed a = v + o.v; 
		if (a>=MOD)a -= MOD;
		return {a};
	}
	mint operator-(const mint & o)const{
		signed a = v - o.v;
		if (a<0)a += MOD;
		return {a};
	}
	mint operator*(const mint & o)const{
		return {((ll)v*o.v)%MOD};
	}
	mint operator/(const mint & o)const{
		return (*this) * fexp(o, MOD-2);
	}
	bool operator==(const mint & o)const{
		return v==o.v;
	}
	operator int()const{return v;}	
};
