//location in segment and segment intersection

int location(point a, point b, point c){
	point d = c-a, e = c-b;
	int cross = d^e;
	if (cross)cross /= abs(cross);
	return cross;
}

bool insegment(point a, point b, point c){
	if (location(a,b,c))return false;
	if (a==c or b==c)return true;
	if (b<a)swap(a, b);
	return a<c and c<b;
}

bool intersect(point a, point b, point c, point d){
	if (insegment(a,b,c) or insegment(a,b,d))return true;
	if (insegment(c,d,a) or insegment(c,d,b))return true;
	bool r1 = (location(a,b,c)*location(a,b,d))==-1;
	bool r2 = (location(c,d,a)*location(c,d,b))==-1;
	return r1 and r2;
}