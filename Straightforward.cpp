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

typedef parabola<int, long long> Function;

int main()
{
	vector<Function> S;
	int q;
	scanf("%d", &q);
	while(q--)
	{
		int type;
		scanf("%d", &type);
		if (type == 1)
		{
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			S.push_back(Function(a, b, c));
		}
		else
		{
			int x;
			scanf("%d", &x);
			long long minimum = LLONG_MAX;
			for(auto i: S)
				minimum = min(minimum, i.query(x));
			
			printf("%lld\n", minimum);
		}
	}
	
	return 0;
}
