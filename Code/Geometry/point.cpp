// Point/vector structure definition

#define T int
float EPS = 1e-6;
bool eq(T a, T b){ return abs(a-b)<=EPS; }

struct point{
	T x, y;
	point(T xx=0, T yy=0): x(xx), y(yy){}
	
	point operator+(const point &o) const{ return {x + o.x, y + o.y}; }
	point operator-(const point &o) const{ return {x - o.x, y - o.y}; }
	point operator*(T k) const{ return {x*k, y*k}; }
	point operator/(T k) const{ return {x/k, y/k}; }
	T operator*(const point &o) const{ return x*o.x + y*o.y; } //dot product
	T operator^(const point &o) const{ return x*o.y - y*o.x; } //cross product
	bool operator<(const point &o) const{ return (eq(x, o.x) ? y < o.y : x < o.x); }
	bool operator==(const point &o) const{ return eq(x, o.x) and eq(y, o.y); }
	
	friend auto& operator<<(ostream& os, point p){
		return os << "(" << p.x << "," << p.y << ")";
	}
	friend auto& operator>>(istream& is, point& p){
		cin >> p.x >> p.y; return is;
	}
};

