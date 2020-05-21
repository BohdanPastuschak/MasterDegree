#include <bits/stdc++.h>
using namespace std;

inline int to_int(char* argv)
{
	int result = 0;
	for(int i = 0; i < (int)strlen(argv); ++i)
		result = 10 * result + argv[i] - '0';
	
	return result;
}

inline int random_int(int l, int r, mt19937& rng)
{
	return l + (rng() % (r - l + 1));
}

inline double random_double(int l, int r, mt19937& rng)
{
	double in01 = (double)(rng() % INT_MAX) / INT_MAX;
	double in01_2 = (double)(rng() % INT_MAX) / INT_MAX;
	return l + (r - l) * in01 + in01_2;
}

int main(int argc, char* argv[])
{
	assert(argc > 5);
	
	int T = to_int(argv[1]);//total number of queries
	int C = to_int(argv[2]);//max coordinate
	int M = to_int(argv[3]);
	int P = to_int(argv[4]);//percentage of first type
	mt19937 rng(to_int(argv[5]));//random device	
	
	int k = 1;
	printf("%d\n", T);
	for(int i = 0; i < T; ++i)
	{
		int type = i == 0 ? 1 : 1 + (random_int(0, 99, rng) < P);
		printf("%d ", type);
		if (type == 1)
		{
			long long a = k;
			long long b = -k * (long long) 2 * (k - 1);
			long long c = k * (long long) (k - 1) * (k - 1);
			c += C / 2;
			k++;			
			printf("%lld %lld %lld\n", a, b, c);
		}
		else
		{
			int x = random_int(0, C - 1, rng);
			printf("%d\n", x);
		}
	}
	
	return 0;
}
