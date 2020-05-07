#include <bits/stdc++.h>
using namespace std;

inline int to_int(char* argv)
{
	int result = 0;
	for(int i = 0; i < (int)strlen(argv); ++i)
	{
		result = 10 * result + argv[i] - '0';
	}
	
	return result;
}

inline int random_int(int l, int r, mt19937& rng)
{
	return l + (rng() % (r - l + 1));
}

int main(int argc, char* argv[])
{
	assert(argc > 3);
	
	int q = to_int(argv[1]);
	int N = to_int(argv[2]);
	mt19937 rng(to_int(argv[3]));	
	
	printf("%d\n", q);
	for(int i = 0; i < q; ++i)
	{
		int type = i == 0 ? 1 : random_int(1, 2, rng);
		printf("%d ", type);
		if (type == 1)
		{
			int a = random_int(0, N - 1, rng);
			int b = random_int(0, N - 1, rng);
			int c = random_int(0, N - 1, rng);
			printf("%d %d %d\n", a, b, c);
		}
		else
		{
			int x = random_int(0, N - 1, rng);
			printf("%d\n", x);
		}
	}
	
	return 0;
}
