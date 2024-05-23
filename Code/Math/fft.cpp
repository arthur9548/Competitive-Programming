template<class num> struct FFT{
	typedef vector<num> vnum;
	vector<num> proots; 
	FFTfield(){proots = {num(1)};}
	
	vnum fast_dft(const vnum & a, bool to_invert=false)const{
		int n = sz(a); 
		vnum na(all(a));
		rep(i, 0, n){
			if (i < revbits(i, n)){
				swap(na[i], na[revbits(i, n)]);
			}
		}
		int step = 1;
		while(step < n){
			step *= 2; 
			num root = proots[step];
			repstep(i, 0, n, step){
				num omega = num(1);
				rep(s, 0, step/2){
					num e = na[i+s], o = na[i+s+step/2];
					na[i+s] = e + omega*o;
					na[i+s+step/2] = e - omega*o;
					omega = omega*root;
				}
			}
		}
		if (to_invert){
			reverse(na.begin()+1, na.end());
			rep(i, 0, n)na[i] = na[i]/num(n);
		}
		return na;
	}
 
	vnum smul(const vnum& a, const vnum& b)const{
		vnum res(sz(a));
		rep(i, 0, sz(a))res[i] = a[i] * b[i];
		return res;
	}
	
	vi poly_mul(const vi & a, const vi & b){
		int rn = sz(a) + sz(b) - 1;
		int n = __builtin_clz(1) - __builtin_clz(rn);
		if (__builtin_popcount(rn)>1)n++;
		n = 1<<n;
		while(sz(proots)<=n)proots.pb(num::proot(sz(proots)));
		vnum na(all(a)); vnum nb(all(b)); 
		na.resize(n, num(0)); nb.resize(n, num(0));
		vnum nc = fast_dft(smul(fast_dft(na), fast_dft(nb)), true);
		return vi(all(nc));
	}
};
