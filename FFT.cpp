#include <bits/stdc++.h>
using namespace std;

/// FFT FUNCTION FOR COMPUTING G * P, WHERE G AND P ARE 2 INTEGER POLINOMIALS

/// Complex function can be replaced with complex <double>
/*
	using Complex = complex <double>;
	Fuctions from std::complex are the same as below
*/

class Complex {
public:
	double r, i;
	Complex(double r = 0, double i = 0) : r(r), i(i) { }
	double real() { return r; }
	double imag() { return i; }
	double real(double v) { return r = v; }
	double imag(double v) { return i = v; }
	Complex operator+ (Complex a) { return { r + a.r, i + a.i }; }
	Complex operator- (Complex a) { return { r - a.r, i - a.i }; }
	Complex operator+= (Complex a) { return { r += a.r, i += a.i }; }
	Complex operator-= (Complex a) { return { r -= a.r, i -= a.i }; }
	Complex operator* (Complex a) { return { r * a.r - i * a.i, r * a.i + i * a.r }; };
	Complex operator* (double a) { return { r * a, i * a }; };
	Complex operator*= (double a) { return { r *= a, i *= a }; };
	Complex operator/ (double a) { return { r / a, i / a }; };
	Complex operator/= (double a) { return { r /= a, i /= a }; };
	Complex operator*= (Complex a) { return *this = *this * a; };

};

Complex Polar(double r, double angle) {
	return Complex({ cos(angle) * r, sin(angle) * r });
}

using Vc = vector <Complex>;
const double PI = acos(-1);

void FFT(Vc & v, int inv = 1) {
	int n = v.size();
	for (int i = 0, j = 0; i < n; i++) {
		if (i < j)
			swap(v[i], v[j]);
		for (int k = n / 2; (j ^= k) < k; k /= 2)
			;
	}

	for (int l = 2; l <= n; l *= 2) {
		Complex k, k0 = Polar(1., 2 * PI * inv / l);
		for (int i = 0; i < n; i += l) {
			k = Polar(1, 0);
			for (int j = 0; j < l / 2; j++) {
				Complex p = v[i + j], q = k * v[i + j + l / 2];
				v[i + j] = p + q;
				v[i + j + l / 2] = p - q;
				if (inv == -1)
					v[i + j] /= 2., v[i + j + l / 2] /= 2.;
				k *= k0;
			}
		}
	}
}

vector <int> FFT(vector <int> & a, vector <int> & b, bool remove_end = 0) {
	int n = a.size() + b.size() - 1;
	while ((n & -n) != n)
		n += n & -n;
	Vc x(n), y(n);
	for (int i = 0; i < a.size(); i++)
		x[i].real(a[i]);
	for (int i = 0; i < b.size(); i++)
		y[i].real(b[i]);

	FFT(x);
	FFT(y);

	for (int i = 0; i < n; i++)
		x[i] *= y[i];

	FFT(x, -1);

	vector <int> ans(n);
	for (int i = 0; i < n; i++)
		ans[i] = (x[i].real() + (x[i].real() > 0 ? 0.5 : -0.5));

	if (remove_end)
		while (ans.size() > 1 && ans.back() == 0)
			ans.pop_back();
	return ans;
}


int main()
{
	int a, b;
	cin >> a >> b;
	vector <int> v1(a), v2(b);

	for (auto& i : v1)
		cin >> i;
	for (auto& i : v2)
		cin >> i;

	auto ans = FFT(v1, v2);

	for (auto i : ans)
		cout << i << ' ';

	return 0;
}