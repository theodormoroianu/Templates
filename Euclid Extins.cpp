#include <bits/stdc++.h>
using namespace std;

using T = int;

T gcd(T a, T b, T& coefa, T& coefb)
{
	T coefaa = 1, coefab = 0, coefba = 0, coefbb = 1;
	while (a) {
		T rap = b / a;
		swap(a, b -= rap * a);
		swap(coefaa, coefba -= rap * coefaa);
		swap(coefab, coefbb -= rap * coefab);
	}
	coefa = coefba, coefb = coefbb;
	return b;
}


int main()
{
	int a, b, x, y;
	cin >> a >> b;

	int d = gcd(a, b, x, y);

	cout << a << " * " << x << " + " << b << " * " << y << " = " << d << '\n';

	return 0;
}