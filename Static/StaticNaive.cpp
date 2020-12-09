#include <bits/stdc++.h>
using namespace std;

int main(){
	int Q1, Q2;
	scanf("%d %d", &Q1, &Q2);
	vector<vector<double>> f(Q1);
	for(int i = 0; i < Q1; ++i){
		f[i].resize(3);
		for(auto& j: f[i]){
			scanf("%lf", &j);
		}
	}

	while(Q2--){
		double x;
		scanf("%lf", &x);
		double res = std::numeric_limits<double>::max();
		for(auto i: f){
			res = min(res, x * x * i[0] + x * i[1] + i[2]);
		}

		printf("%.5lf\n", res);
	}
	
	return 0;
}
