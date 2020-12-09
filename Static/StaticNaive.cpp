#include <bits/stdc++.h>
using namespace std;

int main(){
	int N, Q;
	scanf("%d %d", &N, &Q);
	vector<vector<double>> f(N);
	for(int i = 0; i < N; ++i){
		f[i].resize(3);
		for(auto& j: f[i]){
			scanf("%lf", &j);
		}
	}

	while(Q--){
		double x;
		scanf("%lf", &x);
		double res = std::numeric_limits<double>::max();
		for(auto i: f){
			res = min(res, x * x * i[0] + x * i[1] + i[2]);
		}

		printf("%.3lf\n", res);
	}
	
	return 0;
}
