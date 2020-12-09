#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-7;

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
	T a, b, c;
	parabola(){}
	parabola(T _a, T _b, T _c): a(_a), b(_b), c(_c) {}
		
	R query(T x)
	{
		return a * (R) x * x + b * (R) x + c;
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
				
			return vector<double>{x1, x2};
		}
	}
};

typedef parabola<double, double> Function;
const double INF = 1e9;

struct elem{
	double l, r;
	int value;
};

class Solution{
private:
	vector<elem> P;
	vector<Function> F;

	int find_id_of_minimum_at_point(double x){
		int best = -1;
		double val = 0;
		for(int i = 0; i < (int)F.size(); ++i){
			double here = F[i].query(x);
			if (best == -1 || here < val){
				val = here;
				best = i;
			}				
		}

		return best;
	}
	
	void initialize(){
		double l = -INF;
		int id = find_id_of_minimum_at_point(l);
		while(true){
			double r = 0;
			int best_id = -1;
			for(int i = 0; i < (int)F.size(); ++i) if (i != id){
				vector<double> intersections = F[i].intersections(F[id]);
				for(auto j: intersections){
					if (j > l + EPS && (best_id == -1 || j < r)){
						r = j;
						best_id = i;
					}
				}
			}

			if (best_id == -1){
				P.push_back({l, INF, id});
				break;
			}

			P.push_back({l, r, id});
			l = r;
			id = find_id_of_minimum_at_point(l + EPS);
		}	
	}
	
public:
	Solution(vector<Function>& f){
		F = f;
		initialize();
	}

	double get_minimum(double x){
		int L = -1, R = (int)P.size() - 1, M;
		while(R - L > 1){
			M = (L + R) >> 1;
			if (P[M].r >= x){
				R = M;
			}else{
				L = M;
			}
		}

		return F[P[R].value].query(x);
	}
};

int main(){
	int N, Q;
	scanf("%d %d", &N, &Q);
	vector<Function> functions(N);
	for(int i = 0; i < N; ++i){
		double a, b, c;
		scanf("%lf %lf %lf", &a, &b, &c);
		functions[i] = Function(a, b, c);
	}
	
	Solution solution(functions);
	
	while(Q--){
		double x;
		scanf("%lf", &x);
		printf("%.3lf\n", solution.get_minimum(x));
	}
	

	cerr << "Time spent by solution: " << fixed << setprecision(3) << clock() / (double) CLOCKS_PER_SEC << " seconds" << endl;
	return 0;
}
