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

int main(int argc, char* argv[])
{
	assert(argc > 5);
	
	int T = to_int(argv[1]);//total number of queries
	int C = to_int(argv[2]);//max coordinate
	int M = to_int(argv[3]);
	int P = to_int(argv[4]);//percentage of first type
	mt19937 rng(to_int(argv[5]));//random device	
	
	printf("%d\n", T);
	for(int i = 0; i < T; ++i)
	{
		int type = i == 0 ? 1 : random_int(0, 99, rng) < P;
		printf("%d ", type);
		if (type == 1)
		{
			int a = random_int(-M, M, rng);
			int b = random_int(-M, M, rng);
			int c = random_int(-M, M, rng);
						
			printf("%d %d %d\n", a, b, c);
		}
		else
		{
			int x = random_int(0, C - 1, rng);
			printf("%d\n", x);
		}
	}
	
	return 0;
}
