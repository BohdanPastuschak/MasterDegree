#include <bits/stdc++.h>
using namespace std;

template<typename T, typename R>
struct parabola
{
	T a, b, c;
	parabola(){}
	parabola(T _a, T _b, T _c): a(_a), b(_b), c(_c) {}
	
	R query(int x)
	{
		return a * (R) x * x + b * (R) x + c;
	}
};

typedef parabola<double, double> Function;

int main()
{
	vector<Function> S;
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
			S.push_back(Function(a, b, c));
		}
		else
		{
			int x;
			scanf("%d", &x);
			double minimum = DBL_MAX;
			for(auto i: S)
				minimum = min(minimum, i.query(x));
			
			result += minimum;
			//printf("%lld\n", minimum);
		}
	}
	
	cerr << result << endl;
	cout << clock() / (double) CLOCKS_PER_SEC << endl;
	return 0;
}
