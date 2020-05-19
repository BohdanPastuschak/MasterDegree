#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;//for double evaluation

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
class SegmentTree
{
private:
	
	int n;//size
	vector<Function> tree;
	
	void add_parabola(Function f, int v, int l, int r, int last_type = -1)//push f to range [l, r)
	{
		Function& g = tree[v];
		vector<double> intersections = g.intersections_in_range(f, (double) l, (double) r);
		
		if (r - l == 1 || intersections.size() == 0)//if v is leaf vertex
		{
			if (f.query(l) < g.query(l))//if this candidate is better, substitute current value at vertex by it
				swap(f, g);
			return;
		}
			
		int m = (l + r) >> 1;
		
		if (intersections.size() == 1)//there is exactly one intersection at range
		{			
			double I = intersections[0];
			if (I < m)//intersection on left half
			{
				if (f.query(m) < g.query(m))
					swap(f, g);
				
				add_parabola(f, v * 2, l, m);				
			}
			else//intersection on right half
			{
				if (f.query(l) < g.query(l))
					swap(f, g);
				
				add_parabola(f, v * 2 + 1, m, r);
			}
			
			return;
		}
		
		//now we have two intersections
		
		double I1 = intersections[0];
		double I2 = intersections[1];
		
		if (is_smaller<double>(I2, (double) m))//both intersections are on left half
		{
			if (f.query(m) < g.query(m))
				swap(f, g);
			
			add_parabola(f, v * 2, l, m);	
			return;
		}
		
		if (is_smaller<double>((double) m, I1) || is_equal<double>((double)m, I1))//both intersections are on right half
		{
			if (f.query(l) < g.query(l))
				swap(f, g);
				
			add_parabola(f, v * 2 + 1, m, r);
			return;
		}
		
		//we have one intersection on left half, and one on right one
		//so we need to push f line to both of them
		
		if (last_type != -1)
		{
			if (last_type == 0)
				add_parabola(f, v * 2, l, m);
			else
				add_parabola(f, v * 2 + 1, m, r);
			
			return;
		}
		
		double new_m = (l + m) / 2.0;
		if (is_smaller(I1, new_m))
		{
			if (f.query(m) < g.query(m))
				swap(f, g);
			add_parabola(f, v * 2, l, m, 0);
			add_parabola(f, v * 2 + 1, m, r);
		}
		else
		{
			if (f.query(m) > g.query(m))
				swap(f, g);
			add_parabola(f, v * 2, l, m, 1);
			add_parabola(f, v * 2 + 1, m, r);
		}		
	}	

public:
	SegmentTree(){}
	SegmentTree(int _n)
	{
		n = _n;
		tree.resize(n << 2);
	}
		
	void add_parabola(Function f)
	{
		add_parabola(f, 1, 0, n);
	}	

	double get_minimum(int x)
	{
		int v = 1, l = 0, r = n;
		double result = DBL_MAX;
		while(r - l > 1)//while v is not leaf
		{
			int m = (l + r) >> 1;
			result = min(result, tree[v].query(x));
			if (x < m)//go to left child
			{
				v = v * 2;
				r = m;
			}
			else//go to right child
			{
				v = v * 2 + 1;
				l = m;
			}
		}
		
		return result;
	}
};

int main()
{
	const int C = 1 << 20;
	SegmentTree tree(C);
	
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
			//printf("%lld\n", tree.get_minimum(x));
		}
	}
	
	cerr << result << endl;
	cout << clock() / (double) CLOCKS_PER_SEC << endl;
	return 0;
}
