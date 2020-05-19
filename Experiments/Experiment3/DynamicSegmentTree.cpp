#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-5;//for double evaluation

template<typename T>
inline bool is_equal(T a, T b)
{
	if (std::is_integral<T>::value) return a == b;
	return abs(a - b) < EPS;
}

template<typename T>
inline bool is_smaller(T a, T b)
{
	if (std::is_integral<T>::value) return a < b;
	return a < b && !is_equal<T>(a, b);
}

template<typename T, typename R>
struct parabola
{
	bool is_fictive = true;
	T a, b, c;
	parabola(){}
	parabola(T _a, T _b, T _c): a(_a), b(_b), c(_c) {is_fictive = false;}
	
	bool operator==(const parabola& other) const
	{
		return is_equal<T>(a, other.a) && is_equal<T>(b, other.b) && is_equal<T>(c, other.c);
	}
	
	R query(int x)
	{
		return is_fictive ? std::numeric_limits<R>::max() : a * (R) x * x + b * (R) x + c;
	}
		
	vector<double> intersections(const parabola& other) const//sorted intersecions list
	{
		T delta_a = a - other.a;
		T delta_b = b - other.b;
		T delta_c = c - other.c;
		
		if (is_equal<T>(delta_a, T(0)))//delta_a == 0
		{
			if (is_equal<T>(delta_b, T(0)))//delta_b == 0
				return vector<double>{};
			else
				return vector<double>{-delta_c / (double) delta_b};
		}
		else
		{
			R D = delta_b * (R) delta_b - R(4) * delta_a * delta_c;//discrimimant
			if (is_smaller<R>(D, R(0))) //no solutions
				return vector<double>{};
			
			double sqrt_D = sqrtl((double)D);
			double x1 = (-delta_b - sqrt_D) / (double)(2 * delta_a);//x1, x2 - solutions of quadratic equation
			double x2 = (-delta_b + sqrt_D) / (double)(2 * delta_a);
			
			if (x1 > x2)
				swap(x1, x2);
				
			if (is_equal<double>(x1, x2)) 
				return vector<double>{x1};//roots are the same
			else
				return vector<double>{x1, x2};//dwo different roots
		}
	}

	vector<double> intersections_in_range(const parabola& other, double Left, double Right)//intersection on [Left, Right)
	{
		vector<double> all = intersections(other);
		vector<double> result;
		for(auto i: all)
		{
			if (is_smaller<double>(i, Left)) continue;
			if (is_smaller<double>(i, Right))
				result.push_back(i);
		}
		
		return result;
	}
};

typedef parabola<double, double> Function;

struct Node
{
	Function f;
	Node* l;
	Node* r;
	Node()
	{
		l = nullptr;
		r = nullptr;
	}
};

const double min_query = -1e9;
const double max_query = +1e9;

class SegmentTree
{
private:
	
	Node* root;
	
	void add_parabola(Node*& v, Function f, double l, double r, int len)
	{		
		if (v == nullptr)
		{
			v = new Node();
			v->f = f;
			return;
		}
		
		Function& g = v->f;
		vector<double> intersections = f.intersections(g);
		
		double m = (l + r) / 2;
		if ((int)intersections.size() == 0)
		{
			if (f.query(m) < g.query(m))
				swap(f, g);
			return;
		}
		
		if ((int)l == (int)r)
			return;
		if (is_equal<double>(l, r))
			return;
		
		if ((int)intersections.size() == 1)
		{
			double I = intersections[0];
			if (is_smaller<double>(I, m))
			{
				if (f.query(m) < g.query(m))
					swap(f, g);
				
				if (v->l == nullptr)
					v->l = new Node();
					
				add_parabola(v->l, f, l, m, len);				
			}
			else
			{
				if (f.query(l) < g.query(l))
					swap(f, g);
				
				if (v->r == nullptr)
					v->r = new Node();
					
				add_parabola(v->r, f, m, r, len);	
			}
			
			return;
		}
		
		double I1 = intersections[0];
		double I2 = intersections[1];
		
		if (is_smaller<double>(I2, m))
		{
			if (f.query(m) < g.query(m))
				swap(f, g);
			
			if (v->l == nullptr)
				v->l = new Node();
			add_parabola(v->l, f, l, m, len);	
			return;
		}
		
		if (is_smaller<double>(m, I1) || is_equal<double>(m, I1))
		{
			if (f.query(l) < g.query(l))
				swap(f, g);
				
			if (v->r == nullptr)
				v->r = new Node();
			add_parabola(v->r, f, m, r, len);
			return;
		}
		
		if (v->l == nullptr)
			v->l = new Node();
		if (v->r == nullptr)
			v->r = new Node();
			
		add_parabola(v->l, f, l, m, len);
		add_parabola(v->r, f, m, r, len);
	}

	double get_minimum(Node* v, double x, double l, double r)
	{
		double res = DBL_MAX;
		if (v != nullptr)
		{
			res = min(res, v->f.query(x));
			double m = (l + r) / 2;
			if (x < m)
				res = min(res, get_minimum(v->l, x, l, m));
			else
				res = min(res, get_minimum(v->r, x, m, r));
		}
		
		return res;
	}
	
public:
	
	SegmentTree()
	{
		root = nullptr;
	}
		
	void add_parabola(Function f)
	{
		add_parabola(root, f, min_query, max_query, 0);
	}	

	double get_minimum(double x)
	{
		return get_minimum(root, x, min_query, max_query);
	}
	
};

int main()
{
	SegmentTree tree;
	
	int q;
	scanf("%d", &q);
	double result = 0;
	while(q--)
	{
		int type;
		scanf("%d", &type);
		if (type == 1)
		{
			double a, b, c;
			scanf("%lf %lf %lf", &a, &b, &c);
			tree.add_parabola(Function(a, b, c));
		}
		else
		{
			int x;
			scanf("%d", &x);
			result += tree.get_minimum(x);
		}
	}
	
	cerr << result << endl;
	cout << (double) clock() / CLOCKS_PER_SEC << endl;
	return 0;
}
