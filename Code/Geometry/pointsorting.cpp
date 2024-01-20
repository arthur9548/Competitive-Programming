//comparator for angular sorting of points (counterclockwise)

int ret[2][2] = {{3, 2}, {4, 1}};
inline int quad(point p){
	return ret[p.x >= 0][p.y >= 0];
}

bool comp(point a, point b){
	int qa = quad(a), qb = quad(b);
	return (qa == qb ? (a ^ b) > 0 : qa < qb);
}