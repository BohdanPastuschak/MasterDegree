#include <bits/stdc++.h>
using namespace std;

#define print(a) cerr << #a << " = " << a << endl;

int main()
{
	vector<double> a;
	double x;
	while(cin >> x)
		a.push_back(x);
	sort(a.begin(), a.end());
	double min_time = a[0];
	double max_time = a.back();
	double med_time = a[(int)a.size() / 2];
	double avg_time = 0;
	for(auto i: a)
		avg_time += i;
	avg_time /= (int)a.size();
	
	print(min_time)
	print(max_time)
	print(med_time)
	print(avg_time)
	return 0;
}
