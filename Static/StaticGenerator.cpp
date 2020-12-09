#include <bits/stdc++.h>
using namespace std;

inline int to_int(char* argv){
	int result = 0;
	for(int i = 0; i < (int)strlen(argv); ++i){
		result = 10 * result + argv[i] - '0';
	}	
	return result;
}

inline int random_int(int l, int r, mt19937& rng){
	return l + (rng() % (r - l + 1));
}

inline double random_double(double l, double r, mt19937& rng){
	return l + (random_int(0, 1000000 - 1, rng) / 1000000.0) * (r - l);
}

int main(int argc, char* argv[]){//N Q C seed
	assert(argc == 5);
	
	int N = to_int(argv[1]);
	int Q = to_int(argv[1]);
	int C = to_int(argv[3]);
	mt19937 rng(to_int(argv[4]));	
	
	printf("%d %d\n", N, Q);
	
	for(int i = 0; i < N; ++i){
		double a = random_double(-C, C, rng);
		double b = random_double(-C, C, rng);
		double c = random_double(-C, C, rng);
		printf("%lf %lf %lf\n", a, b, c);
	}

	for(int i = 0; i < Q; ++i){
		double x = random_double(-C, C, rng);
		printf("%lf\n", x);
	}
	
	return 0;
}
