#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

#define INF 1000000007
#define ll long long

template<typename T> inline T MIN(T a, T b) { return a < b ? a : b; }
template<typename T> inline T MAX(T a, T b) { return a > b ? a : b; }

using namespace std;

const int N = 10000;

int main() {
	int i, n, ans = 0;
	float a[N], b[N];

	cout << "enter vector size: ";
	cin >> n;

	cout << "enter vector A: ";
	for (i = 0; i < n; i++)
		cin >> a[i];

	cout << "enter vector B: ";
	for (i = 0; i < n; i++)
		cin >> b[i];


#pragma omp parallel for shared(a,b,ans, n) private(i) schedule(static)
	for (i = 0; i < n; i++) {
		ans += a[i] * b[i];
		cout << "cur ans: " << ans << endl;
	}
	
	cout << "a * b = " << ans << endl;

	return 0;
}
