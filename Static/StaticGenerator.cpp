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

int main(int argc, char* argv[]){//Q1 Q2 N seed
	assert(argc == 5);
	
	int Q1 = to_int(argv[1]);
	int Q2 = to_int(argv[1]);
	int N = to_int(argv[3]);
	mt19937 rng(to_int(argv[4]));	
	
	printf("%d %d\n", Q1, Q2);
	
	for(int i = 0; i < Q1; ++i){
		double a = random_double(-N, N, rng);
		double b = random_double(-N, N, rng);
		double c = random_double(-N, N, rng);
		printf("%lf %lf %lf\n", a, b, c);
	}

	for(int i = 0; i < Q2; ++i){
		double x = random_double(-N, N, rng);
		printf("%lf\n", x);
	}
	
	return 0;
}
