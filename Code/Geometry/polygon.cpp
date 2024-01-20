//polygon functions

float polarea(vector<point> pol){
	float res = 0; pol.pb(pol[0]);
	rep(i, 0, n)res += pol[i]^pol[i+1];
	return abs(res)/2.0;
}

int inpolygon(vector<point> pol, point p){
	pol.pb(pol[0]); 
	int counter=0; point o = point(p.x+1, 2e9);
	rep(i, 0, sz(pol)-1){
		point a = pol[i], b = pol[i+1];
		if (insegment(a,b,p))return 0;
		bool ina = insegment(p,o,a), inb = insegment(p,o,b);
		counter += (intersect(a,b,p,o) and not (ina and inb));
		counter += ina;
	}
	if (counter%2)return 1;
	else return -1;
}